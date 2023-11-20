// This defines the keymappings for the various layers.

#include QMK_KEYBOARD_H

// Includes
#include "defines.h"
#include "layers.h"

// Empty/transparent key aliases
#define _______E        KC_NO               // empty key (does nothing)
#define _______T        KC_TRANSPARENT      // transparent key (falls through to lower layer)

// Media key aliases
#define KC_M_MT         KC_AUDIO_MUTE       // media mute key
#define KC_M_VU         KC_AUDIO_VOL_UP     // media volume up key
#define KC_M_VD         KC_AUDIO_VOL_DOWN   // media volume down key
#define KC_M_PP         KC_MEDIA_PLAY_PAUSE // media play/pause
#define KC_M_NT         KC_MEDIA_NEXT_TRACK // media next track
#define KC_M_PT         KC_MEDIA_PREV_TRACK // media prev track

// Keymapping
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // DEFAULT LAYER
    // This layer is the default when the keyboard is powered on and uses the QWERTY layout.
    // Modifier keys are on the left and right ends, and layer movement is done on the thumb keys.
    [LAYER_0_DEFAULT] = LAYOUT_split_3x6_3(
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,                            KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_LCTL,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,                            KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_DEL,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_LALT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,                            KC_N,      KC_M,      KC_COMMA,  KC_DOT,    KC_SLASH,  KC_LSFT,
    // +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+ //
                                         KC_LGUI,   MO(LAYER_1_LOWER),    KC_ENTER,  KC_SPC,    MO(LAYER_2_RAISE),    KC_ESC
    //                                  +----------+---------------------+----------+----------+---------------------+----------+
    ),
    
    // LOWER LAYER
    // This layer holds symbols, arrow keys, and other navigation keys.
    [LAYER_1_LOWER] = LAYOUT_split_3x6_3(
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_PIPE,   KC_GRAVE,  KC_DQUO,   KC_LPRN,   KC_RPRN,   KC_AMPR,                         KC_INSERT, KC_HOME,   KC_PGUP,   _______E,  _______E,  _______E,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_BSLS,   KC_HASH,   KC_QUOT,   KC_LBRC,   KC_RBRC,   KC_UNDS,                         KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______E,  _______E,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        KC_TILD,   KC_AT,     KC_CIRC,   KC_LCBR,   KC_RCBR,   KC_DLR,                          _______E,  KC_END,    KC_PGDN,   _______E,  _______E,  KC_CAPS,
    // +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+ //
                                         _______E,  _______T,             KC_ENTER,  KC_SPC,    MO(LAYER_3_SUPER),    _______E
    //                                  +----------+---------------------+----------+----------+---------------------+----------+
    ),

    // RAISED LAYER
    // This layer contains numbers and a small number of symbols, as well as media keys.
    [LAYER_2_RAISE] = LAYOUT_split_3x6_3(
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  KC_M_MT,   KC_M_VD,   KC_M_VU,   KC_PSCR,                         KC_EQL,    KC_7,      KC_8,      KC_9,      KC_PLUS,   KC_EXLM,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  KC_M_PP,   KC_M_PT,   KC_M_NT,   _______E,                        KC_MINUS,  KC_4,      KC_5,      KC_6,      KC_ASTR,   KC_COLN,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  _______E,  _______E,  _______E,  _______E,                        KC_0,      KC_1,      KC_2,      KC_3,      KC_PERC,   KC_QUES,
    // +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+ //
                                         _______E,  MO(LAYER_3_SUPER),    KC_ENTER,  KC_SPC,    _______T,             _______E
    //                                  +----------+---------------------+----------+----------+---------------------+----------+
    ),

    // SUPER LAYER
    // This layer contains function keys.
    [LAYER_3_SUPER] = LAYOUT_split_3x6_3(
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  _______E,  _______E,  _______E,  _______E,                        _______E,  KC_F7,     KC_F8,     KC_F9,     KC_F12,    _______E,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  _______E,  _______E,  _______E,  _______E,                        _______E,  KC_F4,     KC_F5,     KC_F6,     KC_F11,    _______E,
    // +----------+----------+----------+----------+----------+----------+                     +----------+----------+----------+----------+----------+----------+ //
        _______E,  _______E,  _______E,  _______E,  _______E,  _______E,                        _______E,  KC_F1,      KC_F2,    KC_F3,     KC_F10,    _______E,
    // +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+ //
                                         _______E,  _______T,             KC_ENTER,  KC_SPC,    _______T,             _______E
    //                                  +----------+---------------------+----------+----------+---------------------+----------+
    )
};

