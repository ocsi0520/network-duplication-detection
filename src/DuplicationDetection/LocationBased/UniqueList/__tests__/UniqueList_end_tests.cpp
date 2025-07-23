#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"

TEST(UniqueListTest, InsertAfterEnd)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(131, 145));
    test_list(ul_pointer->get_all_traversed(), concat(initial_intervals, {{131, 145}}));
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertAfterEndAdjacent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(121, 145));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertAfterEndTangent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(119, 145));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    test_list(ul_pointer->get_all_duplications(), {{119, 119}});
}

TEST(UniqueListTest, InsertAfterEndOverlap)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(109, 145));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{105, 145}}));
    test_list(ul_pointer->get_all_duplications(), {{109, 119}});
}

TEST(UniqueListTest, InsertAfterEndFullContain)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(97, 145));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{97, 145}}));
    test_list(ul_pointer->get_all_duplications(), {{105, 119}});
}

TEST(UniqueListTest, InsertBeforeEndAdjacent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(95, 103));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95, 119}}));
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeEndTangent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(95, 105));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95, 119}}));
    test_list(ul_pointer->get_all_duplications(), {{105, 105}});
}

TEST(UniqueListTest, InsertBeforeEndOverlap)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(95, 111));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{95, 119}}));
    test_list(ul_pointer->get_all_duplications(), {{105, 111}});
}

TEST(UniqueListTest, InsertEndFullContain)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(101, 131));
    test_list(ul_pointer->get_all_traversed(), concat(slice(initial_intervals, 0, -2), {{101, 131}}));
    test_list(ul_pointer->get_all_duplications(), {{105, 119}});
}

TEST(UniqueListTest, InsertBeforeEndFullContain3)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(37, 131));
    test_list(ul_pointer->get_all_traversed(), {initial_intervals[0], {37, 131}});
    test_list(ul_pointer->get_all_duplications(), slice(initial_intervals, 1));
}
