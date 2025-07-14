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

    Segment tangent = create_segment(Parity::Even, 10, 16);
    Segment tangent_result = merger.intersect_segment(base, tangent);
    test_same_base_properties(base, tangent_result);
    test_from_to_properties(tangent_result, 10, 10);
}

TEST(SegmentMergerTest, UnionSegment)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 2, 10);
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
    Segment s1 = create_segment(Parity::Even, 2, 10);
    Segment s2 = create_segment(Parity::Even, 12, 20);
    // s2.from_street_number - 2 == 10
    EXPECT_TRUE(merger.is_contiguous(s1, s2));
    // Not contiguous
    Segment s3 = create_segment(Parity::Even, 14, 20);
    EXPECT_FALSE(merger.is_contiguous(s1, s3));
}

TEST(SegmentMergerTest, IsContiguousMixed)
{
    SegmentMerger merger;
    Segment s1 = create_segment(Parity::Mixed, 1, 10);
    Segment s2 = create_segment(Parity::Mixed, 11, 20);
    // s2.from_street_number - 1 == 10
    EXPECT_TRUE(merger.is_contiguous(s1, s2));
    Segment s3 = create_segment(Parity::Mixed, 12, 20);
    EXPECT_FALSE(merger.is_contiguous(s1, s3));
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
    Segment s1 = create_segment(Parity::Even, 2, 10);
    Segment s2 = create_segment(Parity::Even, 8, 20);
    EXPECT_TRUE(merger.has_intersection(s1, s2));
    Segment s3 = create_segment(Parity::Even, 12, 20);
    EXPECT_FALSE(merger.has_intersection(s1, s3));
}
