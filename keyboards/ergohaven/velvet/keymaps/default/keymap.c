#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_all(
        KC_Q, KC_W,    KC_E,    KC_R,  KC_T,                         KC_Y,    KC_U,  KC_I,    KC_O,   KC_P,
        KC_A, KC_S,    KC_D,    KC_F,  KC_G,                         KC_H,    KC_J,  KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X,    KC_C,    KC_V,  KC_B,                         KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH,
              KC_LBRC, KC_RBRC, RAISE, KC_SPC,        KC_ENT, LOWER, KC_PLUS, KC_EQL
                                            
    ),

    [_LOWER] = LAYOUT_all(
        _______, _______, _______, _______, KC_LBRC,                        KC_RBRC, KC_P7,   KC_P8, KC_P9, _______,
        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LPRN,                        KC_RPRN, KC_P4,   KC_P5, KC_P6, KC_MINS,
        _______, _______, _______, _______, _______,                        _______, KC_P1,   KC_P2, KC_P3, KC_EQL ,
                          KC_LBRC, KC_RBRC, _______, _______,      KC_PLUS, KC_PLUS, KC_PLUS, KC_EQL 

    ),

    [_RAISE] = LAYOUT_all(
          _______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,
          KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,
          _______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,
                         _______,_______, _______, _______,      _______, _______, KC_EQL, _______
    )
};
