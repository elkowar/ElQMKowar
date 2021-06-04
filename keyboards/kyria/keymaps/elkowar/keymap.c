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


enum layers {
    _QWERTY = 0,
    _GAMER,
    _UML,
    _PLOVER,
    _SYM,
    _NUMS,
    _NUMPAD,
    _WMWSP,
    _ADJUST
};


#ifdef COMBO_ENABLE // {{{

enum combos {
  JL_C_BSPC,
  ASEMI_QSTN,
  THUMB_RET,
  FJ_RET,
  KSEMI_EXCL,
  DSEMI_UNDS,

  JM_SHIFT,
  FV_SHIFT,
  KCOMMA_SHIFT,

  QR_UML_OSL,
};




const uint16_t PROGMEM jl_combo[]      = {KC_L,   KC_J,      COMBO_END};
const uint16_t PROGMEM asemi_combo[]   = {KC_A,   KC_SCLN,   COMBO_END};
const uint16_t PROGMEM f13bspc_combo[] = {KC_F13, KC_BSPC,   COMBO_END};
const uint16_t PROGMEM fj_combo[]      = {KC_F,   KC_J,      COMBO_END};
const uint16_t PROGMEM ksemi_combo[]   = {KC_K,   KC_SCLN,   COMBO_END};
const uint16_t PROGMEM dsemi_combo[]   = {KC_D,   KC_SCLN,   COMBO_END};

const uint16_t PROGMEM jm_combo[]      = {KC_J,   KC_M,      COMBO_END};
const uint16_t PROGMEM fv_combo[]      = {KC_F,   KC_V,      COMBO_END};
const uint16_t PROGMEM kcomma_combo[]  = {KC_K,   KC_COMMA,  COMBO_END};
const uint16_t PROGMEM qr_combo[]      = {KC_Q,   KC_R,      COMBO_END};



combo_t key_combos[COMBO_COUNT] = {
  [JL_C_BSPC]  = COMBO_ACTION(jl_combo),
  [ASEMI_QSTN] = COMBO(asemi_combo, KC_QUES),
  [THUMB_RET]  = COMBO(f13bspc_combo, KC_ENT),
  [FJ_RET]     = COMBO(fj_combo, KC_ENT),
  [KSEMI_EXCL] = COMBO(ksemi_combo, KC_EXLM),
  [DSEMI_UNDS] = COMBO(dsemi_combo, KC_UNDS),

  [JM_SHIFT] = COMBO_ACTION(jm_combo),
  [FV_SHIFT] = COMBO_ACTION(fv_combo),
  [KCOMMA_SHIFT] = COMBO_ACTION(kcomma_combo),

  [QR_UML_OSL] = COMBO_ACTION(qr_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case JL_C_BSPC:
            if (pressed) {
                tap_code16(LCTL(KC_BSPC));
            }
            break;
        case JM_SHIFT:
            if (pressed) {
                set_oneshot_mods(MOD_BIT(KC_RSFT));
            }
            break;
        case FV_SHIFT:
            if (pressed) {
                set_oneshot_mods(MOD_BIT(KC_LSFT));
            }
            break;
        case KCOMMA_SHIFT:
            if (pressed) {
                set_oneshot_mods(MOD_BIT(KC_LCTL));
            }
            break;

        case QR_UML_OSL:
            if (pressed) {
                /*set_oneshot_layer(_UML, ONESHOT_START);*/
            } else {
                /*clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);*/
            }
            break;
    }
}

#endif // }}}

// super+number
#define WS(x) G(x)
#define MVWS(x) S(G(x))

#define OSSFT OSM(MOD_LSFT)
#define LT_BSPSYM LT(_SYM, KC_BSPC)
enum {
    TD_SUPR,
};

void td_supr(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // what the hell do I put here :(
    } else if (state->count >= 2) {
        set_oneshot_layer(_WMWSP, ONESHOT_START);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SUPR] = ACTION_TAP_DANCE_FN(td_supr),
};

/*enum {*/
    /*TD_OE,*/
/*};*/

/*void td_oe(qk_tap_dance_state_t *state, void *user_data) {*/
    /*if (state->count >= 3) {*/
        /*send_unicode_string("ö");*/
    /*}*/
/*}*/
/*void td_ae(qk_tap_dance_state_t *state, void *user_data) {*/
    /*if (state->count >= 3) {*/
        /*send_unicode_string("ö");*/
    /*}*/
/*}*/
/*void td_ue(qk_tap_dance_state_t *state, void *user_data) {*/
    /*if (state->count >= 3) {*/
        /*send_unicode_string("ü");*/
    /*}*/
/*}*/
/*void td_sz(qk_tap_dance_state_t *state, void *user_data) {*/
    /*if (state->count >= 3) {*/
        /*send_unicode_string("ß");*/
    /*}*/
/*}*/

/*qk_tap_dance_action_t tap_dance_actions[] = {*/
    /*[TD_O_OE] = ACTION_TAP_DANCE_FN(td_oe)*/
/*};*/

