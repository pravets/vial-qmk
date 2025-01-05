#include "ergohaven_pointing.h"
#include "quantum.h"

pointing_mode_t pointing_mode = POINTING_MODE_NORMAL;

static int32_t accumulated_h = 0;
static int32_t accumulated_v = 0;

static int32_t sens[4] = {1, 2, 16, 32};

void set_sniper_sens(int32_t s) {
    sens[POINTING_MODE_SNIPER] = s;
}

void set_scroll_sens(int32_t s) {
    sens[POINTING_MODE_SCROLL] = s;
}

void set_text_sens(int32_t s) {
    sens[POINTING_MODE_TEXT] = s;
}

void set_automouse(uint8_t layer) {
    if (layer == 0) {
        set_auto_mouse_enable(false);
    } else {
        set_auto_mouse_layer(layer);
        set_auto_mouse_enable(true);
    }
}

static bool invert_scroll = false;

void set_invert_scroll(bool invert) {
    invert_scroll = invert;
}

bool is_mouse_active = false;

bool auto_mouse_activation(report_mouse_t mouse_report) {
    return is_mouse_active;
}

bool is_mouse_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EH_SCR:
        case EH_SNP:
        case EH_TXT:
            return true;
        default:
            return false;
    }

    return is_mouse_record_user(keycode, record);
}

bool process_record_pointing(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case EH_SCR:
        case EH_TXT:
        case EH_SNP: {
            static uint16_t        press_timer        = 0;
            static pointing_mode_t prev_pointing_mode = POINTING_MODE_NORMAL;

            const pointing_mode_t NEW_MODE = POINTING_MODE_SNIPER + (keycode - EH_SNP);

            if (record->event.pressed) {
                prev_pointing_mode = pointing_mode;
                pointing_mode      = NEW_MODE;
                press_timer        = timer_read();
            } else {
                if (timer_elapsed(press_timer) < get_tapping_term(keycode, record)) {
                    if (prev_pointing_mode == NEW_MODE)
                        pointing_mode = POINTING_MODE_NORMAL;
                    else
                        pointing_mode = NEW_MODE;
                } else
                    pointing_mode = POINTING_MODE_NORMAL;
            }
            return false;
        }
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mrpt) {
    is_mouse_active = abs(mrpt.x) > 1 || abs(mrpt.y) > 1 || abs(mrpt.v) > 1 || abs(mrpt.h) > 1 || mrpt.buttons;

    pointing_mode_t pmode = pointing_mode;

    // dealing with two finger gesture on touch
    if (mrpt.h != 0 || mrpt.v != 0) {
        pmode  = POINTING_MODE_SCROLL;
        mrpt.x = mrpt.h;
        mrpt.y = mrpt.v;
        mrpt.h = 0;
        mrpt.v = 0;
    }

    int32_t divisor = sens[pmode];

    if (pmode != POINTING_MODE_NORMAL) {
        accumulated_h += mrpt.x;
        accumulated_v += mrpt.y;

        int shift_x = accumulated_h / divisor;
        int shift_y = accumulated_v / divisor;

        accumulated_h -= shift_x * divisor;
        accumulated_v -= shift_y * divisor;

        mrpt.x = 0;
        mrpt.y = 0;

        switch (pmode) {
            case POINTING_MODE_SNIPER:
                mrpt.x = shift_x;
                mrpt.y = shift_y;
                break;

            case POINTING_MODE_SCROLL:
                mrpt.h = shift_x;
                mrpt.v = -shift_y;
                break;

            case POINTING_MODE_TEXT:
                while (shift_x > 0) {
                    tap_code(KC_RIGHT);
                    shift_x--;
                }
                while (shift_x < 0) {
                    tap_code(KC_LEFT);
                    shift_x++;
                }
                while (shift_y < 0) {
                    tap_code(KC_UP);
                    shift_y++;
                }
                while (shift_y > 0) {
                    tap_code(KC_DOWN);
                    shift_y--;
                }
                break;

            default:
            case POINTING_MODE_NORMAL:
                break;
        }
    }

    if (invert_scroll) {
        mrpt.v = -mrpt.v;
        mrpt.h = -mrpt.h;
    }

    return mrpt;
}
