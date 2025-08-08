#ifndef MICRONET_HTTPMETHOD_HPP
#define MICRONET_HTTPMETHOD_HPP

#include <string>

namespace micronet {

    enum class Method {
        GET,
        PUT,
        POST,
        HEAD,
        PATCH,
        DELETE,
        OPTIONS,
        UNKNOWN
    };

    std::string to_string(const Method &method);
    Method to_method(const std::string&);

}

#endif //MICRONET_HTTPMETHOD_HPP