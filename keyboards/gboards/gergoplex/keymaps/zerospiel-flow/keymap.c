#include QMK_KEYBOARD_H

#include "flow.h"

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

const uint16_t flow_config[FLOW_COUNT][2] = {
    {LA_NAV, KC_LSFT},
    {LA_NAV, KC_LALT},
    {LA_NAV, KC_LGUI},
    {LA_NAV, KC_LCTL},
    {LA_SYM, KC_RCTL},
    {LA_SYM, KC_RGUI},
    {LA_SYM, KC_RALT},
    {LA_SYM, KC_RSFT},
    {LA_EXTRA, KC_LSFT},
    {LA_EXTRA, KC_LALT},
    {LA_EXTRA, KC_LGUI},
    {LA_EXTRA, KC_LCTL},
    {LA_EXTRA, KC_RCTL},
    {LA_EXTRA, KC_RGUI},
    {LA_EXTRA, KC_RALT},
    {LA_EXTRA, KC_RSFT},
};

const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {XXXXXXX, EXTRA},
};

enum keycodes {
    SW_WIN = SAFE_RANGE,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (cmd-spc)
    SW_CTAB, // Switch to next tab (ctl-tab)
};

// Combos
const uint16_t PROGMEM weEsc[]  = {KC_W,   KC_E, COMBO_END};
const uint16_t PROGMEM hjGJ[]   = {KC_H,   KC_J, COMBO_END};
const uint16_t PROGMEM navvGV[] = {LA_NAV, KC_V, COMBO_END};
combo_t key_combos[] = {
    COMBO(weEsc,  KC_ESC),
    COMBO(hjGJ,   LGUI(KC_J)),
    COMBO(navvGV, LGUI(KC_V)),
};
// Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEF] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                      KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
              KC_ESC, LA_NAV, KC_SPC,                      KC_LSFT, LA_SYM, XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_RPRN, KC_RBRC, KC_AMPR, KC_ASTR,
        KC_DQT,  KC_MINS, KC_LBRC, KC_LPRN, KC_PLUS,       KC_GRV,  KC_RGUI,  KC_RALT,  KC_RCTL, KC_RSFT,
        KC_QUOT, KC_UNDS, KC_LCBR, KC_LT,   KC_BSLS,       KC_QUES, KC_GT,   KC_RCBR, KC_COLN, KC_EQL,
                          XXXXXXX, _______, _______,       _______, _______, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        KC_TAB,  SW_LANG, SW_WIN,  SW_CTAB, KC_VOLU,       KC_TILD, ALTBSPC, CMDBSPC, KC_MUTE,  KC_DEL,
        KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI,  KC_VOLD,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_BSPC,
        CMDZ,    CMDX,    CMDC,    CMDV,    KC_MPLY,       CW_TOGG, KC_MPRV, KC_MNXT, LA_EXTRA, KC_ENT,
                          XXXXXXX, _______, _______,       _______, _______, XXXXXXX
    ),

    [NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,     KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LSFT, KC_LCTL, KC_LALT,  KC_LGUI,   KC_F11,       KC_F12,  KC_RGUI,  KC_RALT,  KC_RCTL, KC_RSFT,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
                          XXXXXXX, _______, _______,       _______, _______, KC_DOT
    ),

    [EXTRA] = LAYOUT_split_3x5_3(
        _______,  KC_WH_D, KC_MS_U,  KC_WH_U, _______,       KC_BRIU, _______, _______, _______,  QK_RBT,
        _______,  KC_MS_L, KC_MS_D,  KC_MS_R, _______,       KC_BRID, _______, _______, _______,  _______,
        _______,  KC_BTN1, KC_BTN3,  KC_BTN2, _______,       _______, _______, _______, LA_EXTRA, _______,
                            XXXXXXX, _______, _______,       _______, _______, XXXXXXX
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

bool sw_win_active = false;
bool sw_lang_active = false;
bool sw_ctab_active = false;

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active
        && keycode != KC_LSFT && keycode != KC_LEFT && keycode != KC_RIGHT
    ) {
        unregister_code(cmdish);
        *active = false;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LGUI, KC_SPC, SW_LANG,
        keycode, record
    );
    update_swapper(
        &sw_ctab_active, KC_LCTL, KC_TAB, SW_CTAB,
        keycode, record
    );
    
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;

    return true;
}

void matrix_scan_user(void) {
    flow_matrix_scan();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
