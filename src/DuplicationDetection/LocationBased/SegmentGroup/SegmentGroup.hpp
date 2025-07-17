// TODO: assert, all of them has the same location
#pragma once
#include "NetworkSegment.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

namespace MyNetwork
{
    class SegmentGroup
    {
    public:
        SegmentGroup(UniqueListFactory);
        void add(const Segment &segment);
        const std::deque<Segment> get_all_duplications() const;

    private:
        UniqueList mixed;
        UniqueList odd;
        UniqueList even;
    };
}