enum custom_keycodes {
    CUS_OE = SAFE_RANGE,
    CUS_SZ,
    CUS_UE,
    CUS_AE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 */
    [_QWERTY] = LAYOUT(
//   ,-------------------------------------------------------------------------.                                               ,---------------------------------------------------------------.
      LT(_NUMPAD, KC_TAB),    KC_Q,          KC_W,   KC_E,    KC_R,    KC_T,                                                     KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,            KC_PLUS,
//   |-----------------------+-------------+-------+--------+--------+---------|                                               |---------+--------+--------+--------+-----------------+--------|
      MT(MOD_LCTL, KC_ESC),   LSFT_T(KC_A),  KC_S,   KC_D,    KC_F,    KC_G,                                                     KC_H,     KC_J,    KC_K,    KC_L,    RSFT_T(KC_SCLN), KC_QUOT,
//   |-----------------------+-------------+-------+--------+--------+---------+------------+------------. ,--------+----------+---------+--------+--------+--------+-----------------+--------|
      KC_LSFT,                KC_Z,          KC_X,   KC_C,    KC_V,    KC_B,    MO(_ADJUST), MO(_NUMPAD),   TG(_UML),KC_F13,    KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_MINS,          KC_RSFT,
//   `-----------------------+-------------+-------+--------+--------+---------+------------+------------| |--------+----------+---------+--------+--------+--------+-----------------+--------'
                                                    KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
                                                    /*KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      TD(TD_SUPR),   KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT*/
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
                                                    KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      KC_LGUI,       KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT
                                                    /*KC_LALT, KC_LCTL, OSSFT,    KC_SPC,      TD(TD_SUPR),   KC_ENT,  LT_BSPSYM, OSSFT,    KC_LCTL, KC_RALT*/
//                                                 `--------+--------+---------+--------+----------------' `--------+----------+---------+--------+--------'
    ),
/*
 * umlauts
 */
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

/*
 * Symbol and movement layer
 */
    [_SYM] = LAYOUT(
//   ,-----------------------------------------------------.                                         ,------------------------------------------------------.
      _______, KC_CIRC, KC_EXLM, KC_DQUO, KC_SLSH, KC_BSLS,                                           KC_GRV,   KC_LCBR, KC_LBRC, KC_RBRC, KC_RCBR, KC_ASTR,
//   |--------+--------+--------+--------+--------+--------|                                         |---------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_DLR,  KC_LPRN, KC_RPRN, KC_END,                                            KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, KC_AMPR, KC_PERC,
//   |--------+--------+--------+--------+--------+--------+-----------+--------.  ,--------+--------+---------+--------+--------+--------+--------+--------|
      _______, KC_AT,   KC_DEL,  KC_PIPE, KC_QUES, KC_TILD, OSL(_WMWSP), _______,   _______, _______, KC_DEL,   KC_EQL,  KC_HASH, KC_UNDS, _______, _______,
//   `--------+--------+--------+--------+--------+--------+-----------+--------|  |--------+--------+---------+--------+--------+--------+--------+--------'
                                 _______, _______, _______,  KC_0,      _______,    _______, KC_DEL,  _______,  _______, _______
//                              `--------+--------+--------+-----------+--------'  `--------+--------+---------+--------+--------'
    ),
/*
 * Number keys
 */
    [_NUMS] = LAYOUT(
//   ,-----------------------------------------------------.                                     ,------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                       _______, _______,  _______, _______, _______, _______,
//   |--------+--------+--------+--------+--------+--------|                                     |---------+--------+--------+--------+--------+--------|
      _______, KC_1, 	KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    _______,
//   |--------+--------+--------+--------+--------+--------+--------+--------. ,--------+--------+---------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______,  _______, _______, _______, _______,
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+---------+--------+--------+--------+--------+--------'
                                 _______, KC_0,    KC_0,    _______, _______,   _______, _______, _______,  _______, _______
//                              `--------+--------+--------+--------+--------' `--------+--------+---------+--------+--------'
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
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______,   _______, _______, _______,     UC_MOD,  _______, _______, _______, _______,
//   `--------+--------+--------+--------+--------+--------+--------+--------| |--------+--------+------------+--------+--------+--------+--------+--------'
                                 _______, _______, _______, _______, _______,   _______, _______, _______,     _______, _______
//                              `--------+--------+--------+--------+--------' `--------+--------+------------+--------+--------'
    ),

};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && is_oneshot_layer_active()) {
        clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
    }
    switch (keycode) {
        case CUS_OE:
            if (record->event.pressed) {
                send_unicode_string("ö");
            }
            break;
        case CUS_SZ:
            if (record->event.pressed) {
                send_unicode_string("ß");
            }
            break;
        case CUS_UE:
            if (record->event.pressed) {
                send_unicode_string("ü");
            }
            break;
        case CUS_AE:
            if (record->event.pressed) {
                send_unicode_string("ä");
            }
            break;
    }
    return true;
}


void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);
}



/*layer_state_t layer_state_set_user(layer_state_t state) {*/
    /*return update_tri_layer_state(state, _SYM, _NUMS, _ADJUST);*/
/*}*/



layer_state_t layer_state_set_user(layer_state_t state) {
    // epic rgb lighting
    switch(get_highest_layer(state)) {
        case _QWERTY:
            rgblight_setrgb(0, 255, 157);
            break;
        case _GAMER:
            rgblight_setrgb(220, 005, 057);
            break;
        case _UML:
            rgblight_setrgb(30, 255, 250);
            break;
        case _PLOVER:
            rgblight_setrgb(0, 055, 237);
            break;
        case _SYM:
            break;
        case _NUMS:
            break;
        case _NUMPAD:
            break;
        case _WMWSP:
            break;
        case _ADJUST:
            rgblight_setrgb(255, 255, 0);
            break;
    }
    return state;
}


#ifdef OLED_DRIVER_ENABLE // {{{
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case _NUMS:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif // }}}

#ifdef ENCODER_ENABLE // {{{
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif // }}}
