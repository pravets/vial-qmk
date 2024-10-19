#include "display.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include "ergohaven_ruen.h"
#include "ergohaven_keycode_str.h"
#include "hid.h"
#include "ergohaven.h"
#include "ergohaven_symbols.h"
#include "ergohaven_display.h"

LV_FONT_DECLARE(ergohaven_symbols_20);
LV_FONT_DECLARE(ergohaven_symbols_28);

static uint32_t screen_timer = 0;

typedef enum {
    SCREEN_OFF = -1,
    SCREEN_SPLASH,
    SCREEN_LAYOUT,
    SCREEN_VOLUME,
    SCREEN_HID,
} screen_t;

static screen_t screen_state        = SCREEN_OFF;
static screen_t change_screen_state = SCREEN_OFF;

/* screens */
static lv_obj_t *screen_layout;

/* layout screen content */
static lv_obj_t *key_labels[15];
static lv_obj_t *label_layer_small;

/* public function to be used in keymaps */

void init_screen_layout(void) {
    screen_layout = lv_obj_create(NULL);
    lv_obj_add_style(screen_layout, &style_screen, 0);
    use_flex_column(screen_layout);
    lv_obj_set_scrollbar_mode(screen_layout, LV_SCROLLBAR_MODE_OFF);

    label_layer_small = lv_label_create(screen_layout);
    lv_label_set_text(label_layer_small, "layer");
    lv_obj_set_style_pad_top(label_layer_small, 25, 0);
    lv_obj_set_style_pad_bottom(label_layer_small, 25, 0);
    lv_obj_set_style_text_color(label_layer_small, accent_color_blue, 0);
    lv_obj_set_style_text_font(label_layer_small, &ergohaven_symbols_28, LV_PART_MAIN);

    lv_obj_t *cont = lv_obj_create(screen_layout);
    lv_obj_set_size(cont, 232, 250);
    // lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    int32_t v = 0;
    lv_obj_set_style_pad_row(cont, v, 0);
    lv_obj_set_style_pad_column(cont, v, 0);
    lv_obj_add_style(cont, &style_container, 0);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    uint32_t i;
    for (i = 0; i < 15; i++) {
        if (i == 12) {
            lv_obj_t *obj = lv_obj_create(cont);
            lv_obj_set_size(obj, 231, 10);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_add_style(obj, &style_screen, 0);
            lv_obj_set_style_border_opa(obj, 0, 0);
        }
        lv_obj_t *obj = lv_obj_create(cont);
        lv_obj_set_size(obj, 77, 45);
        lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_style(obj, &style_screen, 0);
        lv_obj_set_style_border_width(obj, 1, 0);

        key_labels[i] = lv_label_create(obj);
        lv_obj_center(key_labels[i]);
        lv_obj_set_style_text_font(key_labels[i], &ergohaven_symbols_20, LV_PART_MAIN);
        lv_obj_set_style_text_align(key_labels[i], LV_TEXT_ALIGN_CENTER, 0);

        if (i >= 12) {
            lv_obj_set_style_border_opa(obj, 0, 0);
            lv_obj_set_style_text_color(key_labels[i], accent_color_blue, 0);
        }
    }
}

void display_init_screens_kb(void) {
    eh_screen_splash.init();
    init_screen_layout();
    eh_screen_hid.init();
    eh_screen_volume.init();
    display_process_layer_state(layer_state);
    change_screen_state = SCREEN_SPLASH;
}

bool display_process_hid_data(hid_data_t *hid_data) {
    if (!hid_data->hid_changed) return is_hid_active();

    hid_data->hid_changed = false;

    eh_screen_hid.update_hid(hid_data);

    if (hid_data->time_changed) {
        hid_data->time_changed = false;
    }
    if (hid_data->volume_changed) {
        eh_screen_volume.update_hid(hid_data);
        change_screen_state      = SCREEN_VOLUME;
        hid_data->volume_changed = false;
        screen_timer             = timer_read32();
    }
    if (hid_data->media_artist_changed) {
        change_screen_state            = SCREEN_HID;
        hid_data->media_artist_changed = false;
    }
    if (hid_data->media_title_changed) {
        change_screen_state           = SCREEN_HID;
        hid_data->media_title_changed = false;
    }

    return is_hid_active();
}

static const char *PROGMEM LAYER_NAME[] = {
    "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN",
};

const char *layer_upper_name(uint8_t layer) {
    if (layer < 16) {
        return LAYER_NAME[layer];
    } else {
        return "UNDEFINED";
    }
}

