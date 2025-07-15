#include "gtest/gtest.h"
#include "SegmentMerger.hpp"
#include "NetworkSegment.hpp"
#include "Segment/__tests__/TestSegment.hpp"

/*
  legends for test:

  base:                                      |<----------------->|
  same:                                      |<----------------->|
  super:                                  <--|-------------------|--->
  adj_left:                          <-----> |                   |
  adj_right:                                 |                   | <----->
  tangent_left:                       <----->|                   |
  tangent_right:                             |                   |<----->
  overlaps_left:                         <---|----->             |
  overlaps_right:                            |               <---|----->
  far_left:             <-------->           |                   |
  far_right:                                 |                   |     <------>
*/

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

TEST(SegmentMergerTest, IsMergeableEven)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 30, 50);

    Segment same = create_segment(Parity::Even, 30, 50);
    EXPECT_TRUE(merger.is_mergeable(base, same));
    Segment sub = create_segment(Parity::Even, 40, 48);
    EXPECT_TRUE(merger.is_mergeable(base, sub));
    Segment super = create_segment(Parity::Even, 20, 60);
    EXPECT_TRUE(merger.is_mergeable(base, super));

    Segment adjacent_from_left = create_segment(Parity::Even, 20, 28);
    EXPECT_TRUE(merger.is_mergeable(base, adjacent_from_left));
    Segment adjacent_from_right = create_segment(Parity::Even, 52, 58);
    EXPECT_TRUE(merger.is_mergeable(base, adjacent_from_right));

    Segment tangent_from_left = create_segment(Parity::Even, 20, 30);
    EXPECT_TRUE(merger.is_mergeable(base, tangent_from_left));
    Segment tangent_from_right = create_segment(Parity::Even, 50, 58);
    EXPECT_TRUE(merger.is_mergeable(base, tangent_from_right));

    Segment overlaps_from_left = create_segment(Parity::Even, 20, 36);
    EXPECT_TRUE(merger.is_mergeable(base, overlaps_from_left));
    Segment overlaps_from_right = create_segment(Parity::Even, 44, 58);
    EXPECT_TRUE(merger.is_mergeable(base, overlaps_from_right));

    Segment far_from_left = create_segment(Parity::Even, 20, 26);
    EXPECT_FALSE(merger.is_mergeable(base, far_from_left));

    Segment far_from_right = create_segment(Parity::Even, 54, 58);
    EXPECT_FALSE(merger.is_mergeable(base, far_from_right));
}

TEST(SegmentMergerTest, IsMergeableMixedFar)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Mixed, 30, 50);

    Segment adjacent_from_left = create_segment(Parity::Mixed, 20, 29);
    EXPECT_TRUE(merger.is_mergeable(base, adjacent_from_left));
    Segment adjacent_from_right = create_segment(Parity::Mixed, 51, 58);
    EXPECT_TRUE(merger.is_mergeable(base, adjacent_from_right));

    Segment far_from_left = create_segment(Parity::Mixed, 20, 28);
    EXPECT_FALSE(merger.is_mergeable(base, far_from_left));

    Segment far_from_right = create_segment(Parity::Mixed, 52, 58);
    EXPECT_FALSE(merger.is_mergeable(base, far_from_right));
}

TEST(SegmentMergerTest, MergeEven)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 30, 50);

    Segment same = create_segment(Parity::Even, 30, 50);
    EXPECT_EQ(merger.merge_segments(base, same), base);

    Segment sub = create_segment(Parity::Even, 40, 48);
    EXPECT_EQ(merger.merge_segments(base, sub), base);
    Segment super = create_segment(Parity::Even, 20, 60);
    EXPECT_EQ(merger.merge_segments(base, super), super);

    Segment adjacent_from_left = create_segment(Parity::Even, 20, 28);
    EXPECT_EQ(merger.merge_segments(base, adjacent_from_left), create_segment(Parity::Even, 20, 50));

    Segment adjacent_from_right = create_segment(Parity::Even, 52, 58);
    EXPECT_EQ(merger.merge_segments(base, adjacent_from_right), create_segment(Parity::Even, 30, 58));

    Segment tangent_from_left = create_segment(Parity::Even, 20, 30);
    EXPECT_EQ(merger.merge_segments(base, tangent_from_left), create_segment(Parity::Even, 20, 50));
    Segment tangent_from_right = create_segment(Parity::Even, 50, 58);
    EXPECT_EQ(merger.merge_segments(base, tangent_from_right), create_segment(Parity::Even, 30, 58));
}

