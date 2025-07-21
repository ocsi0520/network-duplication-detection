// TODO: assert, all of them has the same location
#pragma once
#include "NetworkSegment.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

namespace MyNetwork
{
    class SegmentGroup
    {
    public:
        SegmentGroup(const SegmentGroup &) = delete;
        SegmentGroup(SegmentGroup &&) = delete;

        SegmentGroup &operator=(const SegmentGroup &) = delete;
        SegmentGroup &operator=(SegmentGroup &&) = delete;

        SegmentGroup(std::shared_ptr<UniqueListFactory>);

        void add(const Segment &segment);
        const std::deque<Segment> get_all_duplications() const;

    private:
        std::unique_ptr<UniqueList> mixed;
        std::unique_ptr<UniqueList> odd;
        std::unique_ptr<UniqueList> even;
    };
}