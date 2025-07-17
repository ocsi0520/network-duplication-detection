#pragma once
#include "SegmentMerger.hpp"
#include "SegmentGroup.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

// TODO: tests

namespace MyNetwork
{
    class SegmentGroupFactory
    {
    public:
        // TODO: check this
        SegmentGroupFactory(const UniqueListFactory &ul_f) : list_factory{ul_f} {};
        SegmentGroup create_group()
        {
            return SegmentGroup{list_factory};
        }

    private:
        UniqueListFactory list_factory;
    };
}