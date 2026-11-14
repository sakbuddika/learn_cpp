cmake_minimum_required(VERSION 3.28)
project(build_your_own_vector CXX)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -g -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)


add_subdirectory(include)
add_subdirectory(tests)
