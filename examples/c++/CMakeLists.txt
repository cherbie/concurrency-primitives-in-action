cmake_minimum_required(VERSION 3.10)
project(ConcurrencyExamples)

# reference: http://google.github.io/googletest/quickstart-cmake.html

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../packages/googletest ./packages/googletest)

# Add your test files
add_executable(test_examples tests/test_main.cpp
                             tests/mutex.cpp
                             tests/barrier.cpp
                             tests/atomic.cpp)
target_include_directories(test_examples PUBLIC include)
target_link_libraries(test_examples GTest::gtest_main
                                    pthread) # pthread for Linux, may vary on other platforms

enable_testing()
gtest_discover_tests(test_examples)