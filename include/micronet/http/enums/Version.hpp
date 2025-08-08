#ifndef MICRONET_HTTPVERSION_HPP
#define MICRONET_HTTPVERSION_HPP

#include <string>

namespace micronet {

    enum class Version {
        HTTP1_0,
        HTTP1_1,
        HTTP2,
        HTTP3,
        UNKNOWN
    };

    std::string to_string(const Version& version);
    Version to_version(const std::string&);

}

#endif //MICRONET_HTTPVERSION_HPP