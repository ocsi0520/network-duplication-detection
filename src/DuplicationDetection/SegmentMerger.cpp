#include "SegmentMerger.hpp"
#include <cassert>
#include <algorithm>

using namespace MyNetwork;

Segment SegmentMerger::intersect_segment(const Segment &s1, const Segment &s2) const
{
    assert(has_intersection(s1, s2));

    Segment result{s2};
    result.from_street_number = std::max(s1.from_street_number, s2.from_street_number);
    result.to_street_number = std::min(s1.to_street_number, s2.to_street_number);
    return result;
}

Segment SegmentMerger::union_segment(const Segment &s1, const Segment &s2) const
{

    assert(is_contiguous(s1, s2));
    Segment result{s1};
    result.from_street_number = std::min(s1.from_street_number, s2.from_street_number);
    result.to_street_number = std::max(s1.to_street_number, s2.to_street_number);
    return result;
}

int one_less_from_number(const Segment &s)
{
    if (s.parity == Parity::Mixed)
        return s.from_street_number - 1;

    return s.from_street_number - 2;
}

bool SegmentMerger::is_contiguous(const Segment &s1, const Segment &s2) const
{
    return s1.postal_code == s2.postal_code && s1.STREET_NAME_AND_TYPE == s2.STREET_NAME_AND_TYPE && s1.parity == s2.parity &&
           one_less_from_number(s2) <= s1.to_street_number;
}

bool SegmentMerger::has_intersection(const Segment &s1, const Segment &s2) const
{
    assert(s1 <= s2 && is_contiguous(s1, s2));
    return s2.from_street_number <= s1.to_street_number;
}