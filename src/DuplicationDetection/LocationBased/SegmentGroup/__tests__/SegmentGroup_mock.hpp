#include "gmock/gmock.h"
#include "LocationBased/SegmentGroup/SegmentGroup.hpp"
#include "LocationBased/UniqueList/__tests__/UniqueListFactory_mock.hpp"

using namespace MyNetwork;

class MockSegmentGroup : public SegmentGroup
{
public:
    MockSegmentGroup() : SegmentGroup{std::make_shared<MockUniqueListFactory>()}
    {
    }

    MOCK_METHOD(void, add, (const Segment &), (override));
    MOCK_METHOD(const std::deque<Segment>, get_all_duplications, (), (const, override));
};
