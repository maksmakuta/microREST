#ifndef MICRONET_SERVERSOCKET_HPP
#define MICRONET_SERVERSOCKET_HPP

#include <memory>

#include "ClientSocket.hpp"

namespace micronet {

    class ServerSocket {
    public:
        ServerSocket(const std::string& host, int port);
        void listen(int backlog = 128) const;
        [[nodiscard]] std::unique_ptr<ClientSocket> accept(int timeout_ms = 1000) const;

        void close() const;

    private:
        int m_socket{-1};
    };

}


#endif //MICRONET_SERVERSOCKET_HPP