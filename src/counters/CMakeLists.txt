add_library(counters STATIC counter.cpp)
target_include_directories(counters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(network_duplication PUBLIC counters)