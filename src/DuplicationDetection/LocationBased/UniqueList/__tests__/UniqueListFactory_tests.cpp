#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

TEST(UniqueListFactory, CreateUniqueList)
{
    SegmentMerger sm;
    UniqueListFactory factory{sm};
    auto result = factory.create_unique_list();
    EXPECT_THAT(result, testing::A<UniqueList>());
}
