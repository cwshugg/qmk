// Implements functions for driving the OLED screens on the crkbd.

#if defined(OLED_ENABLE)

// Includes
#include QMK_KEYBOARD_H
#include "defines.h"
#include "layers.h"
#include "activity.h"

// Globals
static char __P(oled_keylog_pos_str)[8] = {'\0'};
static char __P(oled_keylog_code_str)[8] = {'\0'};

// Function prototypes (QMK uses -Werror=strict-prototypes) during compilation
static void __P(oled_write_space)(void);
static void __P(oled_write_separator)(char character);
static void __P(oled_write_header)(void);
static void __P(oled_write_layer_name)(void);
static void __P(oled_write_keylog_position)(void);
static void __P(oled_write_keylog_code)(void);
static void __P(oled_write_mods)(void);
static void __P(oled_write_art)(void);
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
static void __P(oled_write_separator)(char character)
{
    // by default (character=0), use dashes
    if (character == 0)
    {
        oled_write("-----", false);
    }
    else
    {
        char str[6];
        snprintf(str, 6, "%c%c%c%c%c",
                 character,
                 character,
                 character,
                 character,
                 character);

        oled_write(str, false);
    }
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
    oled_write("Layer", false);
    __P(oled_write_separator)(0);
    oled_write(" ", false);
    oled_write(name, false);
    oled_write(" ", false);
}

// Writes the latest keypress' position.
static void __P(oled_write_keylog_position)()
{
    // build a string to show the latest keypress position
    keyrecord_t* r = __P(activity_keylog_get_record)();
    snprintf(__P(oled_keylog_pos_str), sizeof(__P(oled_keylog_pos_str)),
             "R%d C%d",
             r->event.key.row,
             r->event.key.col);

    // write out to the string
    oled_write("Key-P", false);
    __P(oled_write_separator)(0);
    oled_write(__P(oled_keylog_pos_str), false);
}

// Writes the latest keypress' code.
static void __P(oled_write_keylog_code)()
{
    // build a string to show the latest keypress code
    uint16_t c = __P(activity_keylog_get_code)();
    snprintf(__P(oled_keylog_code_str), sizeof(__P(oled_keylog_code_str)),
             "%05d", c);

    oled_write("Key-C", false);
    __P(oled_write_separator)(0);
    oled_write(__P(oled_keylog_code_str), false);
}

// Writes the current modifier keys that are pressed.
static void __P(oled_write_mods)()
{
    // get a bitmap of the currently active modifier keys
    uint8_t mods = get_mods();
    uint8_t mod_ctl = mods & MOD_MASK_CTRL;
    uint8_t mod_alt = mods & MOD_MASK_ALT;
    uint8_t mod_sft = mods & MOD_MASK_SHIFT;
    uint8_t mod_os = mods & MOD_MASK_GUI;
    uint8_t mod_caps = __P(activity_capslock_get)();
    // write the modifier key states
    oled_write(mod_ctl ?  " CTL " : "     ", mod_ctl);
    oled_write(mod_alt ?  " ALT " : "     ", mod_alt);
    oled_write(mod_sft ?  " SFT " : "     ", mod_sft);
    oled_write(mod_os ?   " OS  " : "     ", mod_os);
    oled_write(mod_caps ? " CAP " : "     ", mod_caps);
}

static void __P(oled_write_art)()
{
    // if the current layer is one of the gaming layers, draw gaming art
    __P(layer_e) layer = get_highest_layer(layer_state);
    if (layer >= LAYER_4_GAMING_0 && layer <= LAYER_7_GAMING_3)
    {
        // TODO - fix this - currently not displaying on right screen
        oled_write(" .^. ", false);
        oled_write(" | | ", false);
        oled_write(" | | ", false);
        oled_write(" | | ", false);
        oled_write(" | | ", false);
        oled_write(" | | ", false);
        oled_write("=====", false);
        oled_write("  #  ", false);
        oled_write("  #  ", false);
    }
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

    // draw a little "idling" animation
    uint32_t timer = __P(activity_timer_get)();
    uint32_t tval = timer % 1000;
    if (tval < 250)
    { oled_write("|   |", false); }
    else if (tval >= 250 && tval < 500)
    { oled_write("/   \\", false); }
    else if (tval >= 500 && tval < 750)
    { oled_write("-   -", false); }
    else if (tval >= 750 && tval < 1000)
    { oled_write("\\   /", false); }

    return false;
}

// Performs all OLED rendering on the primary screen while the keyboard is
// active.
static bool __P(oled_primary_task_alive)()
{
    __P(oled_write_header)();
    __P(oled_write_separator)('=');
    __P(oled_write_space)();

    __P(oled_write_layer_name)();
    __P(oled_write_space)();

    __P(oled_write_keylog_position)();
    __P(oled_write_space)();
    __P(oled_write_keylog_code)();
    return false;
}

// Performs all OLED rendering on the secondary screen while the keyboard is
// active.
static bool __P(oled_secondary_task_alive)()
{
    __P(oled_write_mods)();
    __P(oled_write_space)();
    __P(oled_write_art)();
    return false;
}


// ============================= OLED Overrides ============================= //
// Overridden OLED firmware function that performs initialization for the OLED
// screen.
oled_rotation_t oled_init_user(oled_rotation_t r)
{
    // zero out the keylog string
    memset(__P(oled_keylog_pos_str), 0, sizeof(__P(oled_keylog_pos_str)));
    memset(__P(oled_keylog_code_str), 0, sizeof(__P(oled_keylog_code_str)));

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

