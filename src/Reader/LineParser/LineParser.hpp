#pragma once
#include <string>
#include "NetworkRecord.hpp"
#include "CellParser.hpp"

namespace MyNetwork
{
    class LineParser
    {
    public:
        LineParser(CellParser&);
        NetworkRecord parse_line(const std::string &a_line);

    private:
        CellParser &cell_parser;
    };
}