#include QMK_KEYBOARD_H

enum jian_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum jian_keycodes {
  QWERTY = SAFE_RANGE,
};

enum combo_events {
  DF_TAB,
  WE_ESC,
  ER_ALT,
};

// TODO: tapdance somewhere?

#define RAISE_T(kc) LT(_RAISE, kc)
#define LOWER_T(kc) LT(_LOWER, kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  XXXXXXX, XXXXXXX, KC_Q,        KC_W, KC_E, KC_R, KC_T,                  KC_Y,   KC_U, KC_I,    KC_O,    KC_P,            XXXXXXX, XXXXXXX,
           XXXXXXX, CTL_T(KC_A), KC_S, KC_D, KC_F, KC_G,                  KC_H,   KC_J, KC_K,    KC_L,    RCTL_T(KC_SCLN), XXXXXXX,
           XXXXXXX, SFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,                  KC_N,   KC_M, KC_COMM, KC_DOT,  RSFT_T(KC_SLSH), XXXXXXX,
                    LCMD_T(KC_ESC), OPT_T(KC_TAB), LOWER_T(KC_SPC),       RAISE_T(KC_SPC), OPT_T(KC_ENT), RCMD_T(KC_BSPC)
),

[_LOWER] = LAYOUT(
  XXXXXXX, XXXXXXX, KC_EXLM,  KC_AT,    KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_EQL,  KC_DEL,   XXXXXXX, XXXXXXX,
           XXXXXXX, KC_DQT,   KC_MINS,  KC_LBRC, KC_LPRN, KC_BSLS,      KC_SLSH, KC_RPRN, KC_RBRC, KC_SCLN, KC_COLN,  XXXXXXX,
           XXXXXXX, KC_QUOT,  KC_UNDS,  KC_LCBR, KC_LT,   KC_PIPE,      KC_PLUS, KC_GT,   KC_RCBR, KC_QUES, KC_GRV,   XXXXXXX,
                                        _______, _______, _______,      _______, _______, _______
),

[_RAISE] = LAYOUT(
  XXXXXXX, XXXXXXX, KC_1,         KC_2,     KC_3,     KC_4,     KC_5,         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX, XXXXXXX,
           XXXXXXX, KC_TILD,      KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,       KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_MPLY,  XXXXXXX,
           XXXXXXX, SCMD(KC_F12), G(KC_F2), KC_GRV,   KC_COMM,  KC_DOT,       KC_F12,   KC_MPRV,  KC_MNXT,  KC_VOLD,  KC_VOLU,  XXXXXXX,
                                             _______, _______, _______,       _______, _______, _______
),

[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX,   DEBUG,    KC_F1, KC_F2,  KC_F3,  KC_F4,       KC_BRIU, KC_BTN1, KC_MS_U, KC_BTN2, LSA(KC_MINS), XXXXXXX, XXXXXXX,
           XXXXXXX,   RESET,    KC_F5, KC_F6,  KC_F7,  KC_F8,       KC_BRID, KC_MS_L, KC_MS_D, KC_MS_R, RESET,        XXXXXXX,
           XXXXXXX,   KC_CAPS,  KC_F9, KC_F10, KC_F11, KC_F12,      KC_MUTE, KC_WH_U, KC_BTN3, KC_WH_D, KC_RCTL,      XXXXXXX,
                                    _______, _______, _______,      _______, _______, _______
),

};

const uint16_t PROGMEM df_tab_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM we_esc_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM er_alt_combo[] = {KC_E, KC_R, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [DF_TAB] = COMBO(df_tab_combo, KC_TAB),
  [WE_ESC] = COMBO(we_esc_combo, KC_ESC),
  [ER_ALT] = COMBO(er_alt_combo, KC_LOPT),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Initialize variable holding the binary
// representation of active modifiers.
uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        uprintf("kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
    switch (keycode) {

    // RCMD_T(KC_BSPC)
    case 0x782A:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }

    }
    return true;
};
