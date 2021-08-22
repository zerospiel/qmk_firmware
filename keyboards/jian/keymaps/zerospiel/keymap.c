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
  ZC_COPY,
  XV_PASTE,
  RE_TAB,
};

#define RAISE_T(kc) LT(_RAISE, kc)
#define LOWER_T(kc) LT(_LOWER, kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
  XXXXXXX, XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,                XXXXXXX, XXXXXXX,
           XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,             XXXXXXX,
           XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,             XXXXXXX,
           RAISE_T(KC_TAB), LSFT_T(KC_SPC), LOWER_T(KC_ENT),       LOWER_T(KC_ESC), RSFT_T(KC_BSPC), RAISE_T(KC_DEL)
),

[_LOWER] = LAYOUT(
  XXXXXXX, XXXXXXX,         KC_F1,   KC_F2, KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,     XXXXXXX, XXXXXXX,
           XXXXXXX,         KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,    XXXXXXX,
           XXXXXXX,         KC_1,    KC_2,  KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
),

[_RAISE] = LAYOUT(
  XXXXXXX, KC_NLCK,         KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SLCK,  XXXXXXX, XXXXXXX,
           LCTL_T(KC_EQL),  KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,   XXXXXXX,
           XXXXXXX,         KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS,  XXXXXXX,
                                              XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
),

[_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX,   DEBUG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MS_BTN1,  KC_MS_UP,   KC_MS_BTN2,    DEBUG,   XXXXXXX, XXXXXXX,
           XXXXXXX,   RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MS_LEFT,  KC_MS_DOWN, KC_MS_RIGHT,   RESET,   XXXXXXX,
           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MS_WH_UP, XXXXXXX,    KC_MS_WH_DOWN, XXXXXXX, XXXXXXX,
                                      XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
),

};

const uint16_t PROGMEM copy_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM re_tab_combo[] = {KC_R, KC_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZC_COPY] = COMBO_ACTION(copy_combo),
  [XV_PASTE] = COMBO_ACTION(paste_combo),
  [RE_TAB] = COMBO_ACTION(re_tab_combo),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
  uprintf("KL: col=%d, row=%d, pressed=%d, layer=%d\n", record->event.key.col, record->event.key.row, record->event.pressed, biton32(layer_state));
  #endif
  return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case ZC_COPY:
      if (pressed) {
        tap_code16(LCTL(KC_C));
      }
      break;
    case XV_PASTE:
      if (pressed) {
        tap_code16(LCTL(KC_V));
      }
      break;
    case RE_TAB:
      if (pressed) {
        tab_code16(KC_TAB);
      }
      break;
  }
}