#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define CMDBSPC G(KC_BSPC)
#define ALTBSPC A(KC_BSPC)
#define CMDZ G(KC_Z)
#define CMDX G(KC_X)
#define CMDC G(KC_C)
#define CMDV G(KC_V)
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_EXTRA TG(EXTRA)

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
    EXTRA,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (cmd-spc)
    SW_CTAB, // Switch to next tab (ctl-tab)
};

// Combos
const uint16_t PROGMEM weEsc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM hjGJ[] = {KC_H, KC_J, COMBO_END};
combo_t key_combos[] = {
    COMBO(weEsc, KC_ESC),
    COMBO(hjGJ, LGUI(KC_J)),
};
// Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEF] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                      KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
              XXXXXXX, LA_NAV,  KC_SPC,                    KC_LSFT, LA_SYM, XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_RPRN, KC_RBRC, KC_AMPR, KC_ASTR,
        KC_DQT,  KC_MINS, KC_LBRC, KC_LPRN, KC_PLUS,       KC_GRV,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_QUOT, KC_UNDS, KC_LCBR, KC_LT,   KC_BSLS,       KC_QUES, KC_GT,   KC_RCBR, KC_COLN, KC_EQL,
                          XXXXXXX, _______, _______,       _______, XXXXXXX, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        KC_TAB,  SW_LANG, SW_WIN,  SW_CTAB, KC_VOLU,       KC_TILD, ALTBSPC, CMDBSPC, KC_MUTE,  KC_DEL,
        OS_SHFT, OS_CTRL, OS_ALT,  OS_CMD,  KC_VOLD,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_BSPC,
        CMDZ,    CMDX,    CMDC,    CMDV,    KC_MPLY,       CW_TOGG, KC_MPRV, KC_MNXT, LA_EXTRA, KC_ENT,
                          XXXXXXX, XXXXXXX, _______,       _______, _______, XXXXXXX
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,   KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_SHFT, KC_DOT, OS_ALT,  OS_CMD,  KC_F11,         KC_F12,  OS_CMD,  OS_ALT,  OS_CTRL, OS_SHFT,
        KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                         XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [EXTRA] = LAYOUT_split_3x5_3(
        XXXXXXX,  KC_WH_D, KC_MS_U,  KC_WH_U, XXXXXXX,     KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX,  QK_BOOT,
        XXXXXXX,  KC_MS_L, KC_MS_D,  KC_MS_R, XXXXXXX,     KC_BRID, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        XXXXXXX,  KC_BTN1, KC_BTN3,  KC_BTN2, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, LA_EXTRA, XXXXXXX,
                            XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
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

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;
bool sw_ctab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN, OS_SHFT,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LGUI, KC_SPC, SW_LANG, OS_SHFT,
        keycode, record
    );
    update_swapper(
        &sw_ctab_active, KC_LCTL, KC_TAB, SW_CTAB, OS_SHFT,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
