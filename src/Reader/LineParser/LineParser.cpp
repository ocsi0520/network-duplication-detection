#include "LineParser.hpp"
#include <string>
#include <sstream>
#include <functional>
#include <limits>
#include <iostream>

namespace MyNetwork
{
    LineParser::LineParser(CellParser &cp) : cell_parser{cp} {};
    NetworkRecord LineParser::parse_line(const std::string &a_line)
    {
        std::istringstream line_stream{a_line};
        NetworkRecord nw;

        nw.ID = cell_parser.read_cell_int(line_stream);
        nw.FROM_NODE = cell_parser.read_cell_int(line_stream);
        nw.TO_NODE = cell_parser.read_cell_int(line_stream);
        nw.FRC_A = cell_parser.read_cell_string(line_stream);
        nw.FOW = cell_parser.read_cell_int(line_stream);
        nw.ONEWAY = cell_parser.read_cell_string(line_stream);
        nw.STRUCTURE = cell_parser.read_cell_char(line_stream);
        nw._not_documented_1 = cell_parser.read_cell_int(line_stream);
        nw.TOLL = cell_parser.read_cell_char(line_stream);
        nw.VTR = cell_parser.read_cell_string(line_stream);
        nw.SPEED_LIMIT = cell_parser.read_cell_int(line_stream);
        nw.SPEED_LIMIT_VALID = cell_parser.read_cell_int(line_stream);
        nw.KPH = cell_parser.read_cell_int(line_stream);
        nw.FROM_LEVEL = cell_parser.read_cell_int(line_stream);
        nw.TO_LEVEL = cell_parser.read_cell_int(line_stream);
        nw._not_documented_2 = cell_parser.read_cell_int(line_stream);
        nw.STRET_NAME = cell_parser.read_cell_string(line_stream);
        nw.STRET_TYPE = cell_parser.read_cell_string(line_stream);
        nw.ROAD_NAME = cell_parser.read_cell_string(line_stream);
        nw.ALT_NAME = cell_parser.read_cell_string(line_stream);
        nw.SCHEMELEFT = cell_parser.read_cell_char(line_stream);
        nw.FROMLEFT = cell_parser.read_cell_int(line_stream);
        nw.TOLEFT = cell_parser.read_cell_int(line_stream);
        nw.SCHEMERIGHT = cell_parser.read_cell_char(line_stream);
        nw.FROMRIGHT = cell_parser.read_cell_int(line_stream);
        nw.TORIGHT = cell_parser.read_cell_int(line_stream);
        nw.L_ORDER8_NAME = cell_parser.read_cell_string(line_stream);
        nw.R_ORDER8_NAME = cell_parser.read_cell_string(line_stream);
        nw.L_ORDER9_NAME = cell_parser.read_cell_string(line_stream);
        nw.R_ORDER9_NAME = cell_parser.read_cell_string(line_stream);
        nw.ADMINIDX_L = cell_parser.read_cell_int(line_stream);
        nw.ADMINIDX_R = cell_parser.read_cell_int(line_stream);
        nw.L_POSTAL_CODE = cell_parser.read_cell_string(line_stream);
        nw.R_POSTAL_CODE = cell_parser.read_cell_string(line_stream);

        return nw;
    }
}