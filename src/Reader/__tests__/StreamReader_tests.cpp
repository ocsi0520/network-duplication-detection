#include <gtest/gtest.h>
#include "StreamReader.hpp"
#include <istream>

TEST(StreamReaderTest, ReadSomeRecord)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};
    std::istringstream string_stream{
        "515968,10986,390897,\"4\",3,\"\",\"\",110,\"F\",\"NNNNNNN\",50,0,45,0,0,0,\"Budaörsi\",\"út\",\"1\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XI. kerület\",\"XI. kerület\",3352,3352,\"0\",\"0\""
        "\r\n"
        "135061,22785,108177,\"7\",3,\"\",\"\",108,\"F\",\"NNNNNNN\",50,0,22,0,0,0,\"Kamaraerdei\",\"út\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XXII. kerület\",\"XI. kerület\",3363,3352,\"0\",\"0\""
        "\n"
        "\r"
        "515992,108205,391193,\"7\",3,\"\",\"\",126,\"F\",\"NNNNNNN\",50,0,22,0,0,0,\"Felsõörsöd\",\"utca\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XI. kerület\",\"XI. kerület\",3352,3352,\"0\",\"0\""};
    MyNetwork::DataStreamReader stream_reader{string_stream, line_parser};

    auto data = stream_reader.read_data();

    EXPECT_EQ(data.size(), 3);
}

TEST(StreamReaderTest, ReadNoneFromEmptyStringStream)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};
    std::istringstream string_stream{""};
    MyNetwork::DataStreamReader stream_reader{string_stream, line_parser};

    auto data = stream_reader.read_data();

    EXPECT_EQ(data.size(), 0);
}

TEST(StreamReaderTest, ReadNoneFromEmptyStream)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};
    std::istringstream string_stream{};
    MyNetwork::DataStreamReader stream_reader{string_stream, line_parser};
    auto data = stream_reader.read_data();

    EXPECT_EQ(data.size(), 0);
}

TEST(StreamReaderTest, HandleInvalidDataBySkipping)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};
    std::istringstream string_stream{
        // 4th param should be "4", but changed to number
        "515968,10986,390897,4,3,\"\",\"\",110,\"F\",\"NNNNNNN\",50,0,45,0,0,0,\"Budaörsi\",\"út\",\"1\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XI. kerület\",\"XI. kerület\",3352,3352,\"0\",\"0\""
        "\r\n"
        // ID is string
        "\"135061\",22785,108177,\"7\",3,\"\",\"\",108,\"F\",\"NNNNNNN\",50,0,22,0,0,0,\"Kamaraerdei\",\"út\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XXII. kerület\",\"XI. kerület\",3363,3352,\"0\",\"0\""
        "\n"
        "\r"
        // still valid line
        "515992,108205,391193,\"7\",3,\"\",\"\",126,\"F\",\"NNNNNNN\",50,0,22,0,0,0,\"Felsõörsöd\",\"utca\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XI. kerület\",\"XI. kerület\",3352,3352,\"0\",\"0\""};
    MyNetwork::DataStreamReader stream_reader{string_stream, line_parser};
    auto data = stream_reader.read_data();

    EXPECT_EQ(data.size(), 1);
}
