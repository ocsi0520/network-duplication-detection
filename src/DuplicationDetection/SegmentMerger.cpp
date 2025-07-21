#include "SegmentMerger.hpp"
#include <cassert>
#include <algorithm>

using namespace MyNetwork;

SegmentMerger::SegmentMerger() = default;

int SegmentMerger::one_less_street_number(const Parity parity, const int street_number) const
{
    return parity == Parity::Mixed ? street_number - 1 : street_number - 2;
}

bool has_same_location_and_parity(const Segment &s1,  const Segment &s2)
{
    return s1.postal_code == s2.postal_code && s1.STREET_NAME_AND_TYPE == s2.STREET_NAME_AND_TYPE && s1.parity == s2.parity;
}


bool SegmentMerger::is_mergeable(const Segment &s1, const Segment &s2) const
{
    if (!has_same_location_and_parity(s1, s2))
        return false;

    if (s2.to_street_number < one_less_street_number(s1.parity, s1.from_street_number))
        return false;

    if (s1.to_street_number < one_less_street_number(s2.parity, s2.from_street_number))
        return false;
    
    return true;
}

// TODO: de-duplicate with is_mergeable
bool SegmentMerger::has_duplication(const Segment &s1, const Segment &s2) const
{
    if (!has_same_location_and_parity(s1, s2))
        return false;

    if (s2.to_street_number < s1.from_street_number)
        return false;

    if (s1.to_street_number < s2.from_street_number)
        return false;

    return true;
}

Segment SegmentMerger::get_duplicate_segment_from(const Segment &s1, const Segment &s2) const
{
    assert(has_duplication(s1, s2));

    Segment result{s2};
    result.from_street_number = std::max(s1.from_street_number, s2.from_street_number);
    result.to_street_number = std::min(s1.to_street_number, s2.to_street_number);
    return result;
}

Segment SegmentMerger::merge_segments(const Segment &s1, const Segment &s2) const
{
    assert(is_mergeable(s1, s2));
    Segment result{s1};
    result.from_street_number = std::min(s1.from_street_number, s2.from_street_number);
    result.to_street_number = std::max(s1.to_street_number, s2.to_street_number);
    return result;
}
