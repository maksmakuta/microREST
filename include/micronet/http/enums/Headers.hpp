#ifndef MICRONET_HEADERS_HPP
#define MICRONET_HEADERS_HPP

#include <string>

namespace micronet {

    //Here only base headers, you can add more if you want
    enum class Headers {
        Connection,
        Date,
        Host,
        UserAgent,
        Accept,
        AcceptEncoding,
        ContentLength,
        ContentType,
        UNKNOWN
    };

    std::string to_string(const Headers&);
    Headers to_header(const std::string&);

}

#endif //MICRONET_HEADERS_HPP