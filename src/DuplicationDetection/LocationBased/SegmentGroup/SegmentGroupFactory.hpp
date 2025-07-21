#pragma once
#include "SegmentMerger.hpp"
#include "SegmentGroup.hpp"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

namespace MyNetwork
{
    class SegmentGroupFactory
    {
    public:
        SegmentGroupFactory(const SegmentGroupFactory &) = delete;
        SegmentGroupFactory(SegmentGroupFactory &&) = delete;

        SegmentGroupFactory &operator=(const SegmentGroupFactory &) = delete;
        SegmentGroupFactory &operator=(SegmentGroupFactory &&) = delete;

        SegmentGroupFactory(std::shared_ptr<UniqueListFactory>);
        std::unique_ptr<SegmentGroup> create_group();

    private:
        std::shared_ptr<UniqueListFactory> list_factory;
    };
}