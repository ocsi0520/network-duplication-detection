#pragma once
#include "NetworkSegment.hpp"
#include "SegmentMerger.hpp"
#include <deque>
#include <vector>
#include <memory>

namespace MyNetwork
{
    class UniqueList
    {
    public:
        UniqueList(std::shared_ptr<SegmentMerger>);

        UniqueList(const UniqueList&) = delete;
        UniqueList(UniqueList&&) = delete;

        UniqueList& operator=(const UniqueList&) = delete;
        UniqueList& operator=(UniqueList&&) = delete;

        void add_segment(const Segment&);
        const std::deque<Segment> &get_all_traversed() const;
        const std::deque<Segment> &get_all_duplications() const;

    private:
        std::vector<Segment> insert_segment_into_list(std::deque<Segment> &list, Segment segment);

        std::deque<Segment> all_traversed{};
        std::deque<Segment> duplications{};
        std::shared_ptr<SegmentMerger> merger;
    };
}