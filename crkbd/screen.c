// Implements functions for driving the OLED screens on the crkbd.

#if defined(OLED_ENABLE)

// Includes
#include QMK_KEYBOARD_H
#include "defines.h"
#include "layers.h"
#include "activity.h"

// Globals
static char __P(oled_keylog_str)[32] = {'\0'};

// Function prototypes (QMK uses -Werror=strict-prototypes) during compilation
static void __P(oled_write_space)(void);
static void __P(oled_write_separator)(void);
static void __P(oled_write_header)(void);
static void __P(oled_write_layer_name)(void);
static void __P(oled_write_keylog)(void);
static bool __P(oled_primary_task_idle)(void);
static bool __P(oled_secondary_task_idle)(void);
static bool __P(oled_primary_task_alive)(void);
static bool __P(oled_secondary_task_alive)(void);


// ============================== OLED Helpers ============================== //
// Writes an empty line to the OLED screen.
static void __P(oled_write_space)()
{
    oled_write("     ", false);
}

// Writes a line containing all dashes ("-") to the OLED screen.
static void __P(oled_write_separator)()
{
    oled_write("-----", false);
}

// Writes a small header string to the OLED string. The header goes at the top
// of the screen.
static void __P(oled_write_header)()
{
    oled_write("SHUGGCRKBD", false);
}

// Writes the current layer name to the OLED screen.
static void __P(oled_write_layer_name)()
{
    __P(layer_e) layer = get_highest_layer(layer_state);
    const char* name = __P(layer_to_string)(layer);
    oled_write("LAYER", false);
    oled_write(" ", false);
    oled_write(name, false);
    oled_write(" ", false);
}

// Writes the most recent keypress to the screen.
static void __P(oled_write_keylog)(void)
{
    keyrecord_t* r = __P(activity_keylog_get_record)();
    uint16_t c = __P(activity_keylog_get_code)();

    // build a strinng to represent each part of the keylog
    snprintf(__P(oled_keylog_str), sizeof(__P(oled_keylog_str)),
             "KEY-P" "R%d C%d" "KEY-C" "%05d",
             r->event.key.row,
             r->event.key.col,
             c);
    
    // write the string to the screen
    oled_write(__P(oled_keylog_str), false);
}

// Performs OLED rendering for the primary screen while the keyboard is in the
// idle state.
static bool __P(oled_primary_task_idle)()
{
    oled_clear();
    __P(oled_write_header)();
    return false;
}

// Performs OLED rendering for the secondary screen while the keyboard is in
// the idle state.
static bool __P(oled_secondary_task_idle)()
{
    oled_clear();
    __P(oled_write_header)();
    return false;
}

// Performs all OLED rendering on the primary screen while the keyboard is
// active.
static bool __P(oled_primary_task_alive)()
{
    __P(oled_write_header)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    __P(oled_write_layer_name)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    __P(oled_write_keylog)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    return false;
}

// Performs all OLED rendering on the secondary screen while the keyboard is
// active.
static bool __P(oled_secondary_task_alive)()
{
    __P(oled_write_header)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    __P(oled_write_layer_name)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    __P(oled_write_keylog)();
    __P(oled_write_separator)();
    __P(oled_write_space)();
    return false;
}


// ============================= OLED Overrides ============================= //
// Overridden OLED firmware function that performs initialization for the OLED
// screen.
oled_rotation_t oled_init_user(oled_rotation_t r)
{
    // zero out the keylog string
    memset(__P(oled_keylog_str), 0, sizeof(__P(oled_keylog_str)));

    // rotate both screens 270 degrees so they face the user
    return OLED_ROTATION_270;
}

// Overridden OLED firmware function used to render to the OLED screens.
bool oled_task_user()
{
    // get the keyboard's current activity state
    __P(activity_state_e) state = __P(activity_state_refresh)();

    // if the state is idle or dead, render accordingly
    if (state == ACTIVITY_STATE_DEAD)
    {
        // ture off the screen
        if (is_oled_on())
        { oled_off(); }
        return false;
    }
    else if (state == ACTIVITY_STATE_IDLE)
    {
        // run the idle tasks, differentiating between the primary/master and
        // secondary/slave OLEDs
        if (is_keyboard_master())
        { return __P(oled_primary_task_idle)(); }
        else
        { return __P(oled_secondary_task_idle)(); }
    }

    // otherwise, we'll consider the screen to be active. Turn it on if it
    // isn't already
    if (!is_oled_on())
    { oled_on(); }
    
    // if the keyboard is currently considered active (i.e. someone is
    // currently using it), differentiate between the master/primary and
    // slave/secondary screens
    if (is_keyboard_master())
    { return __P(oled_primary_task_alive)(); }
    else
    { return __P(oled_secondary_task_alive)(); }
}

#endif

