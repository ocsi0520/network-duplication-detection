#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"

using namespace MyNetwork;

TEST(SegmentGroupFactory, createGroup)
{
    std::shared_ptr<UniqueListFactory> ul_f_pointer =
        std::make_shared<UniqueListFactory>(std::make_shared<SegmentMerger>());

    SegmentGroupFactory factory{ul_f_pointer};

    auto result = factory.create_group();
    using expected_type = std::unique_ptr<SegmentGroup>;
    EXPECT_THAT(result, testing::A<expected_type>());
}