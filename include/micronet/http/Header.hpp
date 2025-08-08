#ifndef MICRONET_HEADER_HPP
#define MICRONET_HEADER_HPP

#include <string>

#include "enums/Headers.hpp"

namespace micronet {

    struct Header {
        std::string key;
        std::string value;

        Header(std::string k, std::string v) : key(std::move(k)), value(std::move(v)) {}
        Header(const Headers& k, std::string v) : key(to_string(k)), value(std::move(v)) {}
    };

}

#endif //MICRONET_HEADER_HPP