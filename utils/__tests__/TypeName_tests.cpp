#include <gtest/gtest.h>
#include "TypeName.hpp"
#include <string>

TEST(ACounterTest, HandleStringValue)
{
    ASSERT_STREQ(get_type_name(std::string{"asd"}), "string");
}

TEST(ACounterTest, HandleIntValue)
{
    int a = 5;
    ASSERT_STREQ(get_type_name(a), "int");
    ASSERT_STREQ(get_type_name(5), "int");
}


TEST(ACounterTest, HandleValueWithFallback)
{
    ASSERT_STREQ(get_type_name(5.2f), "f");
}

