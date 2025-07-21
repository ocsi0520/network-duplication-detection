#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

UniqueListFactory::UniqueListFactory(std::shared_ptr<SegmentMerger> sm) : merger{sm} {};
UniqueList UniqueListFactory::create_unique_list()
{
    return UniqueList{merger};
}
