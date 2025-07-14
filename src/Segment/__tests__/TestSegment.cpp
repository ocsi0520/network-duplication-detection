#include "TestSegment.hpp"
#include <cassert>

using namespace MyNetwork;

Segment create_segment(Parity parity, int from, int to, std::string postal, std::string street)
{
    assert(parity == MyNetwork::Parity::Even ? from % 2 == 0 && to % 2 == 0 : true);
    assert(parity == MyNetwork::Parity::Odd ? from % 2 == 1 && to % 2 == 1 : true);

    MyNetwork::Segment s;
    s.postal_code = postal;
    s.STREET_NAME_AND_TYPE = street;
    s.parity = parity;
    s.from_street_number = from;
    s.to_street_number = to;
    return s;
}
