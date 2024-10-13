#include "display.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include "ergohaven_ruen.h"
#include "hid.h"
#include "ergohaven.h"
#include "k03pro.h"
#include "ergohaven_display.h"

static uint16_t home_screen_timer = 0;

/* screens */
static lv_obj_t *screen_media;

/* media screen content */
static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

void init_screen_media(void) {
    screen_media = lv_obj_create(NULL);
    lv_obj_add_style(screen_media, &style_screen, 0);
    use_flex_column(screen_media);
    lv_obj_set_flex_align(screen_media, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    label_media_artist = lv_label_create(screen_media);
    lv_label_set_text(label_media_artist, "N/A");
    lv_label_set_long_mode(label_media_artist, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_artist, lv_pct(90));
    lv_obj_set_style_text_align(label_media_artist, LV_TEXT_ALIGN_CENTER, 0);

    label_media_title = lv_label_create(screen_media);
    lv_label_set_text(label_media_title, "N/A");
    lv_label_set_long_mode(label_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_media_title, lv_pct(90));
    lv_obj_set_style_text_align(label_media_title, LV_TEXT_ALIGN_CENTER, 0);
}

void display_init_screens_kb(void) {
    eh_screen_home.init();
    eh_screen_volume.init();
    init_screen_media();
    display_turn_on();
}

void start_home_screen_timer(void) {
    dprint("start_home_screen_timer\n");
    home_screen_timer = timer_read();
}

void display_process_hid_data(hid_data_t *hid_data) {
    dprintf("display_process_hid_data");
    if (!hid_data->hid_changed) return;
    hid_data->hid_changed = false;

    eh_screen_volume.update_hid(hid_data);
    eh_screen_home.update_hid(hid_data);

    if (hid_data->time_changed) {
        hid_data->time_changed = false;
    }
    if (hid_data->volume_changed) {
        eh_screen_volume.load();
        start_home_screen_timer();
        hid_data->volume_changed = false;
    }
    if (hid_data->media_artist_changed) {
        lv_label_set_text(label_media_artist, hid_data->media_artist);
        lv_scr_load(screen_media);
        start_home_screen_timer();
        hid_data->media_artist_changed = false;
    }
    if (hid_data->media_title_changed) {
        lv_label_set_text(label_media_title, hid_data->media_title);
        lv_scr_load(screen_media);
        start_home_screen_timer();
        hid_data->media_title_changed = false;
    }
}

void display_process_layer_state(uint8_t layer) {
    if (!is_display_enabled()) return;
    eh_screen_home.update_layer(layer);
}

void display_housekeeping_task(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        home_screen_timer = 0;
        eh_screen_home.load();
    }

    uint8_t mods = get_mods() | get_oneshot_mods();
    eh_screen_home.update_mods(mods);

    hid_data_t *hid_data = get_hid_data();
    display_process_hid_data(hid_data);
    eh_screen_home.update_layout(get_cur_lang());

    led_t led_state = host_keyboard_led_state();
    led_state.caps_lock |= get_caps_word();
    eh_screen_home.update_leds(led_state);

    display_process_layer_state(get_current_layer());
}
