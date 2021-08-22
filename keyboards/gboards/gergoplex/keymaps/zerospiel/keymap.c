#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum gergoplex_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define RAISE_T(kc) LT(_RAISE, kc)
#define LOWER_T(kc) LT(_LOWER, kc)

    /* Combomap
     *
     * ,-------------------------------.      ,-------------------------------.
     * |       |  1  ESC   |     |     |      |       |    DEL    |     |     |
     * |-------+-----+-----+-----+-----|      |-------+-----+-----+-----+-----|
     * |       |  2 BSPC  TAB 123|     |      |       |   BSPC 4  |     |     |
     * |-------+-----+-----+-----+-----|      |-------+-----+-----+-----+-----|
     * |       |  3  |    ENT    |     |      |       |  4  ESC   |     |     |
     * `-------------------------------'      `-------------------------------'
     *            .-----------------.            .-----------------.
     *            |     |     |     |            |     |     |     |
     *            '-----------------'            '-----------------'
     *  1 == RMB
     *  2 == LMB
     *  3 == MMB
     *  4 == ENT
     *
     */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Alpha layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |     Q |  W  |  E  |  R  |  T  |      |  Y  |  U  |  I  |  O  |   P   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | CTRL A|  S  |  D  |  F  |  G  |      |  H  |  J  |  K  |  L  |CTRL ; |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * | SHFT Z|  X  |  C  |  V  |  B  |      |  N  |  M  |  ,  |  .  |SHFT / |
     * `-------------------------------'      `-------------------------------'
     *       .----------------------.           .----------------------.
     *       | ATL | CMD | SPC LWR |           | SPC UPR | SHFT | TAB |
     *       '----------------------'           '----------------------'
     */
    [_QWERTY] = LAYOUT_split_3x5_3(
         KC_Q,        KC_W, KC_E, KC_R, KC_T,          KC_Y, KC_U, KC_I,    KC_O,   KC_P,
         CTL_T(KC_A), KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K,    KC_L,   RCTL_T(KC_SCLN),
         SFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,          KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH),
           KC_LALT, KC_LCMD, LOWER_T(KC_SPC),          RAISE_T(KC_SPC), KC_RSFT, KC_TAB
    ),

    /* Lower layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |    !  |  @  |  #  |  $  |  %  |      |  ^  |  &  |  *  |  ~  |   =   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    "  |  -  |  [  |  (  |  \  |      |  /  |  )  |  ]  |  ;  |   :   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |    '  |  _  |  {  |  <  |  |  |      |  +  |  >  |  }  |  ?  |   `   |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             |     |     |     |          |     |     |     |
     *             '-----------------'          '-----------------'
     */
    [_LOWER] = LAYOUT_split_3x5_3(
         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_TILD, KC_EQL,
         KC_DQT,  KC_MINS, KC_LBRC, KC_LPRN, KC_BSLS,          KC_SLSH, KC_RPRN, KC_RBRC, KC_SCLN, KC_COLN,
         KC_QUOT, KC_UNDS, KC_LCBR, KC_LT,   KC_PIPE,          KC_PLUS, KC_GT,   KC_RCBR, KC_QUES, KC_GRV,
                           _______, _______, _______,          _______, _______, _______
    ),

    /* Upper layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   1   |  2  |  3  |  4  |  5  |      |  6  |  7  |  8  |  9  |   0   |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |   `   |     | WHU | WHD | MSU |      | LFT | DWN |  UP | RGT | MPLY  |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  S1   | S2  | MSL | MSD | MSR |      | F12 | MPRV| MNXT| VOLD| VOLU  |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             |     |     |     |          |     |     |     |
     *             '-----------------'          '-----------------'
     *
     *  S1 == SHIFT+CMD+F12
     *  S2 == CMD+F2
     *
     */
    [_RAISE] = LAYOUT_split_3x5_3(
         KC_1,         KC_2,     KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
         KC_GRV,       _______,  KC_WH_U, KC_WH_D, KC_MS_U,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_MPLY,
         SCMD(KC_F12), G(KC_F2), KC_MS_L, KC_MS_D, KC_MS_R,          KC_F12,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,
                                 _______, _______, _______,          _______, _______, _______
    ),

    /* Adjust layer
     *
     * ,-------------------------------.      ,-------------------------------.
     * |   DBG |  F1 |  F2 |  F3 |  F4 |      | BRIU|     |     |     |   S1  |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |   RST |  F5 |  F6 |  F7 |  F8 |      | BRID|     |     |     |  RST  |
     * |-------+-----+-----+-----+-----|      |-----+-----+-----+-----+-------|
     * |  CAPS |  F9 | F10 | F11 | F12 |      | MUTE|     |     |     |       |
     * `-------------------------------'      `-------------------------------'
     *             .-----------------.          .-----------------.
     *             |     |     |     |          |     |     |     |
     *             '-----------------'          '-----------------'
     *
     *  S1 == SHIFT+ALT+-
     *
     */
    [_ADJUST] = LAYOUT_split_3x5_3(
         DEBUG,   KC_F1, KC_F2,  KC_F3,  KC_F4,           KC_BRIU, _______, _______, _______, LSA(KC_MINS),
         RESET,   KC_F5, KC_F6,  KC_F7,  KC_F8,           KC_BRID, _______, _______, _______, RESET,
         KC_CAPS, KC_F9, KC_F10, KC_F11, KC_F12,          KC_MUTE, _______, _______, _______, _______,
                      _______, _______, _______,          _______, _______, _______
    ),

};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case CTL_T(KC_A):
//         case SFT_T(KC_Z):
//         case RCTL_T(KC_SCLN):
//         case RSFT_T(KC_SLSH):
//             return false;
//         default:
//             return true;
//     }
// }

// bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case LOWER_T(KC_SPC):
//             // Immediately select the hold action when another key is tapped.
//             return true;
//         default:
//             // Do not select the hold action when another key is tapped.
//             return false;
//     }
// }

 bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
