set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined")
set(CMAKE_CXX_STANDARD 17)

add_executable(run_tests tests/test_vector.cpp)
target_include_directories(run_tests PRIVATE include)



