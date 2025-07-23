#pragma once
#include "SegmentMerger.hpp"
#include "UniqueList.hpp"
#include <memory>

namespace MyNetwork
{
    class UniqueListFactory
    {
    public:
        UniqueListFactory(const UniqueListFactory &) = delete;
        UniqueListFactory(UniqueListFactory &&) = delete;

        UniqueListFactory &operator=(const UniqueListFactory &) = delete;
        UniqueListFactory &operator=(UniqueListFactory &&) = delete;

        UniqueListFactory(std::shared_ptr<SegmentMerger>);
        virtual std::unique_ptr<UniqueList> create_unique_list();

    private:
        std::shared_ptr<SegmentMerger> merger;
    };
}