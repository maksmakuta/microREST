#include "micronet/http/enums/Version.hpp"

namespace micronet {

    std::string to_string(const Version& version) {
        switch (version) {
            case Version::HTTP1_0:
                return "HTTP/1.0";
            case Version::HTTP1_1:
                return "HTTP/1.1";
            case Version::HTTP2:
                return "HTTP/2";
            case Version::HTTP3:
                return "HTTP/3";
            default:
                return "UNKNOWN";
        }
    }

    Version to_version(const std::string& s) {
        if (s == "HTTP/1.0") {
            return Version::HTTP1_0;
        }
        if (s == "HTTP/1.1") {
            return Version::HTTP1_1;
        }
        if (s == "HTTP/2") {
            return Version::HTTP2;
        }
        if (s == "HTTP/3") {
            return Version::HTTP3;
        }
        return Version::UNKNOWN;
    }

}
