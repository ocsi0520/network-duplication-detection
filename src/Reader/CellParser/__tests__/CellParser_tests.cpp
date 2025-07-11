#include <gtest/gtest.h>
#include "CellParser.hpp"
#include <sstream>
#include <exception>
#include <string>

TEST(CellParserTest, ReadCharFromEmptyLine)
{
    MyNetwork::CellParser cp;
    std::istringstream empty_stream{""};
    try
    {
        cp.read_cell_char(empty_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "expected type: char got cell: ");
    }
}

TEST(CellParserTest, ReadCharFromUnqoutedChar)
{
    MyNetwork::CellParser cp;
    std::istringstream unqouted_char{"a"};
    try
    {
        cp.read_cell_char(unqouted_char);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "not quoted string: a");
    }
}

TEST(CellParserTest, ReadCharFromNonCharLine)
{
    MyNetwork::CellParser cp;
    std::istringstream multiple_chars{"\"ab\""};
    try
    {
        cp.read_cell_char(multiple_chars);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "cell is not a simple character: \"ab\"");
    }
}

TEST(CellParserTest, ReadCharFromMissingEndQuotion)
{
    MyNetwork::CellParser cp;
    std::istringstream missing_closing_quotion{"\"a"};
    try
    {
        cp.read_cell_char(missing_closing_quotion);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "not quoted string: \"a");
    }
}

TEST(CellParserTest, ReadCharFromMissingStartingQuotion)
{
    MyNetwork::CellParser cp;
    std::istringstream missing_closing_quotion{"a\""};
    try
    {
        cp.read_cell_char(missing_closing_quotion);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "not quoted string: a\"");
    }
}

TEST(CellParserTest, ReadRequiredCharFromEmpty)
{
    MyNetwork::CellParser cp;
    std::istringstream empty_line{"\"\""};
    try
    {
        cp.read_cell_char(empty_line, true);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "character required");
    }
}

TEST(CellParserTest, ReadOptionalCharFromEmpty)
{
    MyNetwork::CellParser cp;
    std::istringstream empty_line{"\"\""};
    EXPECT_EQ(cp.read_cell_char(empty_line), '\0');
}

TEST(CellParserTest, ReadCharProperly)
{
    MyNetwork::CellParser cp;
    std::istringstream missing_starting_quotion{"\"a\""};
    EXPECT_EQ(cp.read_cell_char(missing_starting_quotion), 'a');
}

TEST(CellParserTest, ReadNegativeInt)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"-123"};
    EXPECT_EQ(cp.read_cell_int(line_stream), -123);
}

TEST(CellParserTest, Read0)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"0"};
    EXPECT_EQ(cp.read_cell_int(line_stream), 0);
}

TEST(CellParserTest, ReadPositiveInt)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"987"};
    EXPECT_EQ(cp.read_cell_int(line_stream), 987);
}

TEST(CellParserTest, ReadDouble)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"999.999"};
    EXPECT_EQ(cp.read_cell_int(line_stream), 999);
}

TEST(CellParserTest, ReadIntFromEmpty)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{""};
    try
    {
        cp.read_cell_int(line_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "expected type: int got cell: ");
    }
}

TEST(CellParserTest, ReadIntFromGibberish)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"asd"};
    try
    {
        cp.read_cell_int(line_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "stoi");
    }
}

TEST(CellParserTest, ReadStringFromEmpty)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{""};
    try
    {
        cp.read_cell_string(line_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "expected type: string got cell: ");
    }
}

TEST(CellParserTest, ReadEmptyString)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"\"\""};
    EXPECT_STREQ(cp.read_cell_string(line_stream).c_str(), "");
}

TEST(CellParserTest, ReadProperString)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"\"asd asd\""};
    EXPECT_STREQ(cp.read_cell_string(line_stream).c_str(), "asd asd");
}

TEST(CellParserTest, ReadStringFromMissingStartingQuotion)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"asd asd\""};
    try
    {
        cp.read_cell_string(line_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "not quoted string: asd asd\"");
    }
}

TEST(CellParserTest, ReadStringFromMissingEndingQuotion)
{
    MyNetwork::CellParser cp;
    std::istringstream line_stream{"\"asd asd"};
    try
    {
        cp.read_cell_string(line_stream);
        throw std::logic_error{"It should have thrown an error"};
    }
    catch (std::invalid_argument &ia)
    {
        EXPECT_STREQ(ia.what(), "not quoted string: \"asd asd");
    }
}