# Load test registration helper
include(${CMAKE_CURRENT_SOURCE_DIR}/test_helpers.cmake)

add_library(solution STATIC solution.cpp)

include_directories(solution PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Reader)
add_subdirectory(Segment)
add_subdirectory(DuplicationDetection)

# Register tests for each module
register_module_tests(reader ${CMAKE_CURRENT_SOURCE_DIR}/Reader)
register_module_tests(segment ${CMAKE_CURRENT_SOURCE_DIR}/Segment)
register_module_tests(duplication_detection ${CMAKE_CURRENT_SOURCE_DIR}/DuplicationDetection ${CMAKE_CURRENT_SOURCE_DIR}/Segment)

# e2e tests
add_executable(solution_e2e_tests ./__tests__/solution_e2e_tests.cpp)

target_compile_options(solution_e2e_tests PRIVATE --coverage)
target_link_options(solution_e2e_tests PRIVATE --coverage)

target_link_libraries(
    solution_e2e_tests
    PRIVATE
    solution
    GTest::gtest_main
)
add_test(NAME solution_e2e_tests COMMAND solution_e2e_tests)
set_tests_properties(solution_e2e_tests PROPERTIES LABELS main_e2e)

# main
add_executable(network_duplication main.cpp)
target_link_libraries(network_duplication
    PRIVATE
    solution
)
