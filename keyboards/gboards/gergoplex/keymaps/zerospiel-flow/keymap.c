#include QMK_KEYBOARD_H

#include "flow.h"

#define LA_SYM   MO(SYM)
#define LA_NAV   MO(NAV)
#define LA_MOUSE TG(MOUSE)

#define UMLAUT SS_DOWN(X_LALT) SS_TAP(X_U) SS_UP(X_LALT)
#define ESCET  SS_DOWN(X_LALT) SS_TAP(X_S) SS_UP(X_LALT)

enum layers {
    DEF,
    SYM,
    NAV,
    FUNC,
    MISC,
    MOUSE,
    EXTRA,
};

enum keycodes {
    OS_MISC = SAFE_RANGE,
    OS_FUNC,
    _KC_SS,
    _KC_DU,
    _KC_DU_U,
    _KC_DA,
    _KC_DA_U,
    _KC_DO,
    _KC_DO_U,
};

const uint16_t flow_config[FLOW_COUNT][2] = {
    {LA_NAV, KC_LSFT},
    {LA_NAV, KC_LALT},
    {LA_NAV, KC_LGUI},
    {LA_NAV, KC_LCTL},
    {LA_SYM, KC_RCTL},
    {LA_SYM, KC_RGUI},
    {LA_SYM, KC_RALT},
};

const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_MISC, MISC},
    {OS_FUNC, FUNC},
};

// Combos
const uint16_t PROGMEM weEsc[]  = {KC_W,   KC_E, COMBO_END};
const uint16_t PROGMEM hjGJ[]   = {KC_H,   KC_J, COMBO_END};
const uint16_t PROGMEM navvGV[] = {LA_NAV, KC_V, COMBO_END};
const uint16_t PROGMEM navcGV[] = {LA_NAV, KC_C, COMBO_END};
const uint16_t PROGMEM navxGV[] = {LA_NAV, KC_X, COMBO_END};
const uint16_t PROGMEM navzGV[] = {LA_NAV, KC_Z, COMBO_END};
combo_t key_combos[] = {
    COMBO(weEsc,  KC_ESC),
    COMBO(hjGJ,   LGUI(KC_J)),
    COMBO(navvGV, LGUI(KC_V)),
    COMBO(navcGV, LGUI(KC_C)),
    COMBO(navxGV, LGUI(KC_X)),
    COMBO(navzGV, LGUI(KC_Z)),
};
// Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DEF] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,                        KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                        KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
              XXXXXXX, LA_NAV,  KC_SPC,                      KC_RSFT, LA_SYM, XXXXXXX
    ),

    [SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_DEL,  KC_MINS, KC_LBRC, KC_RBRC, KC_PLUS,         KC_GRV,  KC_RGUI, KC_RALT, KC_RCTL, OS_MISC,
        KC_PIPE, KC_UNDS, KC_LCBR, KC_RCBR, KC_BSLS,         KC_QUES, KC_QUOT, KC_DQT,  KC_COLN, KC_EQL,
                          XXXXXXX, _______, _______,         _______, XXXXXXX, XXXXXXX
    ),

    [NAV] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,     KC_8,    KC_9,    KC_0,
        KC_TAB,  KC_LCTL, KC_LALT, KC_LGUI, KC_ENT,          KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, KC_BSPC,
        KC_LSFT, KC_BSPC, XXXXXXX, OS_FUNC, KC_TILD,         KC_CAPS, LA_MOUSE, KC_COMM, KC_DOT,  KC_ENT,
                          XXXXXXX, XXXXXXX, _______,         _______, _______,  XXXXXXX
    ),

    [FUNC] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,          XXXXXXX, KC_RGUI, KC_RALT, KC_RCTL, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_F11,  KC_F12,  XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX,         _______, XXXXXXX, XXXXXXX
    ),

    [MISC] = LAYOUT_split_3x5_3(
        QK_BOOT,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, QK_RBT,
        XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
                            XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [MOUSE] = LAYOUT_split_3x5_3(
        XXXXXXX,  XXXXXXX, KC_MS_U,  KC_BTN3, KC_WH_D,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,  KC_MS_L, KC_MS_D,  KC_MS_R, KC_WH_U,       XXXXXXX, KC_RGUI,  KC_RALT, KC_RCTL, XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX, LA_MOUSE, XXXXXXX, XXXXXXX, XXXXXXX,
                            XXXXXXX, KC_BTN1, KC_BTN2,       _______, XXXXXXX,  XXXXXXX
    ),

    [EXTRA] = LAYOUT_split_3x5_3(
        XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX, _KC_DU,   XXXXXXX, _KC_DO,   XXXXXXX,
        _KC_DA,   _KC_SS,  XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX, _KC_DU_U, XXXXXXX, _KC_DO_U, XXXXXXX,
        _KC_DA_U, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,
                            XXXXXXX, XXXXXXX, XXXXXXX,       _______, XXXXXXX,  XXXXXXX
    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;

    switch (keycode) {
        case _KC_SS:
            if (!record->event.pressed) return true;
            SEND_STRING(ESCET);
            return false;
        case _KC_DA:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "a");
            return false;
        case _KC_DA_U:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "A");
            return false;
        case _KC_DU:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "u");
            return false;
        case _KC_DU_U:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "U");
            return false;
        case _KC_DO:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "o");
            return false;
        case _KC_DO_U:
            if (!record->event.pressed) return true;
            SEND_STRING(UMLAUT "O");
            return false;
    }
        

    return true;
}

void matrix_scan_user(void) {
    flow_matrix_scan();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, EXTRA);
}
