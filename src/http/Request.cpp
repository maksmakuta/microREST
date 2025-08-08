#include "micronet/http/Request.hpp"

#include <sstream>
#include <vector>

namespace micronet {

    std::string to_string(const Request& request) {
        std::stringstream ss;
        ss << "< " << to_string(request.method) << " " << request.path << ' ' << to_string(request.http_version) << std::endl;
        for (const auto& [key, value] : request.headers) {
            ss << "<  " << key << ": " << value << std::endl;
        }
        if (!request.body.empty()) {
            ss << "< " << request.body << std::endl;
        }
        return ss.str();
    }

}
