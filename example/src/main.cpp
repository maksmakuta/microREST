#include "micronet/http/Router.hpp"
#include "json.hpp"

using namespace micronet;

Response noKey(const std::string& name) {
    return {400,{},"No data in body: " + name};
}

int main() {
    Router router(8080);

    std::unordered_map<std::string, std::string> store;

    router.route(Method::GET, "/", [&store](const Request &req) {
        nlohmann::json json = nlohmann::json::object();
        for (const auto &[key,val]: store) {
            json[key] = val;
        }
        return Response(200,{},json.dump());
    });

    router.route(Method::POST, "/add", [&store](const Request &req) {
        nlohmann::json obj = nlohmann::json::parse(req.body);
        if (obj.contains("key") ) {
            const auto key = obj["key"].get<std::string>();
            if (obj.contains("value")) {
                const auto value = obj["value"].get<std::string>();
                bool exists = store.find(key) != store.end();
                store[key] = value;
                if (exists) {
                    return Response(200,{},"OK: Rewrite");
                }
                return Response(201,{},"OK");
            }
            return noKey("value");
        }
        return noKey("key");
    });

    router.route(Method::POST, "/get", [&store](const Request &req) {
        const nlohmann::json obj = nlohmann::json::parse(req.body);
        if (obj.contains("key") ) {
            const auto key = obj["key"].get<std::string>();
            if (store.contains(key)) {
                nlohmann::json res;
                res["value"] = store[key];
                return Response(200,{},res.dump());
            }
            return Response(404,{},"404: Key Not Found");
        }
        return noKey("key");
    });

    router.route(Method::DELETE, "/del", [&store](const Request &req) {
        const nlohmann::json obj = nlohmann::json::parse(req.body);
        if (obj.contains("key") ) {
            const auto key = obj["key"].get<std::string>();
            if (store.contains(key)) {
                store.erase(key);
                return Response(200,{},"Item deleted");
            }
            return Response(404,{},"404: Key Not Found");
        }
        return noKey("key");
    });

    router.route(Method::GET, "/keys", [&store](const Request &req) {
        nlohmann::json keys = nlohmann::json::array();
        for (const auto &key: store | std::views::keys) {
            keys.push_back(key);
        }
        return Response(200,{},keys.dump());
    });

    router.serve();
    return 0;
}