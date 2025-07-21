#include "gtest/gtest.h"
#include <vector>
#include <deque>
#include <tuple>
#include "NetworkSegment.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"

using namespace MyNetwork;

template <typename T>
static std::vector<T> concat(const std::vector<T> &a, const std::vector<T> &b)
{
    std::vector<T> result = a;
    std::copy(b.begin(), b.end(), std::back_inserter(result));
    return result;
}

template <typename T>
static std::vector<T> slice(const std::vector<T> &a, int from, int to = -1)
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

static Segment create_same_type_segment(int from, int to)
{
    return create_segment(Parity::Odd, from, to);
}

static void test_list(const std::deque<Segment> &list, const std::vector<std::pair<int, int>> &expected_intervals)
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

static const std::vector<std::pair<int, int>> initial_intervals =
    {
        {15, 29},
        {45, 59},
        {75, 89},
        {105, 119}};

static std::unique_ptr<UniqueList> get_base_test_list()
{
    auto ul_pointer = std::make_unique<UniqueList>(std::make_shared<SegmentMerger>());
    for (const auto &interval : initial_intervals)
        ul_pointer->add_segment(create_same_type_segment(interval.first, interval.second));
    return ul_pointer;
}
