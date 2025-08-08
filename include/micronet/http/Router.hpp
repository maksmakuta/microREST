#ifndef MICRONET_ROUTER_HPP
#define MICRONET_ROUTER_HPP

#include <functional>
#include <string>

#include "micronet/http/Route.hpp"
#include "micronet/http/Request.hpp"
#include "micronet/http/Response.hpp"
#include "micronet/http/enums/Method.hpp"
#include "micronet/socket/ServerSocket.hpp"

namespace micronet {

    class Router {
    public:
        explicit Router(int port);
        Router(const std::string& host, int port);

        Router& route(const Method& m, const std::string& path, const std::function<Response(const Request&)>& callback);
        void serve() const;

    private:

        void handleClient(const std::unique_ptr<ClientSocket> &client) const;
        [[nodiscard]] Response process(const Request& request) const;

        ServerSocket m_server;
        std::vector<Route> m_routes;
    };

}


#endif //MICRONET_ROUTER_HPP