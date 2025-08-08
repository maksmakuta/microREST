#ifndef MICRONET_REQUEST_HPP
#define MICRONET_REQUEST_HPP

#include <string>
#include <vector>

#include "micronet/http/Header.hpp"
#include "micronet/http/enums/Method.hpp"
#include "micronet/http/enums/Version.hpp"

namespace micronet {

    struct Request {
        Method method;
        Version http_version;
        std::string path;
        std::vector<Header> headers;
        std::string body;
    };

    std::string to_string(const Request& request);

}

#endif //MICRONET_REQUEST_HPP