#include "kissetfall.h"

#ifdef AUDIO_ENABLE
float base_sound[][2] = SONG(TERMINAL_SOUND);
float caps_sound[][2] = SONG(CAPS_LOCK_ON_SOUND);
#endif

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;    

// custom keycodes
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef WPM_ENABLE
    if (record->event.pressed) {
        extern uint32_t tap_timer;
        tap_timer = timer_read32();
    }
  #endif

  switch (keycode) { // This will do most of the grunt work with the keycodes.
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case NEXTSEN:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING(". ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif 
        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

    case PREDL:  // Next sentence macro.
      if (record->event.pressed) {
        SEND_STRING("/ ");
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif
        add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
      }
      return false;

       case BRACES:
            if (record->event.pressed) {
                uint8_t shifted = get_mods() & (MOD_MASK_SHIFT);
                    if (shifted) {
                        unregister_code(KC_LSFT);
                        unregister_code(KC_RSFT);
                        SEND_STRING("{}"SS_TAP(X_LEFT));
                    }
                    else {
                        SEND_STRING("[]"SS_TAP(X_LEFT));
                    }
            }
            break;

    case PARENTH:
            if (record->event.pressed) {
                SEND_STRING("()");
                tap_code(KC_LEFT);
            }
          break;

    case KC_CAPS:
      if (record->event.pressed) {
    #ifdef AUDIO_ENABLE
        PLAY_SONG(caps_sound);
    #endif 
        }      
      return true; // Let QMK send the enter press/release events
                  
    default:
      return true; // Process all other keycodes normally
  }
   return process_record_keymap(keycode, record);
}



void matrix_scan_user(void) { // The very important timer.
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 300) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}



// __attribute__ ((weak))
// layer_state_t layer_state_set_keymap (layer_state_t state) {
//   return state;
// }

// layer_state_t layer_state_set_user (layer_state_t state) {
//       #if defined(AUDIO_ENABLE)
//         static bool is_base_on = false;
//     if (layer_state_cmp(state, _BASE) != is_base_on) {
//             is_base_on = layer_state_cmp(state, _BASE);
//             if (is_base_on) {
//                 stop_all_notes();
//             } else {
//                 PLAY_SONG(base_sound);
//             }
//         }
//     #endif
//   return layer_state_set_keymap (state);
// }
