cmake_minimum_required(VERSION 3.0)
project(float_repr)

set(CMAKE_CXX_STANDARD 17)

add_library(utils utils.cpp)
target_compile_options(utils PUBLIC -m64 -O1 -fwrapv -g -Werror -Wall -Wextra
        -Wwrite-strings -Wno-unused-parameter -Wno-cast-function-type -Wno-bool-operation)
target_link_libraries(utils PUBLIC m)

add_executable(float2bits float2bits.cpp)
target_link_libraries(float2bits utils)

add_executable(float2double float2double.cpp)
target_link_libraries(float2double utils)
