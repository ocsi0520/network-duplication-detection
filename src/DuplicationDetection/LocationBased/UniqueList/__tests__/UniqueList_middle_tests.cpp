#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"

TEST(UniqueListTest, InsertMiddle)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(63, 71));

    test_list(ul_pointer->get_all_traversed(),
              concat(
                  concat(
                      slice(initial_intervals, 0, 2),
                      {{63, 71}}),
                  slice(initial_intervals, 2)));

    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertMiddleAdjacent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(61, 73));

    test_list(ul_pointer->get_all_traversed(), {{15, 29}, {45, 89}, {105, 119}});
    EXPECT_TRUE(ul_pointer->get_all_duplications().empty());
}

TEST(UniqueListTest, InsertMiddleTangent)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(59, 75));

    test_list(ul_pointer->get_all_traversed(), {{15, 29}, {45, 89}, {105, 119}});
    test_list(ul_pointer->get_all_duplications(), {{59, 59}, {75, 75}});
}

TEST(UniqueListTest, InsertMiddleOverlap)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(53, 81));

    test_list(ul_pointer->get_all_traversed(), {{15, 29}, {45, 89}, {105, 119}});
    test_list(ul_pointer->get_all_duplications(), {{53, 59}, {75, 81}});
}

TEST(UniqueListTest, InsertMiddleFullContain)
{
    std::unique_ptr<UniqueList> ul_pointer = get_base_test_list();
    ul_pointer->add_segment(create_same_type_segment(41, 101));

    test_list(ul_pointer->get_all_traversed(), {{15, 29}, {41, 101}, {105, 119}});
    test_list(ul_pointer->get_all_duplications(), slice(initial_intervals, 1, 3));
}
