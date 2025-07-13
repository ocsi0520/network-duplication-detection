# Load test registration helper
include(${CMAKE_CURRENT_SOURCE_DIR}/test_helpers.cmake)

add_executable(network_duplication main.cpp)

include_directories(network_duplication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Reader)
add_subdirectory(Segment)
add_subdirectory(DuplicationDetection)

# Register tests for each module
register_module_tests(reader ${CMAKE_CURRENT_SOURCE_DIR}/Reader)
register_module_tests(segment ${CMAKE_CURRENT_SOURCE_DIR}/Segment)
register_module_tests(duplication_detection ${CMAKE_CURRENT_SOURCE_DIR}/DuplicationDetection)
