#pragma once
#include "SegmentMerger.hpp"
#include "UniqueList.hpp"

namespace MyNetwork
{
    class UniqueListFactory
    {
    public:
        UniqueListFactory(const SegmentMerger &sm);
        UniqueList create_unique_list();

    private:
        SegmentMerger merger;
    };
}