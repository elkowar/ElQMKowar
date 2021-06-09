/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include <keymap_steno.h>
#include <rgblight.h>

#include "features/casemodes.h"


enum layers {
    _QWERTY = 0,
    _COLEMK,
    _GAMER,
    _UML,
    _PLOVER,
    _SYM,
    _NUMPAD,
    _WMWSP,
    _ADJUST
};

enum custom_keycodes {
    CUS_OE = SAFE_RANGE,
    CUS_SZ,
    CUS_UE,
    CUS_AE,
    CUS_UML,
};

#include "g/keymap_combo.h"

#ifdef COMBO_ENABLE // {{{

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case TN_RET:
            return 100;
    }
    return COMBO_TERM;
}

#endif // }}}


// super+number
#define WS(x) G(x)
#define MVWS(x) S(G(x))

#define OSSFT OSM(MOD_LSFT)
#define LT_BSPSYM LT(_SYM, KC_BSPC)

enum {
    TD_SUPR,
    TD_BKTCK,
};

void td_supr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LGUI);
    } else if (state->count >= 2) {
        set_oneshot_layer(_WMWSP, ONESHOT_START);
    }
}
void td_supr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LGUI);
    } else if (state->count >= 2) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
}

void td_backtick(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 4) {
        SEND_STRING("```"SS_LSFT(SS_TAP(X_ENT))"```"SS_TAP(X_UP)SS_TAP(X_END));
    } else {
        tap_code(KC_GRV);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SUPR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_supr_finished, td_supr_reset),
    [TD_BKTCK] = ACTION_TAP_DANCE_FN(td_backtick),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Q,          KC_W,   KC_E,    KC_R,    KC_T,                                                     KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,            KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   LSFT_T(KC_A),  KC_S,   KC_D,    KC_F,    KC_G,                                                     KC_H,     KC_J,    KC_K,    KC_L,    RSFT_T(KC_SCLN), KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_V,    KC_B,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_LEAD,   KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      TD(TD_SUPR),   KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_COLEMK] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Q,          KC_W,   KC_F,    KC_P,    KC_B,                                                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,          KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   LSFT_T(KC_A),  KC_R,   KC_S,    KC_T,    KC_G,                                                     KC_M,    KC_N,    KC_E,    KC_I,    RSFT_T(KC_O),     KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_D,    KC_V,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_F13,    KC_K,     KC_H,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      TD(TD_SUPR),   KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_GAMER] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Q,          KC_W,   KC_E,    KC_R,    KC_T,                                                    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,             KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   KC_A,          KC_S,   KC_D,    KC_F,    KC_G,                                                    KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_V,    KC_B,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_F13,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      TD(TD_SUPR),   KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_UML] = LAYOUT(
//   ,-----------------------------------------------------.                                     ,------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                       _______,  _______, _______, _______, _______, CUS_UE,
//   |--------+--------+--------+--------+--------+--------|                                     |---------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                       _______,  _______, _______, _______, CUS_OE,  CUS_AE,
//   |--------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+---------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,   TG(_UML),_______, _______,  _______, _______, _______, CUS_SZ,  _______,
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+---------+--------+--------+--------+--------+--------'
                                 _______, _______, _______, _______, _______,   _______, _______, _______,  _______, _______
//                              `--------+--------+--------+--------+--------' `--------+--------+---------+--------+--------'
    ),


    [_PLOVER] = LAYOUT(
//   ,---------------------------------------------------------.                                     ,------------------------------------------------------.
      TG(_QWERTY), STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,                                        STN_N6,   STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,
//   |------------+--------+--------+--------+--------+--------|                                     |---------+--------+--------+--------+--------+--------|
      _______,     STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,                                       STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
//   |------------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+---------+--------+--------+--------+--------+--------|
      _______,     STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, _______, _______,   _______, _______, STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
//   `------------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+---------+--------+--------+--------+--------+--------'
                                     _______, _______, STN_A,   STN_O,   _______,   MO(_SYM),STN_E,   STN_U,    _______, _______
//                                  `--------+--------+--------+--------+--------' `--------+--------+---------+--------+--------'
    ),

    [_SYM] = LAYOUT(
//   ,-----------------------------------------------------.                                         ,------------------------------------------------------.
      _______, KC_CIRC, KC_EXLM, KC_DQUO, KC_SLSH, KC_BSLS,                                           TD(TD_BKTCK), KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_ASTR,
//   |--------+--------+--------+--------+--------+--------|                                         |-------------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_DLR,  KC_LPRN, KC_RPRN, KC_END,                                            KC_LEFT,      KC_DOWN, KC_UP,   KC_RGHT, KC_AMPR, KC_PERC,
//   |--------+--------+--------+--------+--------+--------+-----------+--------.  ,--------+--------+-------------+--------+--------+--------+--------+--------|
      _______, KC_AT,   KC_DEL,  KC_PIPE, KC_QUES, KC_TILD, OSL(_WMWSP), _______,   _______, _______, KC_DEL,       KC_EQL,  KC_HASH, KC_UNDS, _______, _______,
//   `--------+--------+--------+--------+--------+--------+-----------+--------|  |--------+--------+-------------+--------+--------+--------+--------+--------'
                                 _______, _______, _______,  KC_0,      _______,    _______, KC_DEL,  _______,       _______, _______
//                              `--------+--------+--------+-----------+--------'  `--------+--------+---------+--------+--------'
    ),

