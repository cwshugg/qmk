// My keyboard's QMK configuration header file.

#if !defined(CWSHUGG_CRKBD_CONFIG_H)
#define CWSHUGG_CRKBD_CONFIG_H

// Set the left-hand crkbd PCB as the master.
#define MASTER_LEFT

// Define custom split keyboard data synchronization transaction IDs.
// This is used by sync.h/sync.c to synchronize data between the primary and
// secondary sides of the keyboard.
#define SPLIT_TRANSACTION_IDS_USER CWSHUGG_CRKBD_SYNC_TRANSACTION_UPDATE
#define RPC_M2S_BUFFER_SIZE 40  // increase data sync buffer size (default = 32)
#define RPC_S2M_BUFFER_SIZE 40

// Setting the TT() layer-change macro to use 3 taps instead of the default (5)
#if defined(TAPPING_TOGGLE)
#undef TAPPING_TOGGLE
#endif
#define TAPPING_TOGGLE 3

// Set tap-dancing configurations
#if defined(TAPPING_TERM)
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 150

#endif

