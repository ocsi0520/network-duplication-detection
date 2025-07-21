#pragma once
#include "SegmentMerger.hpp"
#include "UniqueList.hpp"
#include <memory>

// TODO: make it non-movable & non-copiable, so that it becomes singleton
// and we make a shared_ptr for that one
namespace MyNetwork
{
    class UniqueListFactory
    {
    public:
        UniqueListFactory(std::shared_ptr<SegmentMerger>);
        std::unique_ptr<UniqueList> create_unique_list();

    private:
        std::shared_ptr<SegmentMerger> merger;
    };
}