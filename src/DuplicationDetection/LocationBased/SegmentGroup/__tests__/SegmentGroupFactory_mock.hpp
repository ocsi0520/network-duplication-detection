#include "gmock/gmock.h"
#include "LocationBased/SegmentGroup/SegmentGroupFactory.hpp"
#include "SegmentGroup_mock.hpp"
#include <vector>

using namespace MyNetwork;
using namespace ::testing;

class MockSegmentGroupFactory : public SegmentGroupFactory
{
public:
    MockSegmentGroupFactory() : mock_ul_factory_p{std::make_shared<MockUniqueListFactory>()},
                                SegmentGroupFactory(mock_ul_factory_p)
    {
    }

    MOCK_METHOD(std::unique_ptr<SegmentGroup>, create_group, (), (override));

    std::vector<MockSegmentGroup *> created_mock_segment_groups;

    void fill_mock_groups(size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            created_mock_segment_groups.push_back(new MockSegmentGroup());
        }
        EXPECT_CALL(*this, create_group())
            .Times(count)
            .WillRepeatedly(InvokeWithoutArgs(this, &MockSegmentGroupFactory::_return_next_group));
    }

    void clear_all_unused_groups()
    {
        for (size_t i = next_group_index; i < created_mock_segment_groups.size(); i++)
            delete created_mock_segment_groups[i];
    }

private:
    std::shared_ptr<MockUniqueListFactory> mock_ul_factory_p;
    size_t next_group_index = 0;
    std::unique_ptr<SegmentGroup> _return_next_group()
    {
        return std::unique_ptr<MockSegmentGroup>(created_mock_segment_groups[next_group_index++]);
    }
};
