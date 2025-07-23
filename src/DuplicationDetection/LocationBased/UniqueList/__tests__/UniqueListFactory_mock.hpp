#include "gmock/gmock.h"
#include "LocationBased/UniqueList/UniqueListFactory.hpp"

using namespace MyNetwork;

class MockUniqueListFactory : public UniqueListFactory
{
public:
    MockUniqueListFactory(): UniqueListFactory(nullptr) {}
    MOCK_METHOD(std::unique_ptr<UniqueList>, create_unique_list, (), (override));
};
