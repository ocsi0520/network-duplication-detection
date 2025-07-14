#pragma once
#include "NetworkRecord.hpp"
#include <vector>
#include <string>

namespace MyNetwork
{
    enum class Parity
    {
        Odd = 'O',
        Even = 'E',
        Mixed = 'M'
    };

    bool is_valid_parity(char examined_value);

    struct Segment
    {
        std::string postal_code;
        std::string STREET_NAME_AND_TYPE;
        Parity parity;
        int from_street_number;
        int to_street_number;

        auto operator<=>(const MyNetwork::Segment &) const = default;
    };
}

std::ostream &operator<<(std::ostream &os, const MyNetwork::Segment &);
