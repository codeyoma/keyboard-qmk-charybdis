/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_ARST,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJ,
    LAYER_MOUSE,
    LAYER_TEST,
};

// #define LOWER MO(LAYER_LOWER)
// #define RAISE MO(LAYER_RAISE))
#define LOWER TL_LOWR
#define RAISE TL_UPPR
#define ARST MO(LAYER_ARST)
#define MOUSE MO(LAYER_MOUSE)
#define ADJ MO(LAYER_ADJ)
#define TEST MO(LAYER_TEST)

// Left-hand home row mods
#define HP(X) LCTL_T(X)
#define HR(X) LGUI_T(X)
#define HM(X) LALT_T(X)
#define HI(X) LSFT_T(X)

#define SFT_TAB LSFT_T(KC_TAB)
#define FOCUS LCTL(KC_F4)
#define MV_LEFT LGUI(KC_LBRC)
#define MV_RGHT LGUI(KC_RBRC)

// Tap Dance declarations
enum {
    TD_QUOTE,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      HP(KC_A),HR(KC_S),HM(KC_D),HI(KC_F),    KC_G,       KC_H,HI(KC_J),HM(KC_K),HR(KC_L),HP(KC_SCLN),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         MOUSE,   KC_LSFT,   LOWER,      RAISE,  KC_SPC 
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_ARST] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      HP(KC_A),HR(KC_R),HM(KC_S),HI(KC_T),    KC_D,       KC_H,HI(KC_N),HM(KC_E),HR(KC_I),HP(KC_O),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         MOUSE,   KC_LSFT,   LOWER,      RAISE,  KC_SPC
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),


  [LAYER_LOWER] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_GLB, KC_HOME, KC_PGUP, KC_PGDN,  KC_END,    XXXXXXX,    KC_7,    KC_8,    KC_9, KC_BSPC,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, MV_LEFT,    MV_RGHT,    KC_4,    KC_5,    KC_6, TD(TD_QUOTE),
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_SPC, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX,    XXXXXXX,    KC_1,    KC_2,    KC_3, KC_BSLS,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,  _______,    KC_0 
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX,      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_BSPC,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_F5,  KC_F6,  KC_F7,  KC_F8, XXXXXXX,      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   FOCUS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_F1,  KC_F2,  KC_F3,  KC_F4, XXXXXXX,       KC_INS,  KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,      _______, _______
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

    [LAYER_ADJ] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(ARST),   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_MPLY, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, _______, _______,    _______, TEST 
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),

