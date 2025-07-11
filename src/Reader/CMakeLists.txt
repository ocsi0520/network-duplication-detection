add_library(reader STATIC LineParser/LineParser.cpp CellParser/CellParser.cpp)

target_include_directories(
    reader
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/LineParser
    ${CMAKE_CURRENT_SOURCE_DIR}/CellParser
)

target_link_libraries(network_duplication PUBLIC reader)