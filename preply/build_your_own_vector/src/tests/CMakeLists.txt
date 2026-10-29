add_executable(run_tests)
target_sources(run_tests PRIVATE test_vector.cpp)

target_include_directories(run_tests PRIVATE ../include)

target_link_libraries(run_tests PRIVATE vector)


