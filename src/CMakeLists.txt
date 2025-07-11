
# Load test registration helper
include(${CMAKE_CURRENT_LIST_DIR}/test_helpers.cmake)

add_executable(network_duplication main.cpp)

add_subdirectory(counters)
add_subdirectory(utils)

# Register tests for each module
register_module_tests(counters ${CMAKE_CURRENT_SOURCE_DIR}/counters)
register_module_tests(utils ${CMAKE_CURRENT_SOURCE_DIR}/utils)
