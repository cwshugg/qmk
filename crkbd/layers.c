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
        default:
            return "???";
    }
}
