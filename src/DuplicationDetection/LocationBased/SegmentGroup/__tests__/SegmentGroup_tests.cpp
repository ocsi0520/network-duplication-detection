#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "LocationBased/SegmentGroup/SegmentGroup.hpp"
#include "LocationBased/UniqueList/__tests__/UniqueListFactory_mock.hpp"
#include "LocationBased/UniqueList/__tests__/UniqueList_mock.hpp"
#include "Segment/__tests__/TestSegment.hpp"
#include <memory>

using namespace MyNetwork;
using namespace ::testing;

class SegmentGroupTest : public Test
{
public:
    virtual void fillFactory()
    {
        EXPECT_CALL(*mock_factory_pointer, create_unique_list())
            .WillOnce(Return(std::move(mock_ul_mixed_pointer)))
            .WillOnce(Return(std::move(mock_ul_odd_pointer)))
            .WillOnce(Return(std::move(mock_ul_even_pointer)));
    }

    std::unique_ptr<MockUniqueList> mock_ul_mixed_pointer;
    std::deque<Segment> mixed_duplications;

    std::unique_ptr<MockUniqueList> mock_ul_odd_pointer;
    std::deque<Segment> odd_duplications;

    std::unique_ptr<MockUniqueList> mock_ul_even_pointer;
    std::deque<Segment> even_duplications;

    std::shared_ptr<MockUniqueListFactory> mock_factory_pointer;

    virtual void fill_duplication_lists(size_t mixed, size_t even, size_t odd)
    {
        fill_even(even);
        fill_odd(odd);
        fill_mixed(mixed);
    }

protected:
    virtual void SetUp()
    {
        mock_ul_mixed_pointer = std::make_unique<MockUniqueList>();
        mock_ul_odd_pointer = std::make_unique<MockUniqueList>();
        mock_ul_even_pointer = std::make_unique<MockUniqueList>();
        mock_factory_pointer = std::make_shared<MockUniqueListFactory>();
    }

    virtual void fill_mixed(size_t n)
    {
        mixed_duplications.clear();
        for (size_t i = 0; i < n; i++)
            mixed_duplications.push_back(create_segment(Parity::Mixed, i * 3 + 1, i * 3 + 2));

        EXPECT_CALL(*mock_ul_mixed_pointer, get_all_duplications()).Times(1).WillOnce(ReturnRef(std::as_const(mixed_duplications)));
    }

    virtual void fill_even(size_t n)
    {
        even_duplications.clear();

        for (size_t i = 0; i < n; i++)
            even_duplications.push_back(create_segment(Parity::Even, i * 6 + 2, i * 6 + 4));

        EXPECT_CALL(*mock_ul_even_pointer, get_all_duplications()).Times(1).WillOnce(ReturnRef(even_duplications));
    }

    virtual void fill_odd(size_t n)
    {
        odd_duplications.clear();

        for (size_t i = 0; i < n; i++)
            odd_duplications.push_back(create_segment(Parity::Odd, i * 6 + 1, i * 6 + 3));

        EXPECT_CALL(*mock_ul_odd_pointer, get_all_duplications())
            .Times(1)
            .WillOnce(ReturnRef(odd_duplications));
    }
};

void state_expectations_with_one(SegmentGroupTest &fixture, const Segment &segment)
{
    if (segment.parity == Parity::Mixed)
        EXPECT_CALL(*(fixture.mock_ul_mixed_pointer), add_segment(segment)).Times(1);
    else
        EXPECT_CALL(*(fixture.mock_ul_mixed_pointer), add_segment(_)).Times(0);

    if (segment.parity == Parity::Odd)
        EXPECT_CALL(*(fixture.mock_ul_odd_pointer), add_segment(segment)).Times(1);
    else
        EXPECT_CALL(*(fixture.mock_ul_odd_pointer), add_segment(_)).Times(0);

    if (segment.parity == Parity::Even)
        EXPECT_CALL(*(fixture.mock_ul_even_pointer), add_segment(segment)).Times(1);
    else
        EXPECT_CALL(*(fixture.mock_ul_even_pointer), add_segment(_)).Times(0);
}

TEST_F(SegmentGroupTest, AddOneOddSegment)
{
    Segment odd_duplications = create_segment(Parity::Odd, 1, 3);
    state_expectations_with_one(*this, odd_duplications);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    segment_group.add(odd_duplications);
}

TEST_F(SegmentGroupTest, AddOneEvenSegment)
{
    Segment even_duplications = create_segment(Parity::Even, 2, 4);
    state_expectations_with_one(*this, even_duplications);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    segment_group.add(even_duplications);
}

TEST_F(SegmentGroupTest, AddOneMixedSegment)
{
    Segment mixed_duplications = create_segment(Parity::Mixed, 1, 4);
    state_expectations_with_one(*this, mixed_duplications);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    segment_group.add(mixed_duplications);
}

TEST_F(SegmentGroupTest, ProvideZero)
{
    fill_duplication_lists(0, 0, 0);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_EQ(segment_group.get_all_duplications().size(), 0);
}

TEST_F(SegmentGroupTest, ProvideOneOdd)
{
    fill_duplication_lists(0, 0, 1);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(odd_duplications));
}

TEST_F(SegmentGroupTest, ProvideThreeOdds)
{
    fill_duplication_lists(0, 0, 3);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(odd_duplications));
}

TEST_F(SegmentGroupTest, ProvideOneEven)
{
    fill_duplication_lists(0, 1, 0);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(even_duplications));
}

TEST_F(SegmentGroupTest, ProvideThreeEvens)
{
    fill_duplication_lists(0, 3, 0);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(even_duplications));
}

// mixed

TEST_F(SegmentGroupTest, ProvideOneMixed)
{
    fill_duplication_lists(1, 0, 0);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(mixed_duplications));
}

TEST_F(SegmentGroupTest, ProvideThreeMixeds)
{
    fill_duplication_lists(3, 0, 0);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    EXPECT_THAT(segment_group.get_all_duplications(), ContainerEq(mixed_duplications));
}

TEST_F(SegmentGroupTest, ProvideEachOne)
{
    fill_duplication_lists(1, 1, 1);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    auto result = segment_group.get_all_duplications();
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result, IsSupersetOf(odd_duplications));
    EXPECT_THAT(result, IsSupersetOf(even_duplications));
    EXPECT_THAT(result, IsSupersetOf(mixed_duplications));
}

TEST_F(SegmentGroupTest, ProvideThreeFromEachOne)
{
    fill_duplication_lists(3, 3, 3);
    fillFactory();
    SegmentGroup segment_group{mock_factory_pointer};
    auto result = segment_group.get_all_duplications();
    EXPECT_EQ(result.size(), 9);
    EXPECT_THAT(result, IsSupersetOf(odd_duplications));
    EXPECT_THAT(result, IsSupersetOf(even_duplications));
    EXPECT_THAT(result, IsSupersetOf(mixed_duplications));
}