/*
 * Workspace stuff
 */
    [_WMWSP] = LAYOUT(
//   ,--------------------------------------------------------------------.                                     ,-----------------------------------------------------.
      _______, MVWS(KC_1), MVWS(KC_2), MVWS(KC_3), MVWS(KC_4), MVWS(KC_5),                                       _______, _______, _______, _______, _______, _______,
//   |--------+-----------+-----------+-----------+-----------+-----------|                                     |--------+--------+--------+--------+--------+--------|
      _______, WS(KC_1),   WS(KC_2),   WS(KC_3),   WS(KC_4),   WS(KC_5),                                         _______, _______, _______, _______, _______, _______,
//   |--------+-----------+-----------+-----------+-----------+-----------+--------+--------. ,--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______,    _______,    _______,    _______,    _______,    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
//   `--------+-----------+-----------+-----------+-----------+-----------+--------+--------| |--------+--------+--------+--------+--------+--------+--------+--------'
                                       _______,    KC_0,       KC_0,       _______, _______,   _______, _______, _______, _______, _______
//                                    `-----------+-----------+-----------+--------+--------' `--------+--------+--------+--------+--------'
    ),

/*
 * Numberpad
 */
    [_NUMPAD] = LAYOUT(
//   ,-----------------------------------------------------.                                     ,------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                       _______,  KC_7,    KC_8,    KC_9,    _______, _______,
//   |--------+--------+--------+--------+--------+--------|                                     |---------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                       _______,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
//   |--------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+---------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,  KC_4,    KC_5,    KC_6,    _______, _______,
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+---------+--------+--------+--------+--------+--------'
                                 _______, KC_0,    KC_0,    _______, _______,   _______, _______, KC_0,     _______, _______
//                              `--------+--------+--------+--------+--------' `--------+--------+---------+--------+--------'
    ),


/*
 * Adjust Layer: Function keys, RGB
 */
    [_ADJUST] = LAYOUT(
//   ,-----------------------------------------------------.                                     ,---------------------------------------------------------.
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  DF(_QWERTY),
//   |--------+--------+--------+--------+--------+--------|                                     |------------+--------+--------+--------+--------+--------|
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                       TG(_PLOVER), CMB_TOG, _______, KC_F11,  KC_F12,  DF(_GAMER),
//   |--------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+------------+--------+--------+--------+--------+--------|
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______,   _______, _______, _______,     UC_MOD,  _______, _______, _______, DF(_COLEMK),
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+------------+--------+--------+--------+--------+--------'
                                 _______, _______, _______, _______, _______,   _______, _______, _______,     _______, _______
//                              `--------+--------+--------+--------+--------' `--------+--------+------------+--------+--------'
    ),

};

LEADER_EXTERNS();
void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_TWO_KEYS(KC_F, KC_F) {
            enable_caps_word();
        }
        SEQ_TWO_KEYS(KC_F, KC_D) {
            enable_xcase_with(KC_UNDS);
            enable_caps_word();
        }
        SEQ_TWO_KEYS(KC_F, KC_S) {
            enable_xcase_with(KC_UNDS);
        }
        SEQ_TWO_KEYS(KC_F, KC_C) {
            enable_xcase_with(OSM(MOD_LSFT));
        }
        SEQ_TWO_KEYS(KC_F, KC_A) {
            enable_xcase();
        }
    }
}


#define MAP_KEY(key, result)  case (key): if (record->event.pressed) { send_unicode_string((result)); } break;
#define KEY_ACTION(key, code) case (key): if (record->event.pressed) { code } break;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && is_oneshot_layer_active()) {
        clear_oneshot_layer_state(ONESHOT_PRESSED);
    }

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    switch (keycode) {
        MAP_KEY(CUS_OE, "ö");
        MAP_KEY(CUS_UE, "ü");
        MAP_KEY(CUS_AE, "ä");
        MAP_KEY(CUS_SZ, "ß");
        KEY_ACTION(CUS_UML,
            SEND_STRING(SS_TAP(X_RALT)"\"");
        );
    }
    return true;
}


void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);
}


layer_state_t layer_state_set_user(layer_state_t state) {
    // epic rgb lighting
    switch(get_highest_layer(state)) {
        case _QWERTY: rgblight_setrgb(0, 255, 157); break;
        case _GAMER:  rgblight_setrgb(220, 005, 057); break;
        case _COLEMK: rgblight_setrgb(255, 255, 255); break;
        case _UML:    rgblight_setrgb(30, 255, 250); break;
        case _PLOVER: rgblight_setrgb(0, 055, 237); break;
        case _WMWSP:  rgblight_setrgb(255, 0, 255); break;
        case _ADJUST: rgblight_setrgb(255, 255, 0); break;
    }
    return state;
}


void suspend_power_down_user(void) {
    rgblight_setrgb(0, 0, 0);
}
void suspend_wakeup_init_user(void) {
    rgblight_setrgb(0, 255, 157);
}

