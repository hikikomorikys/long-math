cmake_minimum_required(VERSION 3.10)
project(long-math)

set(CMAKE_CXX_STANDARD 17)

add_library(LongNumber STATIC longnumber.cpp)

add_executable(run_tests tests.cpp)
target_link_libraries(run_tests PRIVATE LongNumber)

add_executable(pi_calculator main.cpp pi.cpp)
target_link_libraries(pi_calculator PRIVATE LongNumber)

enable_testing()
add_test(NAME LongNumberTests COMMAND run_tests)
add_custom_target(test COMMAND ctest --output-on-failure)
