#include "NetworkSegment.hpp"
#include <string>
#include <iostream>

bool MyNetwork::is_valid_parity(char examined_value)
{
    return examined_value == static_cast<char>(Parity::Odd) ||
           examined_value == static_cast<char>(Parity::Even) ||
           examined_value == static_cast<char>(Parity::Mixed);
}

std::ostream &operator<<(std::ostream &os, const MyNetwork::Segment &ns)
{
    return os << ns.STREET_NAME_AND_TYPE << ": " << static_cast<char>(ns.parity)
              << " " << ns.from_street_number << " " << ns.to_street_number;
}
