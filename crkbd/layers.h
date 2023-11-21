// This header file defines the available layers in the keyboard, along with
// any helper functions.

#if !defined(CWSHUGG_CRKBD_LAYERS_H)
#define CWSHUGG_CRKBD_LAYERS_H

// Includes
#include "defines.h"

// Enum that defines all available layers on the keyboard.
typedef enum __P(layer)
{
    LAYER_0_DEFAULT,
    LAYER_1_LOWER,
    LAYER_2_RAISE,
    LAYER_3_SUPER,
    // LAYER_4_GAMING_0, // TODO
    // ------------
    LAYER_COUNT        // Specifies the total number of defined layer enums
} __P(layer_e);

// Function prototype that accepts a layer enum AND returns a string
// representing the layer's name.
char* __P(layer_to_string)(__P(layer_e) l);

#endif

