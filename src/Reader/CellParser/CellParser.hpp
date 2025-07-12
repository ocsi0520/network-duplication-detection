#pragma once
#include <string>
#include <limits>

namespace MyNetwork
{
    class CellParser
    {
    public:
        char read_cell_char(std::istringstream &line_stream, bool is_required = false);
        int read_cell_int(std::istringstream &line_stream);
        std::string read_cell_string(std::istringstream &line_stream, size_t max_chars = std::numeric_limits<size_t>::max(), size_t min_chars = 0);

    private:
        inline std::string unquoted(const std::string &a_str);
    };
}
