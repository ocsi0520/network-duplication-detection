#pragma once
#include <vector>
#include "NetworkSegment.hpp"

namespace MyNetwork
{
    class SegmentMapper
    {
    public:
        std::vector<Segment> map_from_record(const NetworkRecord &);
    };
}
