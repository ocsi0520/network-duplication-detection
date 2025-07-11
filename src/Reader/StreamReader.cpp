#include "StreamReader.hpp"
#include <string>
#include <iostream>

MyNetwork::DataStreamReader::DataStreamReader(std::istream &ds, LineParser &lp) : data_stream{ds}, line_parser{lp} {};

std::vector<MyNetwork::NetworkRecord> MyNetwork::DataStreamReader::read_data()
{
    std::vector<NetworkRecord> result;
    std::string read_line;
    size_t line_count = 0;
    while (std::getline(data_stream, read_line))
    {
        line_count++;
        bool is_empty_line = read_line.size() < 3; // empty lines with LF or CRLF ending
        if (is_empty_line)
            continue;

        try
        {
            result.push_back(
                line_parser.parse_line(read_line));
        }
        catch (const std::exception &exception)
        {
            std::cout << "error at line " << line_count << ":\n"
                      << exception.what() << "\noriginal:\n"
                      << read_line << "\n";
        }
    }

    return result;
}
