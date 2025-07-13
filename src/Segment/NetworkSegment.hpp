#pragma once
#include "NetworkRecord.hpp"
#include <vector>
#include <string>

// TODO: use forward iterator instead of vector

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
        decltype(NetworkRecord::L_POSTAL_CODE) postal_code;
        std::string STREET_NAME_AND_TYPE;
        Parity parity;
        decltype(NetworkRecord::FROMLEFT) from_street_number;
        decltype(NetworkRecord::TOLEFT) to_street_number;
    };
}

std::ostream& operator<<(std::ostream& os, const MyNetwork::Segment&);
