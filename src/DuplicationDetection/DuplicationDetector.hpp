#pragma once
#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"
#include <map> // not unordered, so segments are sorted at the end
#include <deque>

namespace MyNetwork
{
    class DuplicationDetector
    {
    public:
        DuplicationDetector(const DuplicationDetector &) = delete;
        DuplicationDetector(DuplicationDetector &&) = delete;

        DuplicationDetector &operator=(const DuplicationDetector &) = delete;
        DuplicationDetector &operator=(DuplicationDetector &&) = delete;

        DuplicationDetector(std::unique_ptr<SegmentGroupFactory> sg_f);

        void add_segment(const Segment &segment);

        std::deque<Segment> get_all_duplications() const;

    private:
        const std::string get_location_key(const Segment &segment) const;
        std::unique_ptr<SegmentGroupFactory> group_factory;
        std::map<std::string, std::unique_ptr<SegmentGroup>> location_groups;
    };
}