TEST(SegmentMergerTest, MergeAdjacentAtMixed)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Mixed, 30, 50);

    Segment adjacent_from_left = create_segment(Parity::Mixed, 20, 29);
    EXPECT_EQ(merger.merge_segments(base, adjacent_from_left), create_segment(Parity::Mixed, 20, 50));

    Segment adjacent_from_right = create_segment(Parity::Mixed, 51, 58);
    EXPECT_EQ(merger.merge_segments(base, adjacent_from_right), create_segment(Parity::Mixed, 30, 58));
}

TEST(SegmentMergerTest, HasDuplicationEven)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 30, 50);

    Segment same = create_segment(Parity::Even, 30, 50);
    EXPECT_TRUE(merger.has_duplication(base, same));
    Segment sub = create_segment(Parity::Even, 40, 48);
    EXPECT_TRUE(merger.has_duplication(base, sub));
    Segment super = create_segment(Parity::Even, 20, 60);
    EXPECT_TRUE(merger.has_duplication(base, super));

    Segment adjacent_from_left = create_segment(Parity::Even, 20, 28);
    EXPECT_FALSE(merger.has_duplication(base, adjacent_from_left));
    Segment adjacent_from_right = create_segment(Parity::Even, 52, 58);
    EXPECT_FALSE(merger.has_duplication(base, adjacent_from_right));

    Segment tangent_from_left = create_segment(Parity::Even, 20, 30);
    EXPECT_TRUE(merger.has_duplication(base, tangent_from_left));
    Segment tangent_from_right = create_segment(Parity::Even, 50, 58);
    EXPECT_TRUE(merger.has_duplication(base, tangent_from_right));

    Segment overlaps_from_left = create_segment(Parity::Even, 20, 36);
    EXPECT_TRUE(merger.has_duplication(base, overlaps_from_left));
    Segment overlaps_from_right = create_segment(Parity::Even, 44, 58);
    EXPECT_TRUE(merger.has_duplication(base, overlaps_from_right));

    Segment far_from_left = create_segment(Parity::Even, 20, 26);
    EXPECT_FALSE(merger.has_duplication(base, far_from_left));

    Segment far_from_right = create_segment(Parity::Even, 54, 58);
    EXPECT_FALSE(merger.has_duplication(base, far_from_right));
}

TEST(SegmentMergerTest, HasDuplicationMixed)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Mixed, 30, 50);

    Segment adjacent_from_left = create_segment(Parity::Mixed, 20, 29);
    EXPECT_FALSE(merger.has_duplication(base, adjacent_from_left));
    Segment adjacent_from_right = create_segment(Parity::Mixed, 51, 58);
    EXPECT_FALSE(merger.has_duplication(base, adjacent_from_right));

    Segment far_from_left = create_segment(Parity::Mixed, 20, 28);
    EXPECT_FALSE(merger.has_duplication(base, far_from_left));

    Segment overlaps_from_left = create_segment(Parity::Mixed, 29, 31);
    EXPECT_TRUE(merger.has_duplication(base, overlaps_from_left));
    Segment overlaps_from_right = create_segment(Parity::Mixed, 49, 51);
    EXPECT_TRUE(merger.has_duplication(base, overlaps_from_right));

    Segment far_from_right = create_segment(Parity::Mixed, 52, 58);
    EXPECT_FALSE(merger.has_duplication(base, far_from_right));
}

TEST(SegmentMergerTest, GetDuplicatesForEven)
{
    SegmentMerger merger;
    Segment base = create_segment(Parity::Even, 30, 50);

    Segment same = create_segment(Parity::Even, 30, 50);
    EXPECT_EQ(merger.get_duplicate_segment_from(base, same), base);

    Segment sub = create_segment(Parity::Even, 40, 48);
    EXPECT_EQ(merger.get_duplicate_segment_from(base, sub), sub);
    Segment super = create_segment(Parity::Even, 20, 60);
    EXPECT_EQ(merger.get_duplicate_segment_from(base, super), base);

    Segment tangent_from_left = create_segment(Parity::Even, 20, 30);
    EXPECT_EQ(merger.get_duplicate_segment_from(base, tangent_from_left), create_segment(Parity::Even, 30, 30));
    Segment tangent_from_right = create_segment(Parity::Even, 50, 58);
    EXPECT_EQ(merger.get_duplicate_segment_from(base, tangent_from_right), create_segment(Parity::Even, 50, 50));
}
