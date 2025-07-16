add_library(duplication_detection STATIC SegmentMerger.cpp LocationBased/UniqueList/UniqueList.cpp)

target_include_directories(
    duplication_detection
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(duplication_detection PUBLIC segment)
target_link_libraries(network_duplication PUBLIC duplication_detection)
