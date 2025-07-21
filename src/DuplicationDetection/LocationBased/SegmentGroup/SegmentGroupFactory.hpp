#pragma once
#include "SegmentMerger.hpp"
#include "SegmentGroup.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

namespace MyNetwork
{
    class SegmentGroupFactory
    {
    public:
        SegmentGroupFactory(const UniqueListFactory &);
        std::unique_ptr<SegmentGroup> create_group();

    private:
        UniqueListFactory list_factory;
    };
}