#include <iostream>
#include "StreamReader.hpp"
#include "NetworkRecord.hpp"
#include <fstream>
#include <iostream>

#include "SegmentMapper.hpp"
#include <algorithm>

#include "SegmentMerger.hpp"
#include <optional>

using namespace MyNetwork;

// TODO: move implementation out of main.cpp

std::optional<Segment> detect_duplicates(const SegmentMerger &segment_merger, Segment &accumulator, const Segment &current)
{
    if (segment_merger.is_contiguous(accumulator, current))
    {
        if (segment_merger.has_intersection(accumulator, current))
        {
            return segment_merger.intersect_segment(accumulator, current);
        }

        accumulator = segment_merger.union_segment(accumulator, current);
    }
    else
    {
        accumulator = current;
    }

    // No duplicate
    return std::optional<Segment>{};
}

std::vector<Segment> get_sorted_segments(const std::vector<MyNetwork::NetworkRecord> &data)
{

    MyNetwork::SegmentMapper segment_mapper;
    std::vector<Segment> sv;

    std::for_each(data.begin(), data.end(), [&](const NetworkRecord &nw)
                  {
        auto segments = segment_mapper.map_from_record(nw);
        std::copy(segments.begin(), segments.end(), std::back_inserter(sv)); });

    std::sort(sv.begin(), sv.end(), [](const Segment &s1, const Segment &s2)
              {
        if (s1.postal_code != s2.postal_code)
            return s1.postal_code < s2.postal_code;

        if (s1.STREET_NAME_AND_TYPE != s2.STREET_NAME_AND_TYPE)
            return s1.STREET_NAME_AND_TYPE < s2.STREET_NAME_AND_TYPE;

        if (s1.parity != s2.parity)
            return s1.parity < s2.parity;

        if (s1.from_street_number != s2.from_street_number)
            return s1.from_street_number < s2.from_street_number;

        
            return s1.to_street_number < s2.to_street_number; });

    return sv;
}

// TODO: rename
// to sorted_segments
std::vector<Segment> get_unique_duplications(std::vector<Segment> &sv)
{
    SegmentMerger segment_merger;
    std::vector<Segment> duplicate_segments;
    Segment duplicate_accumulator = sv[0];
    std::for_each(sv.begin() + 1, sv.end(), [&](const Segment &current)
                  {
                    const auto& duplicate = detect_duplicates(segment_merger, duplicate_accumulator, current);
                    if (duplicate.has_value())
                        duplicate_segments.push_back(duplicate.value()); });

    std::vector<Segment> deduped;
    Segment previous = *sv.begin();
    std::for_each(sv.begin() + 1, sv.end(), [&](Segment &current)
                  {
        if (segment_merger.is_contiguous(previous, current)) {
            auto merged = segment_merger.union_segment(previous, current);
            auto& last_deduped = *deduped.rbegin();

            if (deduped.empty()) {
                deduped.push_back(merged);
                return;
            }
            if (segment_merger.is_contiguous(last_deduped, merged)) {
                last_deduped = segment_merger.union_segment(last_deduped, merged);
            } else {
                deduped.push_back(merged);
            }
        }

        previous = current; });
    return deduped;
}

int main()
{
    std::ifstream file{"data/network_utf8.csv"};
    if (!file)
    {
        std::cout << "Could not open file" << std::endl;
        return -1;
    }
    MyNetwork::CellParser cell_parser;
    MyNetwork::LineParser line_parser{cell_parser};
    MyNetwork::DataStreamReader reader{file, line_parser};

    auto data = reader.read_data();
    std::cout << "read data size: " << data.size() << std::endl;

    std::vector<Segment> sorted_segments{get_sorted_segments(data)};

    if (sorted_segments.size() == 0)
        return 0;

    std::vector<Segment> duplicate_segments = get_unique_duplications(sorted_segments);

    std::for_each(duplicate_segments.begin(), duplicate_segments.end(), [](const Segment &s)
                  { std::cout << s << "\n"; });

    std::cout << std::flush;
    return 0;
}