#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

TEST(UniqueListFactory, CreateUniqueList)
{
    SegmentMerger sm;
    UniqueListFactory factory{std::make_shared<SegmentMerger>()};
    auto result = factory.create_unique_list();
    using expected_type = std::unique_ptr<UniqueList>;
    EXPECT_THAT(result, testing::A<expected_type>());
}
