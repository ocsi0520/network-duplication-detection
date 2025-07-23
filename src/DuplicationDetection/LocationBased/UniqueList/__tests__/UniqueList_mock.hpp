#include "gmock/gmock.h"
#include "LocationBased/UniqueList/UniqueList.hpp"

using namespace MyNetwork;

class MockUniqueList : public UniqueList
{
public:
    MockUniqueList() : UniqueList(nullptr) {}

    MOCK_METHOD(void, add_segment, (const Segment &s), (override));
    MOCK_METHOD(const std::deque<Segment> &, get_all_traversed, (), (const, override));
    MOCK_METHOD(const std::deque<Segment> &, get_all_duplications, (), (const, override));
};
