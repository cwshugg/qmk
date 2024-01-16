// This defines function prototypes for interacting with my code's activity
// timer, which is responsible for tracking the latest keyboard activity from
// the user.

#if !defined(CWSHUGG_CRKBD_ACTIVITY_H)
#define CWSHUGG_CRKBD_ACTIVITY_H

// Includes
#include QMK_KEYBOARD_H
#include "defines.h"


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

#endif

