#include <gtest/gtest.h>
#include "counter.hpp"
#include <sstream>

TEST(ACounterTest, CountFiveInAWord)
{
    EXPECT_EQ(count_letter_a("abracadabra"), 5);
}

TEST(ACounterTest, CountFiveInASentence)
{
    EXPECT_EQ(count_letter_a("abra ca dabra."), 5);
}
