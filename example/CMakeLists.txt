add_executable(microrest src/main.cpp)
target_include_directories(microrest PUBLIC include)
target_link_libraries(microrest PUBLIC micronet)