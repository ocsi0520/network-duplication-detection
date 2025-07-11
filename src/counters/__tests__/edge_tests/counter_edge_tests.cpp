#include <gtest/gtest.h>
#include "counter.hpp"
#include <sstream>

TEST(ACounterTest, HandlesEmptyInput)
{
    EXPECT_EQ(count_letter_a(""), 0);
}

TEST(ACounterTest, HandlesOneChar)
{
    EXPECT_EQ(count_letter_a(""), 0);
}

TEST(ACounterTest, HandlesOneA)
{
    EXPECT_EQ(count_letter_a("a"), 1);
}

TEST(ACounterTest, HandlesOneNonA)
{
    EXPECT_EQ(count_letter_a("b"), 0);
}