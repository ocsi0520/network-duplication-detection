#pragma once
#include "SegmentMerger.hpp"
#include "UniqueList.hpp"
#include <memory>

namespace MyNetwork
{
    class UniqueListFactory
    {
    public:
        UniqueListFactory(std::shared_ptr<SegmentMerger>);
        UniqueList create_unique_list();

    private:
        std::shared_ptr<SegmentMerger> merger;
    };
}