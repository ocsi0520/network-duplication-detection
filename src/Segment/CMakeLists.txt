add_library(segment STATIC SegmentMapper.cpp NetworkSegment.cpp)

target_include_directories(
    segment
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(network_duplication PUBLIC segment)
