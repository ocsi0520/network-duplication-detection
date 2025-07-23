#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

UniqueListFactory::UniqueListFactory(std::shared_ptr<SegmentMerger> sm) : merger{sm} {};
std::unique_ptr<UniqueList> UniqueListFactory::create_unique_list()
{
    return std::make_unique<UniqueList>(merger);
}
