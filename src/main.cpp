#include <iostream>
#include "StreamReader.hpp"
#include "NetworkRecord.hpp"
#include <fstream>
#include <iostream>

#include "SegmentMapper.hpp"
#include <algorithm>

#include "SegmentMerger.hpp"

#include "DuplicationDetection/LocationBased/UniqueList/UniqueListFactory.hpp"
#include "DuplicationDetector.hpp"

using namespace MyNetwork;

std::vector<NetworkRecord> read_all_recrods()
{
    std::ifstream file{"data/network_utf8.csv"};
    if (!file)
    {
        std::cout << "Could not open file" << std::endl;
        return {};
    }
    MyNetwork::CellParser cell_parser;
    MyNetwork::LineParser line_parser{cell_parser};
    MyNetwork::DataStreamReader reader{file, line_parser};

    return reader.read_data();
}

std::vector<Segment> map_network_records_to_segments(const std::vector<NetworkRecord> &data)
{
    MyNetwork::SegmentMapper segment_mapper;
    std::vector<Segment> sv;

    std::for_each(data.begin(), data.end(), [&](const NetworkRecord &nw)
                  {
        auto segments = segment_mapper.map_from_record(nw);
        std::copy(segments.begin(), segments.end(), std::back_inserter(sv)); });

    return sv;
}

std::vector<Segment> get_all_segments()
{
    return map_network_records_to_segments(read_all_recrods());
}

int main()
{
    // TODO: dependency injection
    std::shared_ptr<SegmentMerger> shared_sm =
        std::make_shared<SegmentMerger>();
    std::shared_ptr<UniqueListFactory> shared_ul_f =
        std::make_shared<UniqueListFactory>(shared_sm);
    std::unique_ptr<SegmentGroupFactory> unique_group_factory =
        std::make_unique<SegmentGroupFactory>(shared_ul_f);
        
    DuplicationDetector detector{std::move(unique_group_factory)};
    unique_group_factory = nullptr;

    for (const Segment &segment : get_all_segments())
    {
        detector.add_segment(segment);
    }

    for (const Segment &duplicatum_segment : detector.get_all_duplications())
    {
        std::cout << duplicatum_segment << std::endl;
    }

    return 0;
}