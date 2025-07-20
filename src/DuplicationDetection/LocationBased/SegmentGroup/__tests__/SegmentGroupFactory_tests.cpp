#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"

using namespace MyNetwork;

TEST(SegmentGroupFactory, createGroup)
{
    SegmentMerger sm;
    UniqueListFactory ul_f{sm};
    SegmentGroupFactory factory{ul_f};

    auto result = factory.create_group();
    EXPECT_THAT(result, testing::A<SegmentGroup>());
}