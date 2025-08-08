#include "micronet/http/enums/Headers.hpp"

#include <vector>

namespace micronet {

    std::string to_string(const Headers& h) {
        return std::vector{
            "Connection", "Date", "Host", "User-Agent", "Accept", "Accept-Encoding", "Content-Length", "Content-Type", "UNKNOWN"
        }[static_cast<int>(h)];
    }

    Headers to_header(const std::string& str) {
        if (str == "Connection"){
            return Headers::Connection;
        }
        if (str == "Date"){
            return Headers::Date;
        }
        if (str == "Host"){
            return Headers::Host;
        }
        if (str == "User-Agent"){
            return Headers::UserAgent;
        }
        if (str == "Accept"){
            return Headers::Accept;
        }
        if (str == "Accept-Encoding"){
            return Headers::AcceptEncoding;
        }
        if (str == "Content-Length"){
            return Headers::ContentLength;
        }
        if (str == "Content-Type"){
            return Headers::ContentType;
        }
        return Headers::UNKNOWN;
    }


}
