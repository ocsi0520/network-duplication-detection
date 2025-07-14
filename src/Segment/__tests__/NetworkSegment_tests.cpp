#include <gtest/gtest.h>
#include "NetworkSegment.hpp"
#include "TestSegment.hpp"
#include <sstream>
#include <string>

using namespace MyNetwork;

TEST(NetworkSegmentTest, ReturnTrueForValidParityChars)
{
    EXPECT_TRUE(is_valid_parity('O'));
    EXPECT_TRUE(is_valid_parity('E'));
    EXPECT_TRUE(is_valid_parity('M'));
}

TEST(NetworkSegmentTest, ReturnFalseForInvalidParityChars)
{
    EXPECT_FALSE(is_valid_parity('\0'));
    EXPECT_FALSE(is_valid_parity(' '));
    EXPECT_FALSE(is_valid_parity('o'));
    EXPECT_FALSE(is_valid_parity('e'));
    EXPECT_FALSE(is_valid_parity('m'));
    EXPECT_FALSE(is_valid_parity('A'));
    EXPECT_FALSE(is_valid_parity('z'));
}

TEST(NetworkSegmentTest, CastValidParityChars)
{
    EXPECT_EQ(static_cast<Parity>('O'), Parity::Odd);
    EXPECT_EQ(static_cast<Parity>('E'), Parity::Even);
    EXPECT_EQ(static_cast<Parity>('M'), Parity::Mixed);
}

TEST(NetworkSegmentTest, OstreamOperator)
{
    Segment s = create_segment(Parity::Odd, 1, 9);
    std::ostringstream oss;
    oss << s;
    std::string out = oss.str();
    EXPECT_NE(out.find("Kossuth utca"), std::string::npos);
    EXPECT_NE(out.find("O"), std::string::npos);
    EXPECT_NE(out.find("1"), std::string::npos);
    EXPECT_NE(out.find("9"), std::string::npos);
}

TEST(NetworkSegmentTest, OperatorEqualsAndNotEquals)
{
    Segment s1 = create_segment(Parity::Odd, 1, 9);
    Segment s2 = create_segment(Parity::Odd, 1, 9);
    Segment s3 = create_segment(Parity::Even, 2, 10);
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_TRUE(s1 != s3);
}

TEST(NetworkSegmentTest, OperatorLessEqual)
{
    Segment base_segment = create_segment(Parity::Odd, 1, 9);
    Segment totally_equal = create_segment(Parity::Odd, 1, 9);
    Segment greater_from = create_segment(Parity::Odd, 3, 9);
    Segment greater_to = create_segment(Parity::Odd, 1, 11);
    Segment greater_street = create_segment(Parity::Odd, 1, 7, "1045", "Petőfi utca");
    Segment greater_postal_code = create_segment(Parity::Odd, 1, 7, "1046", "Aladár utca");
    EXPECT_TRUE(base_segment <= totally_equal);
    EXPECT_TRUE(base_segment <= greater_from);
    EXPECT_TRUE(base_segment <= greater_to);
    EXPECT_TRUE(base_segment <= greater_street);
    EXPECT_TRUE(base_segment <= greater_postal_code);
    Segment less_from = create_segment(Parity::Odd, 1, 7);
    EXPECT_FALSE(base_segment <= less_from);
}

TEST(NetworkSegmentTest, OperatorLess)
{
    Segment s1 = create_segment(Parity::Odd, 1, 9);
    Segment s2 = create_segment(Parity::Odd, 1, 11);
    Segment s3 = create_segment(Parity::Odd, 1, 9);
    EXPECT_TRUE(s1 < s2);
    EXPECT_FALSE(s1 < s3);
    EXPECT_FALSE(s2 < s1);
}