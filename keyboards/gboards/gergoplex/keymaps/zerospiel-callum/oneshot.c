#include "oneshot.h"

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (*state == os_up_unqueued) {
                register_code(mod);
                *state = os_down_unused;
            }
        } else {
            if (*state == os_down_unused) {
                *state = os_up_queued;
            } else if (*state == os_down_used) {
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        }
    } else if (!record->event.pressed && *state == os_down_unused && !is_oneshot_ignored_key(keycode)) {
        *state = os_down_used;
    } else if (!record->event.pressed && *state == os_up_queued && !is_oneshot_ignored_key(keycode)) {
        *state = os_up_unqueued;
        unregister_code(mod);
    } else if (record->event.pressed && is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
        *state = os_up_unqueued;
        unregister_code(mod);
    }
}
