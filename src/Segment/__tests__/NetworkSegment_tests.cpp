#include <gtest/gtest.h>
#include "NetworkSegment.hpp"
#include <stdexcept>

using MyNetwork::is_valid_parity;

TEST(NetworkSegmentTest, ReturnTrueForValidParityChars)
{

    EXPECT_EQ(is_valid_parity('O'), true);
    EXPECT_EQ(is_valid_parity('E'), true);
    EXPECT_EQ(is_valid_parity('M'), true);
}

TEST(NetworkSegmentTest, ReturnFalseForInvalidParityChars)
{
    EXPECT_EQ(is_valid_parity('\0'), false);
    EXPECT_EQ(is_valid_parity(' '), false);
    EXPECT_EQ(is_valid_parity('o'), false);
    EXPECT_EQ(is_valid_parity('e'), false);
    EXPECT_EQ(is_valid_parity('m'), false);
    EXPECT_EQ(is_valid_parity('A'), false);
    EXPECT_EQ(is_valid_parity('z'), false);
}

TEST(NetworkSegmentTest, CastValidParityChars)
{
    EXPECT_EQ(static_cast<MyNetwork::Parity>('O'), MyNetwork::Parity::Odd);
    EXPECT_EQ(static_cast<MyNetwork::Parity>('E'), MyNetwork::Parity::Even);
    EXPECT_EQ(static_cast<MyNetwork::Parity>('M'), MyNetwork::Parity::Mixed);
}