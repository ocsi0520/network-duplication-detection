#include "SegmentGroup.hpp"

using namespace MyNetwork;
// TODO: tests

SegmentGroup::SegmentGroup(
    std::shared_ptr<UniqueListFactory> ul_f) : mixed{ul_f->create_unique_list()},
                                               odd{ul_f->create_unique_list()},
                                               even{ul_f->create_unique_list()} {};

void SegmentGroup::add(const Segment &segment)
{
    switch (segment.parity)
    {
    case Parity::Mixed:
        mixed->add_segment(segment);
        break;
    case Parity::Even:
        even->add_segment(segment);
        break;
    case Parity::Odd:
        odd->add_segment(segment);
        break;
    }
}

const std::deque<Segment> SegmentGroup::get_all_duplications() const
{
    std::deque<Segment> result{odd->get_all_duplications()};
    const auto &even_duplications = even->get_all_duplications();
    result.insert(result.end(), even_duplications.begin(), even_duplications.end());

    const auto &mixed_duplications = mixed->get_all_duplications();
    result.insert(result.end(), mixed_duplications.begin(), mixed_duplications.end());

    return result;
}