#include "micronet/socket/ClientSocket.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <vector>
#include <sys/socket.h>

namespace micronet {
    ClientSocket::ClientSocket(const int fd) : m_socket {fd} {}

    std::string ClientSocket::getLine() const {
        std::string line;
        char ch;
        while (true) {
            const ssize_t n = ::recv(m_socket, &ch, 1, 0);
            if (n <= 0) break;
            line += ch;
            if (line.size() >= 2 && line.ends_with("\r\n")) break;
        }
        if (line.ends_with("\r\n"))
            line.erase(line.size() - 2);  // remove \r\n

        return line;
    }

    std::string ClientSocket::getBytes(const size_t n) const {
        std::string data;
        data.resize(n);
        size_t received = 0;
        while (received < n) {
            ssize_t r = ::recv(m_socket, &data[received], n - received, 0);
            if (r <= 0) throw std::runtime_error("recv() failed or closed");
            received += r;
        }
        return data;
    }

    void ClientSocket::send(const std::string& data) const {
        size_t total = 0;
        while (total < data.size()) {
            const ssize_t sent = ::send(m_socket, data.data() + total, data.size() - total, 0);
            if (sent <= 0) throw std::runtime_error("send() failed");
            total += sent;
        }
    }

    void ClientSocket::close() const {
        ::close(m_socket);
    }

    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string current;
        std::istringstream stream(str);

        while (std::getline(stream, current, delimiter)) {
            tokens.push_back(current);
        }

        return tokens;
    }

    Request ClientSocket::getRequest() const {
        Request req{};

        if (const auto header = getLine(); !header.empty()) {
            const auto words = split(header, ' ');
            if (words.size() == 3) {
                req.method = to_method(words[0]);
                req.path = words[1];
                req.http_version = to_version(words[2]);
            } else {
                std::cerr << "Invalid request header: " << header << std::endl;
                return {};
            }
        }

        while (true) {
            const auto line = getLine();
            if (!line.empty()) {
                const auto words = split(line, ':');
                if (!words.empty()) {
                    std::string key = words[0];
                    std::string value;
                    for (size_t i = 1; i < words.size(); ++i) {
                        if (i > 1) value += ":";
                        value += words[i];
                    }
                    req.headers.emplace_back(key, value);
                }
            }else {
                break;
            }
        }

        const auto it = std::ranges::find_if(req.headers,[](const Header& h) {
            return h.key == to_string(Headers::ContentLength);
        });
        if (it != req.headers.end()) {
            const int content_length = std::stoi(it->value);
            req.body = getBytes(content_length);
        }

        return req;
    }
}
