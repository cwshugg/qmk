// This implements the function prototypes from activity.h.

// Includes
#include "defines.h"
#include "activity.h"

// Globals
static uint32_t __P(activity_timer) = 0;
static __P(activity_state_e) __P(activity_state) = ACTIVITY_STATE_ALIVE;
static keyrecord_t __P(activity_keylog_latest_record);
static uint16_t __P(activity_keylog_latest_keycode);
static uint8_t __P(activity_capslock_flag) = 0;

// ============================ Activity Keylog ============================= //
void __P(activity_keylog_update)(uint16_t keycode, keyrecord_t* record)
{
    __P(activity_keylog_latest_keycode) = keycode;
    memcpy(&__P(activity_keylog_latest_record), record, sizeof(keyrecord_t));
}

keyrecord_t* __P(activity_keylog_get_record)(void)
{
    return &__P(activity_keylog_latest_record);
}

uint16_t __P(activity_keylog_get_code)(void)
{
    return __P(activity_keylog_latest_keycode);
}


// ============================= Activity State ============================= //
void __P(activity_state_set)(__P(activity_state_e) state)
{
    __P(activity_state) = state;
}

__P(activity_state_e) __P(activity_state_get)()
{
    return __P(activity_state);
}

__P(activity_state_e) __P(activity_state_refresh)()
{
    // refresh and retrieve the activity timer value
    uint32_t t = __P(activity_timer_get)();

    // depending on how much time has passed, set the state
    if (t >= 60000)
    { __P(activity_state_set)(ACTIVITY_STATE_DEAD); }
    else if (t >= 30000 && t < 60000)
    { __P(activity_state_set)(ACTIVITY_STATE_IDLE); }
    else
    { __P(activity_state_set)(ACTIVITY_STATE_ALIVE); }

    return __P(activity_state);
}


// ============================= Activity Timer ============================= //
void __P(activity_timer_refresh)()
{
    // only the master updates the activity timer; the secondary side of the
    // keyboard syncs with the master side to retrieve its value
    if (is_keyboard_master())
    { __P(activity_timer) = timer_read32(); }
}

uint32_t __P(activity_timer_get)()
{
    // only the master calculates the elapsed time; the secondary side receives
    // this value pre-calculated, so should return it as-is
    if (is_keyboard_master())
    { return timer_elapsed32(__P(activity_timer)); }
    return __P(activity_timer);
}

uint32_t __P(activity_timer_get_raw)()
{
    return __P(activity_timer);
}

void __P(activity_timer_set_raw)(uint32_t value)
{
    __P(activity_timer) = value;
}


// =========================== Caps Lock Tracking =========================== //
void __P(activity_capslock_set)(uint8_t enabled)
{
    __P(activity_capslock_flag) = !!enabled;
}

uint8_t __P(activity_capslock_get)()
{
    return !!__P(activity_capslock_flag);
}

uint8_t __P(activity_capslock_toggle)()
{
    // flip the flag and return
    __P(activity_capslock_flag) = !__P(activity_capslock_flag);
    return __P(activity_capslock_flag);
}


// =========================== Firmware Overrides =========================== //
// Function supported by QMK that allows user code to process keyboard events,
// such as keypresses.
bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    // if a key was pressed, update our activity timer and keylog
    if (record->event.pressed)
    {
        __P(activity_timer_refresh)();
        __P(activity_keylog_update)(keycode, record);

        // if the caps lock key was pressed, update the internal state
        if (keycode == KC_CAPS)
        { __P(activity_capslock_toggle)(); }
    }

    return true;
}

