#include "gtest/gtest.h"
#include "SegmentMapper.hpp"
#include <string>

using namespace MyNetwork;

NetworkRecord create_network_record(
    std::string street_name, std::string street_type,
    char left_parity, int left_from, int left_to, std::string left_postal_code,
    char right_parity, int right_from, int right_to, std::string right_postal_code

)
{
    NetworkRecord nr;
    nr.STRET_NAME = street_name;
    nr.STRET_TYPE = street_type;

    nr.SCHEMELEFT = left_parity;
    nr.FROMLEFT = left_from;
    nr.TOLEFT = left_to;
    nr.L_POSTAL_CODE = left_postal_code;

    nr.SCHEMERIGHT = right_parity;
    nr.FROMRIGHT = right_from;
    nr.TORIGHT = right_to;
    nr.R_POSTAL_CODE = right_postal_code;

    return nr;
}

void test_left_segment(const Segment &left_segment)
{
    EXPECT_EQ(left_segment.postal_code, "1545");
    EXPECT_EQ(left_segment.STREET_NAME_AND_TYPE, "Kossuth utca");
    EXPECT_EQ(left_segment.parity, Parity::Odd);
    EXPECT_EQ(left_segment.from_street_number, 1);
    EXPECT_EQ(left_segment.to_street_number, 7);
}

void test_right_segment(const Segment &right_segment)
{
    EXPECT_EQ(right_segment.postal_code, "1546");
    EXPECT_EQ(right_segment.STREET_NAME_AND_TYPE, "Kossuth utca");
    EXPECT_EQ(right_segment.parity, Parity::Even);
    EXPECT_EQ(right_segment.from_street_number, 2);
    EXPECT_EQ(right_segment.to_street_number, 8);
}

TEST(SegmentMapper, MapValidLeftSide)
{
    SegmentMapper mapper;
    NetworkRecord left_valid_side = create_network_record(
        "Kossuth", "utca",
        'O', 1, 7, "1545",
        '\0', 0, 0, "");
    auto segments = mapper.map_from_record(left_valid_side);
    EXPECT_EQ(segments.size(), 1);
    test_left_segment(segments[0]);
}

TEST(SegmentMapper, MapValidRightSide)
{
    SegmentMapper mapper;
    NetworkRecord right_valid_side = create_network_record(
        "Kossuth", "utca",
        '\0', 0, 0, "",
        'E', 2, 8, "1546");
    auto segments = mapper.map_from_record(right_valid_side);
    EXPECT_EQ(segments.size(), 1);
    test_right_segment(segments[0]);
}

TEST(SegmentMapper, MapValidBothSide)
{

    SegmentMapper mapper;
    NetworkRecord right_valid_side = create_network_record(
        "Kossuth", "utca",
        'O', 1, 7, "1545",
        'E', 2, 8, "1546");
    auto segments = mapper.map_from_record(right_valid_side);
    EXPECT_EQ(segments.size(), 2);
    test_left_segment(segments[0]);
    test_right_segment(segments[1]);
}

TEST(SegmentMapper, MapInvalidSides)
{
    SegmentMapper mapper;
    NetworkRecord has_none_valid_segments = create_network_record(
        "Kossuth", "utca",
        '\0', 0, 0, "",
        '\0', 0, 0, "");
    auto segments = mapper.map_from_record(has_none_valid_segments);
    EXPECT_EQ(segments.size(), 0);
}