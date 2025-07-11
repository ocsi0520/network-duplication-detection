# Load test registration helper
include(${CMAKE_CURRENT_SOURCE_DIR}/test_helpers.cmake)

add_executable(network_duplication main.cpp)

include_directories(network_duplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(counters)
add_subdirectory(utils)
add_subdirectory(Reader)

# Register tests for each module
register_module_tests(counters ${CMAKE_CURRENT_SOURCE_DIR}/counters)
register_module_tests(utils ${CMAKE_CURRENT_SOURCE_DIR}/utils)
register_module_tests(reader ${CMAKE_CURRENT_SOURCE_DIR}/Reader)
