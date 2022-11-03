#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

#define RAISE   MO(_RAISE)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)
#define PREVWRD LCTL(KC_LEFT)
#define NEXTWRD LCTL(KC_RIGHT)

#define APP_A   LSG(KC_A)
#define APP_S   LSG(KC_S)
#define APP_D   LSG(KC_D)
#define APP_F   LSG(KC_F)
#define APP_X   LSG(KC_X)
#define APP_C   LSG(KC_C)
#define APP_V   LSG(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_QWERTY] = LAYOUT_5x6(
         KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                          KC_F7, KC_F8, KC_F9,   KC_F10, KC_F11,  KC_F12,
         KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                           KC_Y,  KC_U,  KC_I,    KC_O,   KC_P,    KC_MPLY,
         KC_LALT, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,                           KC_H,  KC_J,  KC_K,    KC_L,   KC_SCLN, KC_ENT,
         KC_ESC,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                           KC_N,  KC_M,  KC_COMM, KC_DOT, KC_QUOT, KC_GRV,
                         KC_VOLD, KC_VOLU,                                                  KC_LBRC, KC_RBRC,
                                        KC_LCTL, LOWER, KC_SPC,       KC_LSFT, RAISE, KC_BSPC
      ),
    
      [_LOWER] = LAYOUT_5x6(
    
         QK_BOOT, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______,  _______,
         _______, KC_3,    KC_2,    KC_1,    KC_0,    KC_4,               KC_7,    KC_6,    KC_5,    KC_9,    KC_8,     _______,
         _______, APP_A,   APP_S,   APP_D,   APP_F,   KC_ENT,             KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
         QK_RBT,  _______, APP_X,   APP_C,   APP_V,   KC_DEL,             KC_PSCR, PREVWRD, KC_PGDN, KC_PGUP, NEXTWRD,  _______,
                           _______, _______,                                                _______, _______,
                                       _______, _______, _______,    _______, ADJUST,  _______
    
      ),
    
      [_RAISE] = LAYOUT_5x6(
         _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,             _______,  _______, KC_CIRC, _______, _______,  QK_BOOT,
         _______, _______, KC_LT,   KC_EQL,  KC_GT,   KC_GRV,              KC_TILDE, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
         _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,             KC_PERC,  KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, _______,             _______,  KC_PIPE, KC_TILD, KC_AMPR, _______,  QK_RBT,
                           _______, _______,                                                 _______, _______,
                                             _______, ADJUST, _______,   _______, _______, _______
      ),
    
      [_ADJUST] = LAYOUT_5x6(
        _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,              _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,              _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
                          _______, _______,                                                  _______, _______,                           
                                           _______, _______, _______,    _______, _______, _______                                           \
       ),
};
