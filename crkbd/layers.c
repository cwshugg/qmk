// Implements the function prototypes in layers.h.

// Includes
#include "layers.h"
#include "defines.h"

char* __P(layer_to_string)(__P(layer_e) l)
{
    switch (l)
    {
        case LAYER_0_DEFAULT:
            return "DEF";
        case LAYER_1_LOWER:
            return "LWR";
        case LAYER_2_RAISE:
            return "RSE";
        case LAYER_3_SUPER:
            return "SPR";
        case LAYER_4_GAMING_0:
            return "GM0";
        case LAYER_5_GAMING_1:
            return "GM1";
        case LAYER_6_GAMING_2:
            return "GM2";
        case LAYER_7_GAMING_3:
            return "GM3";
        default:
            return "???";
    }
}
