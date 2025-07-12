#include <gtest/gtest.h>
#include "LineParser.hpp"
#include <string>

void assert_135061_record(const MyNetwork::NetworkRecord &nw)
{
    EXPECT_EQ(nw.ID, 135061);
    EXPECT_EQ(nw.FROM_NODE, 22785);
    EXPECT_EQ(nw.TO_NODE, 108177);
    EXPECT_EQ(nw.FRC_A, "7");
    EXPECT_EQ(nw.FOW, 3);
    EXPECT_EQ(nw.ONEWAY, "");
    EXPECT_EQ(nw.STRUCTURE, '\0');
    EXPECT_EQ(nw._not_documented_1, 108);
    EXPECT_EQ(nw.TOLL, 'F');
    EXPECT_EQ(nw.VTR, "NNNNNNN");
    EXPECT_EQ(nw.SPEED_LIMIT, 50);
    EXPECT_EQ(nw.SPEED_LIMIT_VALID, 0);
    EXPECT_EQ(nw.KPH, 22);
    EXPECT_EQ(nw.FROM_LEVEL, 0);
    EXPECT_EQ(nw.TO_LEVEL, 0);
    EXPECT_EQ(nw._not_documented_2, 0);
    EXPECT_EQ(nw.STRET_NAME, "Kamaraerdei");
    EXPECT_EQ(nw.STRET_TYPE, "út");
    EXPECT_EQ(nw.ROAD_NAME, "");
    EXPECT_EQ(nw.ALT_NAME, "");
    EXPECT_EQ(nw.SCHEMELEFT, '\0');
    EXPECT_EQ(nw.FROMLEFT, 0);
    EXPECT_EQ(nw.TOLEFT, 0);
    EXPECT_EQ(nw.SCHEMERIGHT, '\0');
    EXPECT_EQ(nw.FROMRIGHT, 0);
    EXPECT_EQ(nw.TORIGHT, 0);
    EXPECT_EQ(nw.L_ORDER8_NAME, "Budapest");
    EXPECT_EQ(nw.R_ORDER8_NAME, "Budapest");
    EXPECT_EQ(nw.L_ORDER9_NAME, "XXII. kerület");
    EXPECT_EQ(nw.R_ORDER9_NAME, "XI. kerület");
    EXPECT_EQ(nw.ADMINIDX_L, 3363);
    EXPECT_EQ(nw.ADMINIDX_R, 3352);
    EXPECT_EQ(nw.L_POSTAL_CODE, "0");
    EXPECT_EQ(nw.R_POSTAL_CODE, "0");
}

TEST(LineParserTest, ReadLineWithoutNewLine)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};

    MyNetwork::NetworkRecord nw = line_parser.parse_line(
        "135061,22785,108177,\"7\",3,\"\",\"\",108,\"F\",\"NNNNNNN\",50,0,22,0,0,0,"
        "\"Kamaraerdei\",\"út\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XXII. kerület\","
        "\"XI. kerület\",3363,3352,\"0\",\"0\"");

    assert_135061_record(nw);
}

TEST(LineParserTest, ReadLineWithNewLine)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};

    MyNetwork::NetworkRecord nw = line_parser.parse_line(
        "135061,22785,108177,\"7\",3,\"\",\"\",108,\"F\",\"NNNNNNN\",50,0,22,0,0,0,"
        "\"Kamaraerdei\",\"út\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XXII. kerület\","
        "\"XI. kerület\",3363,3352,\"0\",\"0\"\r\n");

    assert_135061_record(nw);
}

TEST(LineParserTest, ReadLineWithGibberishAtTheEnd)
{
    MyNetwork::CellParser cp;
    MyNetwork::LineParser line_parser{cp};

    MyNetwork::NetworkRecord nw = line_parser.parse_line(
        "135061,22785,108177,\"7\",3,\"\",\"\",108,\"F\",\"NNNNNNN\",50,0,22,0,0,0,"
        "\"Kamaraerdei\",\"út\",\"\",\"\",\"\",0,0,\"\",0,0,\"Budapest\",\"Budapest\",\"XXII. kerület\","
        "\"XI. kerület\",3363,3352,\"0\",\"0\"\nasd\r\nasd"
        "blabla");

    assert_135061_record(nw);
}
