#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

UniqueListFactory::UniqueListFactory(const SegmentMerger &sm) : merger{sm} {};
UniqueList UniqueListFactory::create_unique_list()
{
    return UniqueList{merger};
}
