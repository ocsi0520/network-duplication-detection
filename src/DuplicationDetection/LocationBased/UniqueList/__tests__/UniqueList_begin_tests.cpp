#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"

TEST(UniqueListTest, InsertBeforeBegin)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(1, 5));

    test_list(ul_pointer->get_all_traversed(), concat({{1, 5}}, initial_intervals));

    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeBeginAdjacent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(5, 13));
    test_list(ul_pointer->get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeBeginTangent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(5, 15));
    test_list(ul_pointer->get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{15, 15}});
}

TEST(UniqueListTest, InsertBeforeBeginOverlap)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(5, 21));
    test_list(ul_pointer->get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{15, 21}});
}

TEST(UniqueListTest, InsertBeforeBeginFullContain)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(5, 29));
    test_list(ul_pointer->get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{15, 29}});
}

TEST(UniqueListTest, InsertAfterBeginAdjacent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(31, 39));
    test_list(ul_pointer->get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertAfterBeginTangent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(29, 39));
    test_list(ul_pointer->get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{29, 29}});
}

TEST(UniqueListTest, InsertAfterBeginOverlap)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(25, 39));
    test_list(ul_pointer->get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{25, 29}});
}

TEST(UniqueListTest, InsertAfterBeginFullContain)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(15, 39));
    test_list(ul_pointer->get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul_pointer->get_all_duplications(), {{15, 29}});
}

TEST(UniqueListTest, InsertAfterBeginFullContain3)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(11, 93));
    const auto &actual = ul_pointer->get_all_traversed();
    const auto &expected = concat({{11, 93}}, slice(initial_intervals, 3));
    test_list(actual, expected);
    test_list(ul_pointer->get_all_duplications(), slice(initial_intervals, 0, 3));
}
