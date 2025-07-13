#pragma once
#include <string>

namespace MyNetwork
{
  struct NetworkRecord
  {
    int ID;
    int FROM_NODE;
    int TO_NODE;
    /*3+1 char*/ std::string FRC_A;
    int FOW;
    /*2+1*/ std::string ONEWAY;
    char STRUCTURE;
    int _not_documented_1;
    char TOLL;
    /* 7+1char */ std::string VTR;
    int SPEED_LIMIT;
    int SPEED_LIMIT_VALID;
    int KPH;
    int FROM_LEVEL;
    int TO_LEVEL;
    int _not_documented_2;
    // TODO: typo STREET not STRET
    std::string STRET_NAME;
    std::string STRET_TYPE;
    std::string ROAD_NAME;
    std::string ALT_NAME;
    char SCHEMELEFT;
    int FROMLEFT;
    int TOLEFT;
    char SCHEMERIGHT;
    int FROMRIGHT;
    int TORIGHT;
    std::string L_ORDER8_NAME;
    std::string R_ORDER8_NAME;
    std::string L_ORDER9_NAME;
    std::string R_ORDER9_NAME;
    int ADMINIDX_L;
    int ADMINIDX_R;
    /* 6+1char */ std::string L_POSTAL_CODE;
    /* 6+1char */ std::string R_POSTAL_CODE;
  };
}
