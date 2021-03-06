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
/*#include <keymap_steno.h>*/
#include <rgblight.h>

#include "features/casemodes.h"


enum layers {
    _QWERTY = 0,
    _COLEMK,
    _SEMIMK,
    _SEMIMKFL,
    _GAMER,
    _UML,
    /*_PLOVER,*/
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

    CUS_SCREAM_SNAKE,
};

enum {
    TD_SUPR,
    TD_BKTCK,
};



// super+number
#define WS(x) G(x)
#define MVWS(x) S(G(x))


#define LS(x) LSFT_T((x))
#define RS(x) RSFT_T((x))
#define ALT(x) LALT_T((x))
#define CTL(x) LCTL_T((x))
#define GUI(x) LGUI_T((x))

// defined colemak homerow to make my life easier in combos.def
#define HOME_A KC_A
#define HOME_R LS(KC_R)
#define HOME_S KC_S
#define HOME_T KC_T
#define HOME_N KC_N
#define HOME_E KC_E
#define HOME_I RS(KC_I)
#define HOME_O KC_O


#define SEMI_S KC_S
#define SEMI_R LS(KC_R)
#define SEMI_N KC_N
#define SEMI_T KC_T
#define SEMI_D KC_D
#define SEMI_E KC_E
#define SEMI_A RS(KC_A)
#define SEMI_I KC_I




#define OSSFT OSM(MOD_LSFT)
#define LT_BSPSYM LT(_SYM, KC_BSPC)

#include "g/keymap_combo.h"




// the time of the last non-combo input, used to tweak the timing of combos depending on if I'm currently
// in active typing flow (should practically remove any chance of mistriggering space-combos)
static uint16_t non_combo_input_timer = 0;


#ifdef COMBO_ENABLE // {{{

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // home row number combos need some more time.
    if (index >= HRNR_7 && index <= HRNR_4) {
        return 40;
    } else if (index >= COMBO_LCTL && index <= COMBO_SFT_CTL_GUI) {
        return timer_elapsed(non_combo_input_timer) > 300 ? 50 : 5;
    }
    switch (index) {
        case TN_RET:
            return 40;
        case NI_C_BSPC:
        case EO_EXCL:
        case UML_AE:
        case UML_OE:
        case UML_UE:
        case UML_SS:
        case LPREN:
        case RPREN:
            return 20;
        case CTRL_Z:
        case CTRL_C:
        case CTRL_V:
            return timer_elapsed(non_combo_input_timer) > 300 ? 30 : 5;
    }
    return 25;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo) {
    return true;
}

#endif // }}}





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
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_GRV);
        }
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
      MT(MOD_LCTL, KC_ESC),   KC_A,         LS(KC_S),KC_D,    KC_F,    KC_G,                                                     KC_H,     KC_J,    KC_K,   RS(KC_L), KC_SCLN,         KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_V,    KC_B,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_LEAD,   KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_MINS,         KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSL(_SYM),KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_COLEMK] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Q,          KC_W,   KC_F,    KC_P,    KC_B,                                                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,          KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   HOME_A,        HOME_R, HOME_S,  HOME_T,  KC_G,                                                     KC_M,    HOME_N,  HOME_E,  HOME_I,  HOME_O,           KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_D,    KC_V,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_LEAD,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSL(_SYM),KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_SEMIMK] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_F,          KC_L,   KC_H,    KC_V,    KC_Z,                                                     KC_Q,    KC_W,    KC_U,    KC_O,    KC_Y,             KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   SEMI_S,        SEMI_R, SEMI_N,  SEMI_T,  KC_K,                                                     KC_C,    SEMI_D,  SEMI_E,  SEMI_A,  SEMI_I,           KC_SCLN,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_X,         KC_QUOT, KC_B,    KC_M,    KC_J,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_LEAD,    KC_P,    KC_G,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSL(_SYM),KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_SEMIMKFL] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Y,         KC_O,   KC_U,    KC_W,    KC_Q,                                                     KC_Z,     KC_V,    KC_H,    KC_L,    KC_F,             KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   SEMI_I,       SEMI_A, SEMI_E,  SEMI_D,  KC_C,                                                     KC_K,     SEMI_T,  SEMI_N,  SEMI_R,  SEMI_S,           KC_SCLN,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_MINS,      KC_DOT, KC_COMM, KC_G,    KC_P,     MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_LEAD,   KC_J,     KC_M,    KC_B,    KC_QUOT, KC_X,             KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSL(_SYM),KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),

    [_GAMER] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      KC_TAB,                 KC_Q,          KC_W,   KC_E,    KC_R,    KC_T,                                                    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,             KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      KC_LCTL,                KC_A,          KC_S,   KC_D,    KC_F,    KC_G,                                                    KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_V,    KC_B,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_ESC,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSL(_SYM),KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
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

