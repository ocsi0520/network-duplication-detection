#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"

using namespace MyNetwork;

SegmentGroupFactory::SegmentGroupFactory(const UniqueListFactory &ul_f) : list_factory{ul_f} {};
std::unique_ptr<SegmentGroup> SegmentGroupFactory::create_group()
{
    return std::make_unique<SegmentGroup>(list_factory);
}
