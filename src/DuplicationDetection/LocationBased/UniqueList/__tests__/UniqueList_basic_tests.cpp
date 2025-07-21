#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"

TEST(UniqueListTest, AddToEmpty)
{
    UniqueList ul{std::make_shared<SegmentMerger>()};
    ul.add_segment(create_same_type_segment(5, 7));
    EXPECT_TRUE(ul.get_all_duplications().empty());
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, AddSameTwice)
{
    UniqueList ul{std::make_shared<SegmentMerger>()};
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    test_list(ul.get_all_duplications(), {{5, 7}});
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, AddSameThrice)
{
    UniqueList ul{std::make_shared<SegmentMerger>()};
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    test_list(ul.get_all_duplications(), {{5, 7}});
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, TestBaseTestList)
{
    UniqueList ul = get_base_test_list();
    test_list(ul.get_all_traversed(), initial_intervals);

    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, IncludeEverything)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(11, 131));
    test_list(ul.get_all_traversed(), {{11, 131}});
    test_list(ul.get_all_duplications(), initial_intervals);
}
