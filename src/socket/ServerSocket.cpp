#include "micronet/socket/ServerSocket.hpp"

#include <functional>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/poll.h>

namespace micronet {

    ServerSocket::ServerSocket(const std::string& host, const int port) {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
            if (m_socket < 0) throw std::runtime_error("socket() failed");

        constexpr int opt = 1;
        setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(host.c_str());

        if (::bind(m_socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0)
            throw std::runtime_error("bind() failed");
    }

    void ServerSocket::listen(const int backlog) const {
        ::listen(m_socket,backlog);
    }

    std::unique_ptr<ClientSocket> ServerSocket::accept(int timeout_ms) const {
        pollfd pfd{};
        pfd.fd = m_socket;
        pfd.events = POLLIN;

        const int ret = ::poll(&pfd, 1, timeout_ms);
        if (ret < 0) {
            throw std::runtime_error("poll() failed");
        }

        if (ret == 0 || !(pfd.revents & POLLIN)) {
            return nullptr; // Timeout or no readable events
        }

        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int client_fd = ::accept(m_socket, reinterpret_cast<sockaddr *>(&client_addr), &len);
        if (client_fd < 0) {
            throw std::runtime_error("accept() failed");
        }

        return std::make_unique<ClientSocket>(client_fd);

    }

    void ServerSocket::close() const {
        ::close(m_socket);
    }
}
