// This header file includes preprocessor defines and other things used
// throughout the code.

#if !defined(CWSHUGG_CRKBD_DEFINES_H)
#define CWSHUGG_CRKBD_DEFINES_H

// Prefix used for all my code's symbols (functions, data structures, etc.)
#define __P(name) __cwshugg_crkbd_##name

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

#endif

