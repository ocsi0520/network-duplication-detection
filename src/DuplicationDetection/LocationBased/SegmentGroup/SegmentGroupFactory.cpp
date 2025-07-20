#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"

using namespace MyNetwork;

SegmentGroupFactory::SegmentGroupFactory(const UniqueListFactory &ul_f) : list_factory{ul_f} {};
SegmentGroup SegmentGroupFactory::create_group() { return SegmentGroup(list_factory); }
