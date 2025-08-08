#ifndef MICRONET_ROUTE_HPP
#define MICRONET_ROUTE_HPP

#include <functional>
#include <string>

#include "micronet/http/Request.hpp"
#include "micronet/http/Response.hpp"
#include "micronet/http/enums/Method.hpp"

namespace micronet {

    struct Route {
        Method method;
        std::string path;
        std::function<Response(const Request&)> callback;
    };

}

#endif //MICRONET_ROUTE_HPP