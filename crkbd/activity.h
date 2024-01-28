// This defines function prototypes for interacting with my code's activity
// timer, which is responsible for tracking the latest keyboard activity from
// the user.

#if !defined(CWSHUGG_CRKBD_ACTIVITY_H)
#define CWSHUGG_CRKBD_ACTIVITY_H

// Includes
#include QMK_KEYBOARD_H
#include "defines.h"
#include "layers.h"


// ============================ Activity Keylog ============================= //
// Takes in a key record and uses it to update the internal keylog.
void __P(activity_keylog_update)(uint16_t keycode, keyrecord_t* record);

// Returns a pointer to the most recent key record from the keylog.
keyrecord_t* __P(activity_keylog_get_record)(void);

// Returns a pointer to the most recent key code from the keylog.
uint16_t __P(activity_keylog_get_code)(void);


// ============================= Activity State ============================= //
// The keyboard's "activity state" is used to determine how recently the
// keyboard has been used.
typedef enum __P(activity_state)
{
    ACTIVITY_STATE_DEAD,    // keyboard hasn't been used in a while
    ACTIVITY_STATE_IDLE,    // keyboard was used somewhat recently
    ACTIVITY_STATE_ALIVE    // keyboard is currently (or very recently) in use
} __P(activity_state_e);

// Sets the keyboard's current activity state.
void __P(activity_state_set)(__P(activity_state_e) state);

// Returns the keyboard's current activity state.
__P(activity_state_e) __P(activity_state_get)(void);

// Updates the activity state based on the activity timer. The new state is
// returned.
__P(activity_state_e) __P(activity_state_refresh)(void);


// ============================= Activity Timer ============================= //
// Updates the activity timer's value to be current.
void __P(activity_timer_refresh)(void);

// Returns the activity timer's current time since it was last checked.
uint32_t __P(activity_timer_get)(void);

// Returns the activity timer's raw value.
uint32_t __P(activity_timer_get_raw)(void);

// Sets the activity timer's raw value.
void __P(activity_timer_set_raw)(uint32_t value);


// =========================== Caps Lock Tracking =========================== //
// Takes in a flag (0 for false, non-zero for true) indicating the current
// state of the caps lock. This stores the given value in a global variable.
void __P(activity_capslock_set)(uint8_t enabled);

// Returns non-zero if the global state of the caps lock key indicates that
// caps lock is enabled. Returns zero otherwise.
uint8_t __P(activity_capslock_get)(void);

// Flips the internal caps lock state and returns its new value.
uint8_t __P(activity_capslock_toggle)(void);


// ============================= Layer Tracking ============================= //
// Invokes QMK layer-retrieving code to retrieve and store the current layer
// state. Returns the current layer value.
__P(layer_e) __P(activity_layer_refresh)(void);

// Sets the internal layer state to the given layer value.
void __P(activity_layer_set)(__P(layer_e) layer);

// Returns the current internal layer state.
__P(layer_e) __P(activity_layer_get)(void);


#endif

