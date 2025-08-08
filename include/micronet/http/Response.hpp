#ifndef MICRONET_RESPONSE_HPP
#define MICRONET_RESPONSE_HPP

#include <string>
#include <vector>

#include "micronet/http/Header.hpp"
#include "micronet/http/enums/Version.hpp"

namespace micronet {

    struct Response {
        std::pmr::vector<Header> headers;
        Version http_version;
        std::string reason_phrase;
        std::string body;
        int status_code;

        Response(int code, const std::initializer_list<Header>& headers, const std::string &body);

        static Response NotFound();
    };

    std::string to_string(const Response& response);
    std::string as_response(const Response& response);

}

#endif //MICRONET_RESPONSE_HPP