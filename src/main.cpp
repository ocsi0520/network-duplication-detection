#include <iostream>
#include "StreamReader.hpp"
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream file{"data/network_utf8.csv"};
    if (!file)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
    MyNetwork::CellParser cell_parser;
    MyNetwork::LineParser line_parser{cell_parser};
    MyNetwork::DataStreamReader reader{file, line_parser};

    auto data = reader.read_data();
    std::cout << "read data size: " << data.size() << std::endl;

    return 0;
}