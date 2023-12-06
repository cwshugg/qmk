// This defines data structures and function prototypes for using the QMK Tap
// Dance feature.

#if !defined(CWSHUGG_CRKBD_TD_H)
#define CWSHUGG_CRKBD_TD_H

// Includes
#include "defines.h"

// Enum for defining specific tap dance routines
typedef enum __P(td_code)
{
    TD_TG,          // Tab with one tap, grave with double-tap
    TD_SC,          // Shift with one tap, caps lock with double-tap
} __P(td_code_e);

#endif

