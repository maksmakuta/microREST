#include "micronet/http/enums/Method.hpp"

#include <vector>

namespace micronet {

    std::string to_string(const Method &method) {
        return std::pmr::vector{
            "GET", "PUT", "POST", "HEAD", "PATCH", "DELETE", "OPTIONS", "UNKNOWN"
        }[static_cast<int>(method)];
    }

    Method to_method(const std::string& s) {
        if (s == "GET"){
            return Method::GET;
        }
        if (s == "PUT"){
            return Method::PUT;
        }
        if (s == "POST"){
            return Method::POST;
        }
        if (s == "HEAD"){
            return Method::HEAD;
        }
        if (s == "PATCH"){
            return Method::PATCH;
        }
        if (s == "DELETE"){
            return Method::DELETE;
        }
        if (s == "OPTIONS"){
            return Method::OPTIONS;
        }
        return Method::UNKNOWN;
    }

}
