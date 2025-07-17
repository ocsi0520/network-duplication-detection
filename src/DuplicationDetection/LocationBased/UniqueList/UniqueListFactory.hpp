#pragma once
#include "SegmentMerger.hpp"
#include "UniqueList.hpp"

namespace MyNetwork
{
    class UniqueListFactory
    {
    public:
        // TODO: check this
        UniqueListFactory(const SegmentMerger &sm) : merger{sm} {};
        UniqueList create_unique_list()
        {
            return UniqueList{merger};
        }

    private:
        SegmentMerger merger;
    };
}