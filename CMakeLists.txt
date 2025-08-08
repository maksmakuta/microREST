cmake_minimum_required(VERSION 4.0)
project(micronet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(micronet SHARED
        include/micronet/socket/ClientSocket.hpp
        include/micronet/socket/ServerSocket.hpp
        include/micronet/http/enums/Method.hpp
        include/micronet/http/enums/Version.hpp
        include/micronet/http/Request.hpp
        include/micronet/http/Response.hpp
        include/micronet/http/Router.hpp

        src/socket/ServerSocket.cpp
        src/socket/ClientSocket.cpp
        src/http/Router.cpp
        src/http/Request.cpp
        src/http/Response.cpp
        include/micronet/http/Route.hpp
        include/json.hpp
        include/micronet/http/enums/Headers.hpp
        src/http/enums/Headers.cpp
        src/http/enums/Method.cpp
        src/http/enums/Version.cpp
        include/micronet/http/Header.hpp

)
target_include_directories(micronet PUBLIC include)
add_subdirectory(example)