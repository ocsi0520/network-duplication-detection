#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"

TEST(UniqueListTest, InsertAfterEnd)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(131, 145));
    test_list(ul.get_all_traversed(), concat(initial_intervals, {{131, 145}}));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertAfterEndAdjacent)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(121, 145));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

////////////

TEST(UniqueListTest, InsertAfterEndTangent)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(119, 145));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    test_list(ul.get_all_duplications(), {{119, 119}});
}

TEST(UniqueListTest, InsertAfterEndOverlap)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(109, 145));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    test_list(ul.get_all_duplications(), {{109, 119}});
}

TEST(UniqueListTest, InsertAfterEndFullContain)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(97, 145));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{97, 145}}));
    test_list(ul.get_all_duplications(), {{105, 119}});
}

TEST(UniqueListTest, InsertBeforeEndAdjacent)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(95, 103));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95,119}}));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeEndTangent)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(95, 105));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95,119}}));
    test_list(ul.get_all_duplications(), {{105, 105}});
}

TEST(UniqueListTest, InsertBeforeEndOverlap)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(95, 111));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95,119}}));
    test_list(ul.get_all_duplications(), {{105, 111}});
}

TEST(UniqueListTest, InsertEndFullContain)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(101, 131));
    test_list(ul.get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{101,131}}));
    test_list(ul.get_all_duplications(), {{105, 119}});
}

TEST(UniqueListTest, InsertBeforeEndFullContain3)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(37, 131));
    test_list(ul.get_all_traversed(), {initial_intervals[0], {37, 131}});
    test_list(ul.get_all_duplications(), slice(initial_intervals, 1));
}
