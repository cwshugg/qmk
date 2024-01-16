// This implements all functions defined in sync.h.

// Includes
#include "sync.h"
#include "transactions.h"

// A static-global timer used to prevent too frequent syncing between the two
// keyboard halves, combined with a global "sync rate", which defines the
// number of milliseconds that must occur between syncs.
static uint32_t __P(sync_timer) = 0;
static uint32_t __P(sync_rate) = 125;

// This is an overridden version of QMK's housekeeping function. It's
// recommended that data synchronization between the primary and secondary
// sides of the keyboard is done here.
void housekeeping_task_user()
{
    if (is_keyboard_master())
    {
        // if enough time has elapsed, the primary will perform a sync
        if (timer_elapsed32(__P(sync_timer)) > __P(sync_rate))
        {
            __P(sync_p2s_t) data_in;
            __P(sync_s2p_t) data_out;

            // fill in the input data's values
            data_in.mods = get_mods();
            data_in.activity_timer = __P(activity_timer_get_raw)();

            // send the transaction
            if (transaction_rpc_exec(CWSHUGG_CRKBD_SYNC_TRANSACTION_UPDATE,
                                     sizeof(__P(sync_p2s_t)), &data_in,
                                     sizeof(__P(sync_s2p_t)), &data_out))
            {
                // on success, reset the timer
                __P(sync_timer) = timer_read32();
            }
            else
            {
                // on failure... TODO
            }
        }
    }
}


// ============================= Sync Interface ============================= //
void __P(sync_init)(void)
{
    // register the secondary-side handler
    transaction_register_rpc(CWSHUGG_CRKBD_SYNC_TRANSACTION_UPDATE,
                             (slave_callback_t) __P(sync_transaction_p2s_update));
}

void __P(sync_transaction_p2s_update)(uint8_t in_len, const void* in_data,
                                      uint8_t out_len, const void* out_data)
{
    const __P(sync_p2s_t)* data = (const __P(sync_p2s_t)*) in_data;

    // update the secondary side's activity timer to reflect the primary's
    __P(activity_timer_set_raw)(data->activity_timer);

    // take the modifier key bitmap from the primary side and override the
    // secondary side's to mirror it
    set_mods(data->mods);
}

