#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/__tests__/UniqueList_tests_helper.hpp"


TEST(UniqueListTest, InsertAfterBegin)
{
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(131, 145));
    test_list(ul.get_all_traversed(), concat(initial_intervals, {{131, 145}}));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

// TEST(UniqueListTest, InsertAfterBeginAdjacent)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(5, 13));
//     test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
//     EXPECT_TRUE(ul.get_all_duplications().empty());
// }

// TEST(UniqueListTest, InsertAfterBeginTangent)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(5, 15));
//     test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{15, 15}});
// }

// TEST(UniqueListTest, InsertAfterBeginOverlap)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(5, 21));
//     test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{15, 21}});
// }

// TEST(UniqueListTest, InsertAfterBeginFullContain)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(5, 29));
//     test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{15, 29}});
// }

// TEST(UniqueListTest, InsertAfterBeginAdjacent)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(31, 39));
//     test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
//     EXPECT_TRUE(ul.get_all_duplications().empty());
// }

// TEST(UniqueListTest, InsertAfterBeginTangent)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(29, 39));
//     test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{29, 29}});
// }

// TEST(UniqueListTest, InsertAfterBeginOverlap)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(25, 39));
//     test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{25, 29}});
// }

// TEST(UniqueListTest, InsertAfterBeginFullContain)
// {
//     UniqueList ul = get_base_test_list();
//     ul.add_segment(create_same_type_segment(15, 39));
//     test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
//     test_list(ul.get_all_duplications(), {{15, 29}});
// }

// TODO: only last 3 segment merges
