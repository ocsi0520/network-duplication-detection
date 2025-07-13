#include "SegmentMapper.hpp"

using namespace MyNetwork;

std::vector<Segment> SegmentMapper::map_from_record(const NetworkRecord &nw)
{
    std::vector<Segment> result;
    if (is_valid_parity(nw.SCHEMELEFT))
    {
        result.push_back(
            Segment{
                .postal_code = nw.L_POSTAL_CODE,
                .STREET_NAME_AND_TYPE = nw.STRET_NAME + " " + nw.STRET_TYPE,
                .parity = static_cast<Parity>(nw.SCHEMELEFT),
                .from_street_number = nw.FROMLEFT,
                .to_street_number = nw.TOLEFT,
            });
    }

    if (is_valid_parity(nw.SCHEMERIGHT))
    {
        result.push_back(
            Segment{
                .postal_code = nw.R_POSTAL_CODE,
                .STREET_NAME_AND_TYPE = nw.STRET_NAME + " " + nw.STRET_TYPE,
                .parity = static_cast<Parity>(nw.SCHEMERIGHT),
                .from_street_number = nw.FROMRIGHT,
                .to_street_number = nw.TORIGHT,
            });
    }

    return result;
}