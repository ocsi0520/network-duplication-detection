#include "SegmentMerger.hpp"

using namespace MyNetwork;

// TODO: tests

Segment SegmentMerger::intersect_segment(const Segment &s1, const Segment &s2) const
{
    // TODO: assert
    // assumption contiguous: s1 < s2 and same location (postal + street + parity)
    Segment result{s2};
    result.to_street_number = s1.to_street_number;
    result.from_street_number = s2.from_street_number;
    return result;
}

Segment SegmentMerger::union_segment(const Segment &s1, const Segment &s2) const
{

    // TODO: assert
    // assumption contiguous s1 < s2 and same location (postal + street + parity)
    Segment result{s1};
    result.to_street_number = s2.to_street_number;
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
    // TODO: assert
    // assumption, s1 < s2 and same location (postal + street + parity)
    return s1.postal_code == s2.postal_code && s1.STREET_NAME_AND_TYPE == s2.STREET_NAME_AND_TYPE && s1.parity == s2.parity &&
           one_less_from_number(s2) <= s1.to_street_number;
}

bool SegmentMerger::has_intersection(const Segment &s1, const Segment &s2) const
{
    // TODO: assert
    // assumption, s1 < s2 and same location (postal + street + parity)
    return s2.from_street_number <= s1.to_street_number;
}