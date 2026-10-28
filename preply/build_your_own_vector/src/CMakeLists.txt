set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -fsanitize=address")

add_executable(test_vector tests/test_vector.cpp)
target_link_libraries(test_vector PRIVATE ${CMAKE_CXX_FLAGS})

# output to ../build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../build")
