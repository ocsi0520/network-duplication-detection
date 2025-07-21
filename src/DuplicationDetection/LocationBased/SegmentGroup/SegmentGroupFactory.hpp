#pragma once
#include "SegmentMerger.hpp"
#include "SegmentGroup.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

namespace MyNetwork
{
    class SegmentGroupFactory
    {
    public:
        SegmentGroupFactory(std::shared_ptr<UniqueListFactory>);
        std::unique_ptr<SegmentGroup> create_group();

    private:
        std::shared_ptr<UniqueListFactory> list_factory;
    };
}