#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DuplicationDetector.hpp"
#include "DuplicationDetection/LocationBased/SegmentGroup/__tests__/SegmentGroupFactory_mock.hpp"
#include "Segment/__tests__/TestSegment.hpp"

using namespace MyNetwork;

class DuplicationDetectorTest : public ::testing::Test
{

protected:
    void SetUp()
    {
        mock_group_factory_p = std::make_unique<MockSegmentGroupFactory>();
        tear_down = std::bind(&MockSegmentGroupFactory::clear_all_unused_groups, mock_group_factory_p.get());
    }

    void TearDown()
    {
        tear_down();
    }

    std::unique_ptr<MockSegmentGroupFactory> mock_group_factory_p;

private:
    std::function<void()> tear_down;
};

TEST_F(DuplicationDetectorTest, AddASegment)
{
    Segment a_segment = create_segment(Parity::Mixed, 1, 5);
    mock_group_factory_p->fill_mock_groups(1);
    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[0], add(a_segment));
    DuplicationDetector dd{std::move(mock_group_factory_p)};
    dd.add_segment(a_segment);
}

TEST_F(DuplicationDetectorTest, AddSameLocationSegment)
{
    Segment a_segment = create_segment(Parity::Mixed, 1, 5);
    Segment same_location_segment = create_segment(Parity::Mixed, 7, 9);
    mock_group_factory_p->fill_mock_groups(1);

    InSequence s;
    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[0], add(a_segment));
    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[0], add(same_location_segment));

    DuplicationDetector dd{std::move(mock_group_factory_p)};
    dd.add_segment(a_segment);
    dd.add_segment(same_location_segment);
}

TEST_F(DuplicationDetectorTest, AddDifferentLocationSegment)
{
    Segment a_segment = create_segment(Parity::Mixed, 1, 5);
    Segment different_location_segment = create_segment(Parity::Mixed, 7, 9, "9999");
    mock_group_factory_p->fill_mock_groups(2);

    InSequence s;
    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[0], add(a_segment));
    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[1], add(different_location_segment));

    DuplicationDetector dd{std::move(mock_group_factory_p)};
    dd.add_segment(a_segment);
    dd.add_segment(different_location_segment);
}

TEST_F(DuplicationDetectorTest, GetZeroDuplications)
{
    mock_group_factory_p->fill_mock_groups(0);
    DuplicationDetector dd{std::move(mock_group_factory_p)};

    EXPECT_EQ(dd.get_all_duplications().size(), 0);
}

TEST_F(DuplicationDetectorTest, GetDuplicationsFromThreeGroups)
{
    Segment segment_location1 = create_segment(Parity::Mixed, 1, 5);
    Segment segment_location2 = create_segment(Parity::Mixed, 7, 9, "9999");
    Segment segment_location3 = create_segment(Parity::Mixed, 7, 9, "9999", "Petőfi utca");
    mock_group_factory_p->fill_mock_groups(3);

    std::deque<Segment> location1_duplications{
        create_segment(Parity::Mixed, 1, 5),
        create_segment(Parity::Mixed, 9, 15)};

    std::deque<Segment> location2_duplications{
        create_segment(Parity::Mixed, 7, 13, "9999"),
        create_segment(Parity::Mixed, 17, 31, "9999")};

    std::deque<Segment> location3_duplications{
        create_segment(Parity::Mixed, 7, 13, "9999", "Petőfi utca"),
        create_segment(Parity::Mixed, 17, 31, "9999", "Petőfi utca")};

    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[0], get_all_duplications())
        .WillOnce(Return(location1_duplications));

    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[1], get_all_duplications())
        .WillOnce(Return(location2_duplications));

    EXPECT_CALL(*mock_group_factory_p->created_mock_segment_groups[2], get_all_duplications())
        .WillOnce(Return(location3_duplications));

    DuplicationDetector dd{std::move(mock_group_factory_p)};
    dd.add_segment(segment_location1);
    dd.add_segment(segment_location2);
    dd.add_segment(segment_location3);

    std::deque<Segment> result = dd.get_all_duplications();
    EXPECT_THAT(result, IsSupersetOf(location1_duplications));
    EXPECT_THAT(result, IsSupersetOf(location2_duplications));
    EXPECT_THAT(result, IsSupersetOf(location3_duplications));
}