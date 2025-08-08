#ifndef MICRONET_CLIENTSOCKET_HPP
#define MICRONET_CLIENTSOCKET_HPP

#include <string>

#include "micronet/http/Request.hpp"

namespace micronet {

    class ClientSocket {
    public:
        explicit ClientSocket(int fd);

        [[nodiscard]] std::string getLine() const;
        [[nodiscard]] std::string getBytes(size_t n) const;

        void send(const std::string&) const;
        void close() const;

        [[nodiscard]] Request getRequest() const;
    private:
        int m_socket{-1};
    };

}

#endif //MICRONET_CLIENTSOCKET_HPP