#include "gtest/gtest.h"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#define MY_SKIP(); // GTEST_SKIP();

using namespace MyNetwork;

template <typename T>
std::vector<T> concat(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<T> result = a;
    std::copy(b.begin(), b.end(), std::back_inserter(result));
    return result;
}

// for (auto& pair: expected_things)
// {
//     std::cout << pair.first << " - " << pair.second << "\n";
// }

template <typename T>
std::vector<T> slice(const std::vector<T> &a, int from, int to = -1)
{
    if (from < 0)
        from += a.size();
    if (to < 0)
        to += a.size() + 1;

    std::vector<T> result;
    for (size_t i = from; i < to; i++)
        result.push_back(a[i]);

    return result;
}

Segment create_same_type_segment(int from, int to)
{
    return create_segment(Parity::Odd, from, to);
}

void test_list(const std::deque<Segment> &list, const std::vector<std::pair<int, int>> &expected_intervals)
{
    ASSERT_EQ(list.size(), expected_intervals.size());
    auto it = list.begin();
    size_t i = 0;
    while (it != list.end())
    {
        const Segment &curr_segment = *it;
        EXPECT_EQ(curr_segment.from_street_number, expected_intervals[i].first) << "non-equal at " << i << "\n";
        EXPECT_EQ(curr_segment.to_street_number, expected_intervals[i].second);
        it++;
        i++;
    }
}

const std::vector<std::pair<int, int>> initial_intervals =
    {
        {15, 29},
        {45, 59},
        {75, 89},
        {105, 119}};

UniqueList get_base_test_list()
{
    UniqueList ul{SegmentMerger{}};
    for (const auto &interval : initial_intervals)
        ul.add_segment(create_same_type_segment(interval.first, interval.second));
    return ul;
}

// TODO: test when segment includes everything

TEST(UniqueListTest, AddToEmpty)
{
    MY_SKIP();
    UniqueList ul{SegmentMerger{}};
    ul.add_segment(create_same_type_segment(5, 7));
    EXPECT_TRUE(ul.get_all_duplications().empty());
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, AddSameTwice)
{
    MY_SKIP();
    UniqueList ul{SegmentMerger{}};
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    test_list(ul.get_all_duplications(), {{5, 7}});
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, AddSameThrice)
{
    MY_SKIP();
    UniqueList ul{SegmentMerger{}};
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    ul.add_segment(create_same_type_segment(5, 7));
    test_list(ul.get_all_duplications(), {{5, 7}});
    test_list(ul.get_all_traversed(), {{5, 7}});
}

TEST(UniqueListTest, TestBaseTestList)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    test_list(ul.get_all_traversed(), initial_intervals);

    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeBegin)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(1, 5));

    test_list(ul.get_all_traversed(), concat({{1, 5}}, initial_intervals));

    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeBeginAdjacent)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(5, 13));
    test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertBeforeBeginTangent)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(5, 15));
    test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{15, 15}});
}

TEST(UniqueListTest, InsertBeforeBeginOverlap)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(5, 21));
    test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{15, 21}});
}

TEST(UniqueListTest, InsertBeforeBeginFullContain)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(5, 29));
    test_list(ul.get_all_traversed(), concat({{5, 29}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{15, 29}});
}

TEST(UniqueListTest, InsertAfterBeginAdjacent)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(31, 39));
    test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    EXPECT_TRUE(ul.get_all_duplications().empty());
}

TEST(UniqueListTest, InsertAfterBeginTangent)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(29, 39));
    test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{29, 29}});
}

TEST(UniqueListTest, InsertAfterBeginOverlap)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(25, 39));
    test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{25, 29}});
}

TEST(UniqueListTest, InsertAfterBeginFullContain)
{
    MY_SKIP();
    UniqueList ul = get_base_test_list();
    ul.add_segment(create_same_type_segment(15, 39));
    test_list(ul.get_all_traversed(), concat({{15, 39}}, slice(initial_intervals, 1)));
    test_list(ul.get_all_duplications(), {{15, 29}});
}

// TODO: only first 3 segment merges
// TODO: only last 3 segment merges
