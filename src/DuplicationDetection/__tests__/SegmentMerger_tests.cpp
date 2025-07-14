#include "gtest/gtest.h"
#include "SegmentMerger.hpp"
#include "NetworkSegment.hpp"
#include "Segment/__tests__/TestSegment.hpp"

using namespace MyNetwork;

void test_same_base_properties(const Segment &s1, const Segment &s2)
{
    EXPECT_EQ(s1.postal_code, s2.postal_code);
    EXPECT_EQ(s1.STREET_NAME_AND_TYPE, s2.STREET_NAME_AND_TYPE);
    EXPECT_EQ(s1.parity, s2.parity);
}

void test_from_to_properties(const Segment &s, int expected_from, int expected_to)
{
    EXPECT_EQ(s.from_street_number, expected_from);
    EXPECT_EQ(s.to_street_number, expected_to);
}

TEST(SegmentMergerTest, IntersectSegment)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 2, 10);

    Segment overlapping = create_segment(Parity::Even, 8, 20);
    Segment overlapping_result = merger.intersect_segment(base, overlapping);
    test_same_base_properties(base, overlapping_result);
    test_from_to_properties(overlapping_result, 8, 10);

    Segment fully_included = create_segment(Parity::Even, 4, 6);
    Segment fully_included_result = merger.intersect_segment(base, fully_included);
    test_same_base_properties(base, fully_included_result);
    test_from_to_properties(fully_included_result, 4, 6);

    Segment tangent = create_segment(Parity::Even, 10, 16);
    Segment tangent_result = merger.intersect_segment(base, tangent);
    test_same_base_properties(base, tangent_result);
    test_from_to_properties(tangent_result, 10, 10);
}

TEST(SegmentMergerTest, UnionSegment)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 2, 10);

    Segment same = create_segment(Parity::Even, 2, 10);
    Segment same_result = merger.union_segment(base, same);
    test_same_base_properties(base, same_result);
    test_from_to_properties(same_result, 2, 10);

    Segment fully_included = create_segment(Parity::Even, 4, 6);
    Segment fully_included_result = merger.union_segment(base, fully_included);
    test_same_base_properties(base, fully_included_result);
    test_from_to_properties(fully_included_result, 2, 10);

    Segment overlapping = create_segment(Parity::Even, 8, 20);
    Segment overlapping_result = merger.union_segment(base, overlapping);
    test_same_base_properties(base, overlapping_result);
    test_from_to_properties(overlapping_result, 2, 20);

    Segment tangent = create_segment(Parity::Even, 10, 16);
    Segment tangent_result = merger.union_segment(base, tangent);
    test_same_base_properties(base, tangent_result);
    test_from_to_properties(tangent_result, 2, 16);

    Segment adjacent = create_segment(Parity::Even, 12, 32);
    Segment adjacent_result = merger.union_segment(base, adjacent);
    test_same_base_properties(base, adjacent_result);
    test_from_to_properties(adjacent_result, 2, 32);
}

TEST(SegmentMergerTest, IsContiguousEven)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 2, 10);

    Segment same = create_segment(Parity::Even, 2, 10);
    EXPECT_TRUE(merger.is_contiguous(base, same));

    Segment fully_included = create_segment(Parity::Even, 4, 8);
    EXPECT_TRUE(merger.is_contiguous(base, fully_included));

    Segment tangent = create_segment(Parity::Even, 10, 16);
    EXPECT_TRUE(merger.is_contiguous(base, tangent));

    Segment adjacent = create_segment(Parity::Even, 12, 20);
    EXPECT_TRUE(merger.is_contiguous(base, adjacent));

    Segment overlapping = create_segment(Parity::Even, 6, 16);
    EXPECT_TRUE(merger.is_contiguous(base, overlapping));

    Segment far = create_segment(Parity::Even, 14, 20);
    EXPECT_FALSE(merger.is_contiguous(base, far));
}

TEST(SegmentMergerTest, IsContiguousMixed)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Mixed, 2, 9);

    Segment same = create_segment(Parity::Mixed, 2, 9);
    EXPECT_TRUE(merger.is_contiguous(base, same));

    Segment fully_included = create_segment(Parity::Mixed, 4, 8);
    EXPECT_TRUE(merger.is_contiguous(base, fully_included));

    Segment tangent = create_segment(Parity::Mixed, 9, 14);
    EXPECT_TRUE(merger.is_contiguous(base, tangent));

    Segment adjacent = create_segment(Parity::Mixed, 10, 20);
    EXPECT_TRUE(merger.is_contiguous(base, adjacent));

    Segment overlapping = create_segment(Parity::Mixed, 6, 16);
    EXPECT_TRUE(merger.is_contiguous(base, overlapping));

    Segment far = create_segment(Parity::Mixed, 11, 20);
    EXPECT_FALSE(merger.is_contiguous(base, far));
}

TEST(SegmentMergerTest, IsContiguousDifferentLocation)
{
    SegmentMerger merger;
    Segment base_segment = create_segment(Parity::Even, 2, 10, "1045", "Kossuth utca");
    Segment different_street = create_segment(Parity::Even, 12, 20, "1045", "Petőfi utca");
    EXPECT_FALSE(merger.is_contiguous(base_segment, different_street));
    Segment different_postal_code = create_segment(Parity::Even, 12, 20, "4046", "Kossuth utca");
    EXPECT_FALSE(merger.is_contiguous(base_segment, different_postal_code));
    Segment different_parity = create_segment(Parity::Odd, 11, 21, "1045", "Kossuth utca");
    EXPECT_FALSE(merger.is_contiguous(base_segment, different_parity));
}

TEST(SegmentMergerTest, HasIntersection)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 2, 10);

    Segment same = create_segment(Parity::Even, 2, 10);
    EXPECT_TRUE(merger.has_intersection(base, same));

    Segment fully_included = create_segment(Parity::Even, 4, 8);
    EXPECT_TRUE(merger.has_intersection(base, fully_included));

    Segment overlapping = create_segment(Parity::Even, 8, 20);
    EXPECT_TRUE(merger.has_intersection(base, overlapping));

    Segment tangent = create_segment(Parity::Even, 10, 16);
    EXPECT_TRUE(merger.has_intersection(base, tangent));

    Segment adjacent = create_segment(Parity::Even, 12, 20);
    EXPECT_FALSE(merger.has_intersection(base, adjacent));

    // far: 14-20 can't be as it's not contiguous with base
}