uint16_t get_keycode(int layer, int row, int col) {
    uint16_t keycode = dynamic_keymap_get_keycode(layer, row, col);
    if (keycode == KC_TRANSPARENT) keycode = dynamic_keymap_get_keycode(0, row, col);
    return keycode;
}

uint16_t get_encoder_keycode(int layer, int encoder, bool clockwise) {
    uint16_t keycode = dynamic_keymap_get_encoder(layer, encoder, clockwise);
    if (keycode == KC_TRANSPARENT) keycode = dynamic_keymap_get_encoder(0, encoder, clockwise);
    return keycode;
}

static int update_layer_index = 0;

void display_process_layer_state(uint8_t layer) {
    if (!is_display_enabled()) return;

    change_screen_state = SCREEN_LAYOUT;

    const char *layer_label = get_layer_label(layer);
    lv_label_set_text(label_layer_small, layer_label);
    eh_screen_hid.update_layer(layer);

    update_layer_index = 0;
}

void update_layer_task(void) {
    if (update_layer_index >= 15) return;
    uint8_t  layer   = get_current_layer();
    uint16_t keycode = KC_TRANSPARENT;
    if (update_layer_index < 12)
        keycode = get_keycode(layer, update_layer_index / 3 + 1, update_layer_index % 3);
    else if (update_layer_index == 13)
        keycode = get_keycode(layer, 0, 2);
    else if (update_layer_index == 12)
        keycode = get_encoder_keycode(layer, 0, false);
    else if (update_layer_index == 14)
        keycode = get_encoder_keycode(layer, 0, true);
    lv_label_set_text(key_labels[update_layer_index], keycode_to_str(keycode));
    update_layer_index += 1;
}

void update_screen_state(void) {
    screen_timer = timer_read32();
    screen_state = change_screen_state;
    switch (screen_state) {
        case SCREEN_SPLASH:
            eh_screen_splash.load();
            display_turn_on();
            break;
        case SCREEN_HID:
            eh_screen_hid.load();
            display_turn_on();
            break;
        case SCREEN_LAYOUT:
            lv_scr_load(screen_layout);
            display_turn_on();
            break;
        case SCREEN_VOLUME:
            eh_screen_volume.load();
            display_turn_on();
            break;
        case SCREEN_OFF:
            display_turn_off();
            break;
    }
}

void display_housekeeping_task(void) {
    if (!is_display_enabled()) return;

    update_layer_task();

    hid_data_t    *hid_data   = get_hid_data();
    bool           hid_active = display_process_hid_data(hid_data);
    static uint8_t prev_lang  = 0;
    uint8_t        cur_lang   = get_cur_lang();
    eh_screen_hid.update_layout(cur_lang);
    if (prev_lang != cur_lang) {
        change_screen_state = SCREEN_HID;
        prev_lang           = cur_lang;
    }

    if (screen_state == change_screen_state) {
        uint32_t screen_elapsed   = timer_elapsed32(screen_timer);
        uint32_t activity_elapsed = last_input_activity_elapsed();

        switch (screen_state) {
            case SCREEN_SPLASH:
                if (screen_elapsed > 2 * 1000) {
                    change_screen_state = SCREEN_LAYOUT;
                }
                break;

            case SCREEN_LAYOUT:
                if (hid_active && activity_elapsed > 10 * 1000) {
                    change_screen_state = SCREEN_HID;
                } else if (activity_elapsed > EH_TIMEOUT) {
                    change_screen_state = SCREEN_OFF;
                }
                break;

            case SCREEN_HID:
                if (!hid_active) {
                    change_screen_state = SCREEN_LAYOUT;
                } else if (activity_elapsed > EH_TIMEOUT && screen_elapsed > 10 * 1000) {
                    change_screen_state = SCREEN_OFF;
                }
                break;

            case SCREEN_VOLUME:
                if (screen_elapsed > 2 * 1000) {
                    change_screen_state = SCREEN_HID;
                }
                break;

            case SCREEN_OFF:
                if (activity_elapsed < EH_TIMEOUT) {
                    change_screen_state = SCREEN_LAYOUT;
                }
                break;
        }
    }
    if (change_screen_state != screen_state) {
        update_screen_state();
        return;
    }
}

void suspend_power_down_kb(void) {
    display_turn_off();
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    display_turn_on();
    suspend_wakeup_init_user();
}
