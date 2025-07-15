#include "NetworkSegment.hpp"

namespace MyNetwork
{
    class SegmentMerger
    {
    public:
        Segment get_duplicate_segment_from(const Segment &,const Segment &) const;
        Segment merge_segments(const Segment &,const Segment &) const;
        bool is_mergeable(const Segment &,const Segment &) const;
        bool has_duplication(const Segment &, const Segment &) const;
    };
}