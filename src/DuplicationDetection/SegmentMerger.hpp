#include "NetworkSegment.hpp"

namespace MyNetwork
{
    class SegmentMerger
    {
    public:
        Segment intersect_segment(const Segment &s1, const Segment &s2) const;
        Segment union_segment(const Segment &s1, const Segment &s2) const;
        bool is_contiguous(const Segment &s1, const Segment &s2) const;
        bool has_intersection(const Segment &s1, const Segment &s2) const;
    };
}