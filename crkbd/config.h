// My keyboard's QMK configuration header file.

#if !defined(CWSHUGG_CRKBD_CONFIG_H)
#define CWSHUGG_CRKBD_CONFIG_H

// Set the left-hand crkbd PCB as the master.
#define MASTER_LEFT

// Setting the TT() layer-change macro to use 3 taps instead of the default (5)
#if defined(TAPPING_TOGGLE)
#undef TAPPING_TOGGLE
#endif
#define TAPPING_TOGGLE 3

// Set tap-dancing configurations
#if defined(TAPPING_TERM)
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 200

#endif


