#include QMK_KEYBOARD_H

#include "g/keymap_combo.h"

// Left-hand home row mods
// default
#define SFT_A LSFT_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define ALT_D LALT_T(KC_D)
#define GUI_F LGUI_T(KC_F)
// lower
#define SFT_DQT LSFT_T(KC_LNG9)
#define CTL_MINS LCTL_T(KC_MINS)
#define ALT_LBRC LALT_T(KC_LNG8)
#define GUI_LPRN LGUI_T(KC_LNG7)

// Right-hand home row mods
// default
#define GUI_J RGUI_T(KC_J)
#define ALT_K RALT_T(KC_K)
#define CTL_L RCTL_T(KC_L)
#define SFT_SCLN RSFT_T(KC_SCLN)
// lower
#define GUI_RPRN RGUI_T(KC_LNG6)
#define ALT_RBRC RALT_T(KC_LNG5)
#define CTL_SCLN RCTL_T(KC_SCLN)
#define SFT_TILD RSFT_T(KC_LNG4)

#define L(kc) LT(LOWER, kc)
#define R(kc) LT(RAISE, kc)
#define LTEXTRA TG(EXTRA)

enum layers {
    DEF,
    LOWER,
    RAISE,
    ADJUST,
    EXTRA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEF] = LAYOUT_split_3x5_3(
        KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,          KC_Y, KC_U,  KC_I,    KC_O,   KC_P,
        SFT_A, CTL_S, ALT_D, GUI_F, KC_G,          KC_H, GUI_J, ALT_K,   CTL_L,  SFT_SCLN,
        KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,          KC_N, KC_M,  KC_COMM, KC_DOT, KC_SLSH,
               KC_ESC, L(KC_TAB), KC_SPC,          KC_ENT, R(KC_BSPC), XXXXXXX
    ),

    [LOWER] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,           KC_CIRC, KC_AMPR, KC_ASTR, KC_COLN, KC_EQL,
        KC_DQT,  KC_MINS, KC_LBRC, KC_LPRN, KC_BSLS,           KC_SLSH, KC_RPRN, KC_RBRC, KC_SCLN, KC_TILD,
        KC_QUOT, KC_UNDS, KC_LCBR, KC_LT,   KC_PIPE,           KC_PLUS, KC_GT,   KC_RCBR, KC_QUES, KC_GRV,
                          XXXXXXX, _______, _______,           _______, _______, XXXXXXX
    ),

    [RAISE] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,        KC_3,     KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        _______, _______,     _______,  _______, KC_DOT,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MPLY,
        KC_DEL, G(S(KC_F12)), G(KC_F2), _______, _______,      KC_F12,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,
                              XXXXXXX,  _______, _______,      _______, _______, XXXXXXX
    ),

    [ADJUST] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        _______, _______, _______, _______, KC_F11,             KC_F12,  _______, _______, _______, _______,
        QK_RBT,  _______, _______, _______, _______,            CW_TOGG, KC_MUTE, LTEXTRA, KC_BRID, KC_BRIU,
                          XXXXXXX, _______, _______,            _______, _______, XXXXXXX
    ),

    [EXTRA] = LAYOUT_split_3x5_3(
        _______,  KC_WH_D, KC_MS_U,  KC_WH_U, _______,          _______, _______, _______, _______, _______,
        _______,  KC_MS_L, KC_MS_D,  KC_MS_R, _______,          _______, _______, _______, _______, _______,
        _______,  KC_BTN1, KC_BTN3,  KC_BTN2, _______,          _______, _______, LTEXTRA, _______, _______,
                            XXXXXXX, _______, _______,          _______, _______, XXXXXXX
    ),

};

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_MINS:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
      return true;

    default:
      return false;  // Deactivate Caps Word.
  }
}

// process_mod_tap_non_basic is a custom func
void process_mod_tap_non_basic(uint16_t keycode, uint16_t trigger, uint16_t output, keyrecord_t *record) {
    if (keycode == trigger && record->event.pressed && record->tap.count > 0) {
        tap_code16(output);
    }

    return;
}

bool process_rolling_mods(uint16_t rolling_from, uint16_t rolling_to, uint16_t mod_from, keyrecord_t *record) {
    if (record->event.pressed && record->tap.count > 0) {
        if (get_mods() & MOD_BIT(mod_from)) {
            unregister_mods(MOD_BIT(mod_from));

            tap_code(rolling_from);
            tap_code(rolling_to);

            add_mods(MOD_BIT(mod_from));
            return false;
        }
    }
    
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // left
    process_mod_tap_non_basic(keycode, SFT_DQT, KC_DQT, record);
    process_mod_tap_non_basic(keycode, ALT_LBRC, KC_LBRC, record);
    process_mod_tap_non_basic(keycode, GUI_LPRN, KC_LPRN, record);
    // right
    process_mod_tap_non_basic(keycode, GUI_RPRN, KC_RPRN, record);
    process_mod_tap_non_basic(keycode, ALT_RBRC, KC_RBRC, record);
    process_mod_tap_non_basic(keycode, SFT_TILD, KC_TILD, record);

    switch (keycode) {
        case CTL_S:
            return process_rolling_mods(KC_D, KC_S, KC_LALT, record);
        case ALT_K:
            return process_rolling_mods(KC_J, KC_K, KC_RGUI, record);
        case CTL_L:
            return process_rolling_mods(KC_J, KC_L, KC_RGUI, record);
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, RAISE, LOWER, ADJUST);
}
