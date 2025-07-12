#pragma once
// TODO: next iteration w/ any container type which has forward_iterator
// #include <iterator>
// #include <ranges>
#include <vector>
#include <istream>
#include "NetworkRecord.hpp"
#include "LineParser.hpp"

namespace MyNetwork
{
    class DataStreamReader
    {
    public:
        DataStreamReader(std::istream &, LineParser &);
        std::vector<NetworkRecord> read_data();

    private:
        std::istream &data_stream;
        LineParser &line_parser;
    };
}