// DPI_MOD POINTER_DEFAULT_DPI_FORWARD
// DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
// S_D_MOD POINTER_SNIPING_DPI_FORWARD
// S_D_RMOD POINTER_SNIPING_DPI_REVERS_D_MOD, XXXXXXX, MS_BTN3, XXXXXXX, XXXXXXX
// SNIPING SNIPING_MODE
// SNP_TOG SNIPING_MODE_TOGGLE
// DRGSCRL DRAGSCROLL_MODE
// DRG_TOG DRAGSCROLL_MODE_TOGGLE

    [LAYER_MOUSE] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, DPI_MOD,    MS_BTN4, MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN5,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       SNIPING, XXXXXXX, DRG_TOG, DRGSCRL, S_D_MOD,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         _______, XXXXXXX, _______,      RAISE, XXXXXXX 
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),


    [LAYER_TEST] = LAYOUT(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

// Combo reference layers
// COMBO_REF_LAYER(LAYER_ARST, LAYER_BASE)

// Combo definitions
enum combos {
    CB_TAB,
    CB_ESC,
    CB_ENTER,
    CB_LESSTHAN,
    CB_GREATERTHAN,
    CB_UNDER,
    CB_MINUS,
    CB_PLUS,
    CB_EQUAL,
    CB_PIPE,
    CB_PREV_TAB,
    CB_NEXT_TAB,
    CB_EXCLAMATION,
    CB_ATSIGN,
    CB_HASH,
    CB_DOLLAR,
    CB_PERCENT,
    CB_CARET,
    CB_AMPERSAND,
    CB_ASTERISK,
    CB_TILDE,
    CB_GRAVE,
    CB_MS_BTN1,
    CB_MS_BTN2,
    // CB_MS_BTN3,
    CB_DRGSCRL,
};

// HP(KC_A),HR(KC_S),HM(KC_D),HI(KC_F)
// HI(KC_J),HM(KC_K),HR(KC_L),HP(KC_SCLN),
const uint16_t PROGMEM tab_combo[] = {MOUSE, KC_LSFT, COMBO_END};
// const uint16_t PROGMEM esc_combo[]   = {SFT_TAB, LOWER, COMBO_END};
const uint16_t PROGMEM esc_combo[]   = {KC_LSFT, LOWER, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {RAISE, KC_SPC, COMBO_END};

// const uint16_t PROGMEM lessthan_combo[]    = {KC_S, KC_X, COMBO_END};
// const uint16_t PROGMEM greaterthan_combo[] = {KC_D, KC_C, COMBO_END};
// const uint16_t PROGMEM greaterthan_combo[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM lessthan_combo[]    = {HR(KC_S), KC_X, COMBO_END};
const uint16_t PROGMEM greaterthan_combo[] = {HM(KC_D), KC_C, COMBO_END};
const uint16_t PROGMEM under_combo[]       = {KC_H, KC_N, COMBO_END};

// const uint16_t PROGMEM minus_combo[]       = {KC_J, KC_M, COMBO_END};
// const uint16_t PROGMEM plus_combo[]        = {KC_K, KC_COMM, COMBO_END};
// const uint16_t PROGMEM equal_combo[]       = {KC_L, KC_DOT, COMBO_END};
// const uint16_t PROGMEM pipe_combo[]        = {KC_SCLN, KC_SLSH, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {HI(KC_J), KC_M, COMBO_END};
const uint16_t PROGMEM plus_combo[]  = {HM(KC_K), KC_COMM, COMBO_END};
const uint16_t PROGMEM equal_combo[] = {HR(KC_L), KC_DOT, COMBO_END};
const uint16_t PROGMEM pipe_combo[]  = {HP(KC_SCLN), KC_SLSH, COMBO_END};

const uint16_t PROGMEM prev_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM next_combo[] = {KC_X, KC_C, COMBO_END};

// const uint16_t PROGMEM exclamation_combo[] = {KC_Q, KC_A, COMBO_END};
// const uint16_t PROGMEM atsign_combo[]      = {KC_W, KC_S, COMBO_END};
// const uint16_t PROGMEM hash_combo[]        = {KC_E, KC_D, COMBO_END};
// const uint16_t PROGMEM dollar_combo[]      = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM exclamation_combo[] = {KC_Q, HP(KC_A), COMBO_END};
const uint16_t PROGMEM atsign_combo[]      = {KC_W, HR(KC_S), COMBO_END};
const uint16_t PROGMEM hash_combo[]        = {KC_E, HM(KC_D), COMBO_END};
const uint16_t PROGMEM dollar_combo[]      = {KC_R, HI(KC_F), COMBO_END};

const uint16_t PROGMEM percent_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM caret_combo[]   = {KC_Y, KC_H, COMBO_END};

// const uint16_t PROGMEM ampersand_combo[]   = {KC_U, KC_J, COMBO_END};
// const uint16_t PROGMEM asterisk_combo[]    = {KC_I, KC_K, COMBO_END};
// const uint16_t PROGMEM tilde_combo[]       = {KC_O, KC_L, COMBO_END};
// const uint16_t PROGMEM grave_combo[]       = {KC_P, KC_SCLN, COMBO_END};
const uint16_t PROGMEM ampersand_combo[] = {KC_U, HI(KC_J), COMBO_END};
const uint16_t PROGMEM asterisk_combo[]  = {KC_I, HM(KC_K), COMBO_END};
const uint16_t PROGMEM tilde_combo[]     = {KC_O, HR(KC_L), COMBO_END};
const uint16_t PROGMEM grave_combo[]     = {KC_P, HP(KC_SCLN), COMBO_END};

// const uint16_t PROGMEM ms_btn1_combo[]     = {KC_M, KC_COMMA, COMBO_END};
// const uint16_t PROGMEM ms_btn2_combo[]     = {KC_COMMA, KC_DOT, COMBO_END};
// const uint16_t PROGMEM ms_btn3_combo[]     = {KC_M, KC_COMMA, KC_DOT, COMBO_END};
// const uint16_t PROGMEM drag_scroll_combo[] = {KC_DOT, KC_SLSH, COMBO_END};

const uint16_t PROGMEM ms_btn1_combo[]     = {KC_M, KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM ms_btn2_combo[]     = {KC_COMMA, KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM drag_scroll_combo[] = {KC_M, KC_COMMA, KC_DOT, KC_SLSH, COMBO_END};

combo_t key_combos[] = {
    [CB_TAB]         = COMBO(tab_combo, KC_TAB),
    [CB_ESC]         = COMBO(esc_combo, KC_ESC),
    [CB_ENTER]       = COMBO(enter_combo, KC_ENT),
    [CB_LESSTHAN]    = COMBO(lessthan_combo, KC_LT),
    [CB_GREATERTHAN] = COMBO(greaterthan_combo, KC_GT),
    [CB_UNDER]       = COMBO(under_combo, LSFT(KC_MINS)),
    [CB_MINUS]       = COMBO(minus_combo, KC_MINS),
    [CB_PLUS]        = COMBO(plus_combo, LSFT(KC_EQL)),
    [CB_EQUAL]       = COMBO(equal_combo, KC_EQL),
    [CB_PIPE]        = COMBO(pipe_combo, LSFT(KC_BSLS)),
    [CB_PREV_TAB]    = COMBO(prev_combo, LCTL(LSFT(KC_TAB))),
    [CB_NEXT_TAB]    = COMBO(next_combo, LCTL(KC_TAB)),
    [CB_EXCLAMATION] = COMBO(exclamation_combo, KC_EXLM),
    [CB_ATSIGN]      = COMBO(atsign_combo, KC_AT),
    [CB_HASH]        = COMBO(hash_combo, KC_HASH),
    [CB_DOLLAR]      = COMBO(dollar_combo, KC_DLR),
    [CB_PERCENT]     = COMBO(percent_combo, KC_PERC),
    [CB_CARET]       = COMBO(caret_combo, KC_CIRC),
    [CB_AMPERSAND]   = COMBO(ampersand_combo, KC_AMPR),
    [CB_ASTERISK]    = COMBO(asterisk_combo, KC_ASTR),
    [CB_TILDE]       = COMBO(tilde_combo, KC_TILD),
    [CB_GRAVE]       = COMBO(grave_combo, KC_GRV),
    [CB_MS_BTN1]     = COMBO(ms_btn1_combo, MS_BTN1),
    [CB_MS_BTN2]     = COMBO(ms_btn2_combo, MS_BTN2),
    // [CB_MS_BTN3]     = COMBO(ms_btn3_combo, MS_BTN3),
    [CB_DRGSCRL] = COMBO(drag_scroll_combo, DRGSCRL),
};

#define COMBO_REF_DEFAULT LAYER_BASE

uint8_t combo_ref_from_layer(uint8_t layer) {
    switch (get_highest_layer(layer_state)) {
        case LAYER_ARST:
            return LAYER_BASE;
        default:
            return LAYER_BASE;
    }
    return layer; // important if default is not in case.
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Disable combo `SOME_COMBO` on layer `_LAYER_A` */
    switch (combo_index) {
        // case SOME_COMBO:
        //     if (layer_state_is(_LAYER_A)) {
        //         return false;
        //     }
        default:
            if (layer_state_is(LAYER_MOUSE) || layer_state_is(LAYER_RAISE) || layer_state_is(LAYER_ADJ)) {
                return false;
            }
    }

    return true;
}

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    // decide by combo->keycode
    switch (combo->keycode) {}

    // or with combo index, i.e. its name from enum.
    switch (combo_index) {
        case CB_MS_BTN1:
        case CB_MS_BTN2:
        case CB_DRGSCRL:
            return 50;
    }

    // And if you're feeling adventurous, you can even decide by the keys in the chord,
    // i.e. the exact array of keys you defined for the combo.
    // This can be useful if your combos have a common key and you want to apply the
    // same combo term for all of them.
    //     if (combo->keys[0] == KC_ENT) { // if first key in the array is Enter
    //         return 150;
    //     }

    return COMBO_TERM;
}
#endif