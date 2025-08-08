#include "micronet/http/Response.hpp"

#include <sstream>
#include <unordered_map>

#include "micronet/http/enums/Headers.hpp"

namespace micronet {

    const std::unordered_map<int, std::string> http_status_texts = {
        {200, "OK"},
        {201, "Created"},
        {204, "No Content"},
        {400, "Bad Request"},
        {401, "Unauthorized"},
        {403, "Forbidden"},
        {404, "Not Found"},
        {405, "Method Not Allowed"},
        {408, "Request Timeout"},
        {409, "Conflict"},
        {500, "Internal Server Error"},
        {501, "Not Implemented"},
        {503, "Service Unavailable"}
    };

    Response::Response(const int code, const std::initializer_list<Header>& headers, const std::string &body) {
        this->http_version = Version::HTTP1_1;
        this->status_code = code;
        this->reason_phrase = http_status_texts.contains(code) ? http_status_texts.at(code) : "Undefined";
        this->headers.insert(this->headers.end(),headers.begin(), headers.end());
        this->body = body;

        if (!body.empty()) {
            this->headers.emplace_back(Headers::ContentLength, std::to_string(body.size()));
            if (body.starts_with('{') || body.starts_with('[')) {
                this->headers.emplace_back(Headers::ContentType, "application/json");
            }else {
                this->headers.emplace_back(Headers::ContentType, "text/plain");
            }
        }
    }

    Response Response::NotFound() {
        auto r = Response(404,{},"");
        r.body = "404 Not Found";
        r.headers.emplace_back(Headers::ContentLength, std::to_string(r.body.size()));
        return r;
    }

    std::string to_string(const Response& response) {
        std::stringstream ss;
        ss << "> " << to_string(response.http_version) << ' ' << response.status_code << ' ' << response.reason_phrase << std::endl;
        for (const auto& [key, value] : response.headers) {
            ss << ">  " << key << ": " << value << std::endl;
        }
        ss << "> " << response.body << std::endl;
        return ss.str();
    }

    constexpr auto RBrake = "\r\n";

    std::string as_response(const Response& response) {
        std::stringstream ss;
        ss << to_string(response.http_version) << " " << response.status_code << " " << response.reason_phrase << RBrake;
        for (const auto& [key, value] : response.headers) {
            ss << key << ": " << value << RBrake;
        }
        ss << RBrake;
        if (!response.body.empty()) {
            ss << response.body;
        }
        return ss.str();
    }

}
