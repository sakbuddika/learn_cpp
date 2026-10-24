cmake_minimum_required(VERSION 3.28)
project(build_your_own_vector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wpedantic -g -fsanitize=address,undefined")

set(CMAKE_CXX_COMPILER "gcc")

set(SOURCE_FILES tests/test_vector.cpp)

add_executable(test_vector ${SOURCE_FILES})
