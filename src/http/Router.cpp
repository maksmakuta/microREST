#include "micronet/http/Router.hpp"

#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

namespace micronet {

    namespace internal {

        std::atomic is_running = true;

        void stop_serving(int) {
            is_running = false;
        }

    }

    Router::Router(const int port) : Router("0.0.0.0", port) {}

    Router::Router(const std::string& host, const int port) : m_server(host,port){}

    Router& Router::route(const Method& m, const std::string& path, const std::function<Response(const Request&)>& callback) {
        m_routes.emplace_back(m, path, callback);
        return *this;
    }

    void Router::serve() const {
        std::signal(SIGINT, internal::stop_serving);
        std::signal(SIGTERM, internal::stop_serving);

        std::cout << "Start Server" << std::endl;
        m_server.listen(256);

        while (internal::is_running) {
            if (auto client = m_server.accept(); client != nullptr) {
                std::thread([this, client = std::move(client)]() mutable {
                    handleClient(client);
                }).detach();
            }
        }
        m_server.close();
        std::cout << "Server closed..." << std::endl;

    }

    void Router::handleClient(const std::unique_ptr<ClientSocket> &client) const {
        try {
            const auto req = client->getRequest();
            std::cout << to_string(req) << std::endl;
            const auto resp = process(req);
            std::cout << to_string(resp) << std::endl;
            client->send(as_response(resp));
            client->close();
            std::cout << "-----------------------------" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error during request handling: " << e.what() << std::endl;
        }
    }

    Response Router::process(const Request &request) const {
        for (const auto& [method, path, callback] : m_routes) {
            if (request.method == method && request.path == path) {
                return callback(request);
            }
        }
        return Response::NotFound();
    }
}
