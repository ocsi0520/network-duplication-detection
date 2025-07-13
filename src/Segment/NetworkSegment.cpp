#include "NetworkSegment.hpp"

bool MyNetwork::is_valid_parity(char examined_value)
{
    return examined_value == static_cast<char>(Parity::Odd) ||
           examined_value == static_cast<char>(Parity::Even) ||
           examined_value == static_cast<char>(Parity::Mixed);
}