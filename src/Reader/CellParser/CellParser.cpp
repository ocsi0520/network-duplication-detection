#include <string>
#include <sstream>
#include <functional>
#include <limits>
#include "CellParser.hpp"

namespace MyNetwork
{
    char CellParser::read_cell_char(std::istringstream &line_stream, bool is_required)
    {
        std::string cell;
        if (!std::getline(line_stream, cell, ',') || line_stream.bad())
            throw std::invalid_argument("expected type: char got cell: " + cell);
        std::string unqouted_cell = unquoted(cell);
        if (unqouted_cell.size() > 1)
            throw std::invalid_argument("cell is not a simple character: " + cell);
        if (is_required && unqouted_cell.size() != 1)
            throw std::invalid_argument("character required");
        if (!is_required && unqouted_cell.size() == 0)
            return '\0';

        return unqouted_cell[0];
    }
    int CellParser::read_cell_int(std::istringstream &line_stream)
    {
        std::string cell;
        if (!std::getline(line_stream, cell, ',') || line_stream.bad())
            throw std::invalid_argument("expected type: int got cell: " + cell);

        return std::stoi(cell);
    }
    std::string CellParser::read_cell_string(std::istringstream &line_stream, size_t max_chars, size_t min_chars)
    {
        std::string cell;
        if (!std::getline(line_stream, cell, ',') || line_stream.bad())
            throw std::invalid_argument("expected type: string got cell: " + cell);

        std::string unqouted_cell = unquoted(cell);
        if (unqouted_cell.size() > max_chars || unqouted_cell.size() < min_chars)
            throw std::invalid_argument{
                "expected size between: " + std::to_string(min_chars) + " - " + std::to_string(max_chars) +
                " got " + std::to_string(unqouted_cell.size())};

        return unqouted_cell;
    }
    std::string CellParser::unquoted(const std::string &a_str)
    {
        if (a_str.size() < 2 || a_str[0] != '"' || a_str[a_str.size() - 1] != '"')
            throw std::invalid_argument{"not quoted string: " + a_str};

        return std::string(a_str.begin() + 1, a_str.end() - 1);
    }
}
