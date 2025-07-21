#pragma once
#include "NetworkSegment.hpp"

namespace MyNetwork
{
    class SegmentMerger
    {
    public:
        SegmentMerger();
        SegmentMerger(const SegmentMerger&) = delete;
        SegmentMerger(SegmentMerger&&) = delete;

        SegmentMerger& operator=(const SegmentMerger&) = delete;
        SegmentMerger& operator=(SegmentMerger&&) = delete;

        Segment get_duplicate_segment_from(const Segment &,const Segment &) const;
        Segment merge_segments(const Segment &,const Segment &) const;
        bool is_mergeable(const Segment &,const Segment &) const;
        bool has_duplication(const Segment &, const Segment &) const;
        int one_less_street_number(Parity parity, int street_number) const;
    };
}