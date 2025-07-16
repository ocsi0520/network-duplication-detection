#include "DuplicationDetection/LocationBased/UniqueList/UniqueList.hpp"
#include <algorithm>

using namespace MyNetwork;

UniqueList::UniqueList(SegmentMerger sm) : merger{sm} {};

// TODO: check whether const Segment&
void UniqueList::add_segment(Segment new_s)
{
    auto first_level_duplications = insert_segment_into_list(all_traversed, new_s);
    for (auto &first_level_duplication : first_level_duplications)
    {
        insert_segment_into_list(duplications, first_level_duplication);
    }
}

std::vector<Segment> UniqueList::insert_segment_into_list(std::deque<Segment> &list, Segment new_s)
{
    if (list.empty())
    {
        list.push_back(new_s);
        return {};
    }

    auto greater_non_mergeable_it = std::find_if(
        list.begin(),
        list.end(),
        [&](const Segment &list_s)
        {
            // no contiguous and less
            return new_s.to_street_number <
                   merger.one_less_street_number(list_s.parity, list_s.from_street_number);
        });

    if (greater_non_mergeable_it == list.begin())
    {
        list.push_front(new_s);
        return {};
    }

    auto merge_candidate_it = greater_non_mergeable_it - 1;
    std::vector<Segment> current_duplications;

    while (merger.is_mergeable(*merge_candidate_it, new_s))
    {
        if (merger.has_duplication(*merge_candidate_it, new_s))
        {
            // TODO: insert in reverse order, so it might be more efficient
            current_duplications.push_back(
                merger.get_duplicate_segment_from(*merge_candidate_it, new_s));
        }
        new_s = merger.merge_segments(*merge_candidate_it, new_s);
        if (merge_candidate_it == list.begin()) // new_s contained the whole first part of the list
        {
            *merge_candidate_it = new_s;
            return current_duplications;
        }
        else
        {
            list.erase(merge_candidate_it);
            merge_candidate_it--;
        }
    }
    list.insert(merge_candidate_it + 1, new_s);

    return current_duplications;
}

const std::deque<Segment> &UniqueList::get_all_traversed()
{
    return all_traversed;
}

const std::deque<Segment> &UniqueList::get_all_duplications()
{
    return duplications;
}
