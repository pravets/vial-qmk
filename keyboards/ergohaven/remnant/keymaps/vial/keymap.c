#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _FIFTH 4
#define _SIXTH 5
#define _SEVENTH 6
#define _EIGHTH 7
#define _NINTH 8
#define _TENTH 9
#define _ELEVENTH 10
#define _TWELTH 11
#define _THIRTEENTH 12
#define _FOURTEENTH 13
#define _FIFTEENTH 14
#define _SIXTEENTH 15


#define QWERTY    DF(_QWERTY)
#define RAISE     MO(_RAISE)
#define LOWER     MO(_LOWER)
#define ADJUST    MO(_ADJUST)
#define PREVWRD   LCTL(KC_LEFT)
#define NEXTWRD   LCTL(KC_RIGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_QWERTY] = LAYOUT_5x6(
         KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5,                               KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS,
         KC_ESC,  KC_Q, KC_W, KC_E, KC_R, KC_T,                               KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_EQL,
         KC_TAB,  KC_A, KC_S, KC_D, KC_F, KC_G,                               KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
         KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                               KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLASH,
                        KC_LGUI, KC_BSPC,                                                  KC_LBRC, KC_RBRC,
                                   KC_LCTL, LOWER, KC_SPC,             KC_ENT, RAISE, KC_RALT
      ),

      [_LOWER] = LAYOUT_5x6(
    
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,                 KC_F7,   KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
         QK_BOOT, _______, KC_HOME, KC_UP,   KC_END,   KC_INS,                KC_PGUP, KC_7,  KC_8,  KC_9,   _______, _______,
         _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT,                KC_PGDN, KC_4,  KC_5,  KC_6,   _______, _______,
         QK_RBT,  _______, PREVWRD, KC_CAPS, NEXTWRD,  KC_DEL,                KC_PSCR, KC_1,  KC_2,  KC_3,   _______, _______,
                           _______, _______,                                                  KC_0, _______,
                                         _______, _______, _______,      _______, ADJUST,  _______
    
      ),

      [_RAISE] = LAYOUT_5x6(
         _______, _______, KC_AT,   KC_DLR,  KC_HASH, _______,             _______, _______, KC_CIRC, _______, _______,  QK_BOOT,
         _______, _______, KC_LT,   KC_EQL,  KC_GT,   KC_GRV,              _______, KC_LBRC, KC_UNDS, KC_RBRC, _______,  _______,
         _______, KC_BSLS, KC_LPRN, KC_MINS, KC_RPRN, KC_PLUS,             KC_PERC, KC_LCBR, KC_SCLN, KC_RCBR, KC_EXLM,  _______,
         _______, _______, KC_ASTR, KC_COLN, KC_SLSH, _______,             _______, KC_PIPE, KC_TILD, KC_AMPR, _______,  QK_RBT,
                           _______, _______,                                                 _______, _______,
                                             _______, ADJUST, _______,   _______, _______, _______
      ),
    
      [_ADJUST] = LAYOUT_5x6(
        _______, _______, _______, _______, _______, _______,                 UC_RMOD, UC_MOD, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                 _______, _______, _______, _______, DM_PLY1, DM_REC1,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                 _______, KC_VOLD, KC_MUTE, KC_VOLU, DM_PLY2, DM_REC2,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, CG_TOGG,                 _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, DM_RSTP,
                          _______, _______,                                                     _______, _______,                  
                                         _______, _______, _______,       _______, _______,  _______                          
       ),
};

/* void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { */
/*     for (uint8_t i = led_min; i <= led_max; i++) { */
/*         switch(get_highest_layer(layer_state|default_layer_state)) { */
/*             case 3: */
/*                 rgb_matrix_sethsv_noeeprom(HSV_BLUE); */
/*                 break; */
/*             case 2: */
/*                 rgb_matrix_sethsv_noeeprom(HSV_BLUE); */
/*                 break; */
/*             case 1: */
/*                 rgb_matrix_sethsv_noeeprom(HSV_RED); */
/*                 break; */
/*             default: */
/*                 rgb_matrix_sethsv_noeeprom(HSV_OFF); */
/*                 break; */
/*         } */
/*     } */
/* } */

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
 HSV hsv = {0, 255, 255};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb = hsv_to_rgb(hsv);
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index <= led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
                }
            }
        }
    }
}