/*
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
    */

    [_SYM] = LAYOUT(
//   ,------------------------------------------------------------------------.                                         ,----------------------------------------------------------.
      _______, KC_CIRC,      KC_EXLM,     KC_DQUO,      KC_SLSH,      KC_BSLS,                                           TD(TD_BKTCK), KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_ASTR,
//   |--------+-------------+------------+-------------+-------------+--------|                                         |-------------+--------+--------+--------+--------+--------|
      _______, KC_HOME,      KC_DLR,      KC_LPRN,      KC_RPRN,      KC_END,                                            KC_LEFT,      KC_DOWN, KC_UP,   KC_RGHT, KC_AMPR, KC_PERC,
//   |--------+-------------+------------+-------------+-------------+--------+-----------+--------.  ,--------+--------+-------------+--------+--------+--------+--------+--------|
      _______, KC_AT,        KC_DEL,      KC_PIPE,      KC_QUES,      KC_TILD, OSL(_WMWSP), _______,   _______, _______, KC_DEL,       KC_EQL,  KC_HASH, KC_UNDS, KC_PGUP, KC_PGDN,
//   `--------+-------------+------------+-------------+-------------+--------+-----------+--------|  |--------+--------+-------------+--------+--------+--------+--------+--------'
                                          _______,      _______,      _______, KC_0,       _______,    _______, KC_DEL,  _______,       _______, _______
//                                       `-------------+-------------+--------+-----------+--------'  `--------+--------+---------+--------+--------'
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
      _______, KC_LSFT, KC_LCTL, KC_LGUI, _______, _______,                                       _______,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
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
//   ,-----------------------------------------------------.                                     ,------------------------------------------------------------------------.
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F6,       KC_F7,   KC_F8,   KC_F9,         KC_F10,       DF(_QWERTY),
//   |--------+--------+--------+--------+--------+--------|                                     |------------+--------+--------+--------------+-------------+------------|
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                      /*TG(_PLOVER),*/ _______,     CMB_TOG, _______, KC_F11,        KC_F12,       DF(_GAMER),
//   |--------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+------------+--------+--------+--------------+-------------+------------|
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______,   _______, _______, _______,     UC_MOD,  _______, DF(_SEMIMKFL), DF(_SEMIMK),  DF(_COLEMK),
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+------------+--------+--------+--------------+-------------+------------'
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
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    non_combo_input_timer = timer_read();

    switch (keycode) {
        MAP_KEY(CUS_OE, "??");
        MAP_KEY(CUS_UE, "??");
        MAP_KEY(CUS_AE, "??");
        MAP_KEY(CUS_SZ, "??");
        case KC_ESC:
            clear_oneshot_mods();

        case CUS_SCREAM_SNAKE:
            if (record->event.pressed) {
                enable_xcase_with(KC_UNDS); 
                enable_caps_word();
            }
            break;

    }
    return true;
}



struct {
    uint8_t hue;
    uint8_t sat;
    uint8_t value;
} lighting_state;

void oneshot_mods_changed_user(uint8_t mods) {
    // TODO epic lighting indicator of the one shot mods here

}


void matrix_init_user() {
    /*steno_set_mode(STENO_MODE_GEMINI);*/
}


layer_state_t layer_state_set_user(layer_state_t state) {
    // epic rgb lighting
    switch(get_highest_layer(state|default_layer_state)) {
        case _QWERTY: rgblight_sethsv_noeeprom(109, 255, 255); break;
        case _COLEMK: rgblight_sethsv_noeeprom(0, 0, 255); break;
        case _SEMIMK: rgblight_sethsv_noeeprom(40, 255, 255); break;
        case _SEMIMKFL: rgblight_sethsv_noeeprom(40, 255, 255); break;
        case _GAMER:  rgblight_sethsv_noeeprom(0, 255, 255); break;
        case _UML:    rgblight_sethsv_noeeprom(156, 255, 255); break;
        /*case _PLOVER: rgblight_sethsv_noeeprom(52, 255, 255); break;*/
        case _WMWSP:  rgblight_sethsv_noeeprom(90, 125, 255); break;
        case _ADJUST: rgblight_sethsv_noeeprom(34, 255, 255); break;
    }
    return state;
}


void suspend_power_down_user(void) {
    rgblight_sethsv_noeeprom(0, 0, 0);
}
void suspend_wakeup_init_user(void) {
    rgblight_sethsv_noeeprom(109, 255, 255);
}

