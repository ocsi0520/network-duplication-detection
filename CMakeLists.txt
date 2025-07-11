cmake_minimum_required(VERSION 3.28.0)
project(network_duplication VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(network_duplication main.cpp)

# Enable testing
include(CTest)
enable_testing()

# GoogleTest via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add module directories
add_subdirectory(counters)
add_subdirectory(utils)

# Load test registration helper
include(${CMAKE_CURRENT_LIST_DIR}/test_helpers.cmake)

# Register tests for each module
register_module_tests(counters ${CMAKE_SOURCE_DIR}/counters)
register_module_tests(utils ${CMAKE_SOURCE_DIR}/utils)
