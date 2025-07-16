#pragma once
#include "NetworkSegment.hpp"
#include "SegmentMerger.hpp"
#include <deque>
#include <vector>

namespace MyNetwork
{
    class UniqueList
    {
    public:
        UniqueList(SegmentMerger);
        void add_segment(Segment);
        const std::deque<Segment> &get_all_traversed();
        const std::deque<Segment> &get_all_duplications();

    private:
        std::vector<Segment> insert_segment_into_list(std::deque<Segment> &list, Segment segment);

        std::deque<Segment> all_traversed{};
        std::deque<Segment> duplications{};
        SegmentMerger merger;
    };
}