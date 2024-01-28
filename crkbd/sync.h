// This header file defines data structures and function prototypes used to
// synchronize the primary and secondary side of the keyboard. QMK includes a
// way to send data across the CRKBD's TRRS connection.

#if !defined(CWSHUGG_CRKBD_SYNC_H)
#define CWSHUGG_CRKBD_SYNC_H

// Includes
#include "defines.h"
#include "activity.h"


// ============================ Data Structures ============================= //
// A struct representing several different flags to help with synchronizing
// information between the two sides of the keyboard.
typedef struct __P(sync_data)
{
    uint8_t capslock_enabled:1;     // flag - whether or not caps lock is on
    uint8_t layer:4;                // current layer value
    uint8_t _unused:3;
} __P(sync_data_t);

// This struct contains all data sent from the primary side of the keyboard to
// the secondary side.
typedef struct __P(sync_p2s)
{
    uint8_t mods;                   // bit flags from get_mods() (modifier keys)
    uint32_t activity_timer;        // current keyboard activity timer value
    __P(sync_data_t) data;          // custom flags/data for my code to use
} __P(sync_p2s_t);

// This struct contains all data sent from the secondary side of the keyboard
// to the primary side.
typedef struct __P(sync_s2p)
{
    uint8_t _unused;
} __P(sync_s2p_t);


// ============================= Sync Interface ============================= //
// Initialization function for split keyboard synchronization.
void __P(sync_init)(void);

// Slave-side handler for receiving the "update" transaction sent by the
// primary.
void __P(sync_transaction_p2s_update)(uint8_t in_len, const void* in_data,
                                      uint8_t out_len, const void* out_data);

#endif

