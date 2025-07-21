#pragma once
#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"
#include <map> // not unordered, so segments are sorted at the end
#include <deque>

// TODO: create .cpp
// TODO: tests

namespace MyNetwork
{
    class DuplicationDetector
    {
    public:
        DuplicationDetector(const SegmentGroupFactory &sg_f) : group_factory{sg_f} {};
        void add_segment(const Segment &segment)
        {
            auto location_key = get_location_key(segment);
            auto group_it = location_groups.find(location_key);
            if (group_it == location_groups.end())
            {
                auto new_group_pointer = group_factory.create_group();
                new_group_pointer->add(segment);
                location_groups.insert({location_key, std::move(new_group_pointer)});
            }
            else
            {
                group_it->second->add(segment);
            }
        }

        std::deque<Segment> get_all_duplications() const
        {
            std::deque<Segment> result;
            for (auto& [_key, group] : location_groups)
            {
                auto duplications_for_group = group->get_all_duplications();
                result.insert(
                    result.end(),
                    duplications_for_group.begin(),
                    duplications_for_group.end());
            }
            return result;
        }

    private:
        const std::string get_location_key(const Segment &segment) const
        {
            return segment.postal_code + "_" + segment.STREET_NAME_AND_TYPE;
        }

        SegmentGroupFactory group_factory;
        std::map<std::string, std::unique_ptr<SegmentGroup>> location_groups;
    };
}