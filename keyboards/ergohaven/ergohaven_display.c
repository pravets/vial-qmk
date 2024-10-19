#include "ergohaven_display.h"
#include "ergohaven.h"
#include "lvgl_helpers.h"
#include "gpio.h"
#include "ergohaven_ruen.h"
#include "ergohaven_symbols.h"

LV_FONT_DECLARE(ergohaven_symbols_20);
LV_FONT_DECLARE(ergohaven_symbols_28);

painter_device_t display;

/* shared styles */
lv_color_t accent_color_red;
lv_color_t accent_color_blue;

lv_style_t style_screen;
lv_style_t style_container;
lv_style_t style_button;
lv_style_t style_button_active;

static bool display_enabled = false;

bool is_display_enabled(void) {
    return display_enabled;
}

__attribute__((weak)) void display_init_styles_kb(void) {
    accent_color_red       = lv_color_make(248, 83, 107);
    accent_color_blue      = lv_color_make(84, 189, 191);
    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, accent_color_blue, accent_color_red, true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);

    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_black());

    lv_style_init(&style_container);
    lv_style_set_pad_top(&style_container, 0);
    lv_style_set_pad_bottom(&style_container, 0);
    lv_style_set_pad_left(&style_container, 0);
    lv_style_set_pad_right(&style_container, 0);
    lv_style_set_bg_opa(&style_container, 0);
    lv_style_set_border_width(&style_container, 0);
    lv_style_set_width(&style_container, lv_pct(100));
    lv_style_set_height(&style_container, LV_SIZE_CONTENT);

    lv_style_init(&style_button);
    lv_style_set_pad_top(&style_button, 4);
    lv_style_set_pad_bottom(&style_button, 4);
    lv_style_set_pad_left(&style_button, 4);
    lv_style_set_pad_right(&style_button, 4);
    lv_style_set_radius(&style_button, 6);
    lv_style_set_text_color(&style_button, accent_color_blue);

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, accent_color_blue);
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_black());
}

__attribute__((weak)) void display_init_screens_kb(void);

bool display_init_kb(void) {
    display_enabled = false;
    dprint("display_init_kb - start\n");

    gpio_set_pin_output(EH_DISPLAY_BACKLIGHT_PIN);

    display = qp_st7789_make_spi_device(240, 280, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);
    qp_set_viewport_offsets(display, 0, 20);

    if (!qp_init(display, QP_ROTATION_180) || !qp_lvgl_attach(display)) return display_enabled;

    display_enabled = true;
    dprint("display_init_kb - initialised\n");

    display_init_styles_kb();
    display_init_screens_kb();

    return display_enabled;
}

static bool is_display_on = false;

void display_turn_on(void) {
    if (!is_display_on) {
        gpio_write_pin_high(EH_DISPLAY_BACKLIGHT_PIN);
        qp_power(display, true);
        is_display_on = true;
    }
}

void display_turn_off(void) {
    if (is_display_on) {
        is_display_on = false;
        qp_power(display, false);
        gpio_write_pin_low(EH_DISPLAY_BACKLIGHT_PIN);
    }
}

/* Common helpers */

const char *get_layer_label(uint8_t layer) {
    const char *layer_name = layer_upper_name(layer);
    static char buf[32];
    sprintf(buf, EH_SYMBOL_LAYER " %s", layer_name);
    return buf;
}

const char *get_layout_label(uint8_t layout) {
    switch (layout) {
        default:
        case LANG_EN:
            return EH_SYMBOL_GLOBE " EN";
            break;

        case LANG_RU:
            return EH_SYMBOL_GLOBE " RU";
            break;
    }
}

/* Screen helpers */

void dummy_update_hid(hid_data_t *hid) {}
void dummy_update_layout(uint8_t layout) {}
void dummy_update_layer(uint8_t layer) {}
void dummy_update_leds(led_t led_state) {}
void dummy_update_mods(uint8_t layout) {}
void dummy_housekeep(void) {}

/* Screen splash */

static lv_obj_t *screen_splash;
static lv_obj_t *label_version;

LV_IMG_DECLARE(ergohaven_logo);

void init_screen_splash(void) {
    screen_splash = lv_obj_create(NULL);
    lv_obj_add_style(screen_splash, &style_screen, 0);
    use_flex_column(screen_splash);

    lv_obj_t *img = lv_img_create(screen_splash);
    lv_img_set_src(img, &ergohaven_logo);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_top(img, 60, 0);
    lv_obj_set_style_pad_bottom(img, 60, 0);

    label_version = lv_label_create(screen_splash);
    lv_label_set_text(label_version, "v" EH_VERSION_STR);
}

void load_screen_splash(void) {
    lv_scr_load(screen_splash);
}

const eh_screen_t eh_screen_splash = {
    .init          = init_screen_splash,
    .load          = load_screen_splash,
    .update_hid    = dummy_update_hid,
    .update_layout = dummy_update_layout,
    .update_layer  = dummy_update_layer,
    .update_leds   = dummy_update_leds,
    .update_mods   = dummy_update_mods,
    .housekeep     = dummy_housekeep,
};

/* Screen volume */

static lv_obj_t *screen_volume;
static lv_obj_t *arc_volume;
static lv_obj_t *label_volume_arc;

void init_screen_volume(void) {
    screen_volume = lv_obj_create(NULL);
    lv_obj_add_style(screen_volume, &style_screen, 0);

    arc_volume = lv_arc_create(screen_volume);
    lv_obj_set_size(arc_volume, 200, 200);
    lv_obj_center(arc_volume);

    label_volume_arc = lv_label_create(screen_volume);
    lv_label_set_text(label_volume_arc, "00");
    lv_obj_set_style_text_font(label_volume_arc, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_center(label_volume_arc);

    lv_obj_t *volume_text_label = lv_label_create(screen_volume);
    lv_label_set_text(volume_text_label, "Volume");
    lv_obj_align(volume_text_label, LV_ALIGN_BOTTOM_MID, 0, -50);
}

void load_screen_volume(void) {
    lv_scr_load(screen_volume);
}

void update_hid_volume(hid_data_t *hid) {
    lv_arc_set_value(arc_volume, hid->volume);
    lv_label_set_text_fmt(label_volume_arc, "%02d", hid->volume);
}

const eh_screen_t eh_screen_volume = {
    .init          = init_screen_volume,
    .load          = load_screen_volume,
    .update_hid    = update_hid_volume,
    .update_layout = dummy_update_layout,
    .update_layer  = dummy_update_layer,
    .update_leds   = dummy_update_leds,
    .update_mods   = dummy_update_mods,
    .housekeep     = dummy_housekeep,
};

void load_screen(eh_screen_t screen) {
    screen.update_layer(get_current_layer());
    screen.update_layout(get_cur_lang());
    screen.update_hid(get_hid_data());
    screen.update_leds(host_keyboard_led_state());
    screen.update_mods(get_mods() | get_oneshot_mods());
    screen.load();
}

/* Screen home */

static lv_obj_t *screen_home;
static lv_obj_t *label_time;
static lv_obj_t *label_volume_home;
static lv_obj_t *label_shift;
static lv_obj_t *label_ctrl;
static lv_obj_t *label_alt;
static lv_obj_t *label_gui;
static lv_obj_t *label_layer;
static lv_obj_t *label_caps;
static lv_obj_t *label_num;
static lv_obj_t *label_layout;
static lv_obj_t *label_version;

void update_layer_home(uint8_t layer) {
    lv_label_set_text(label_layer, layer_upper_name(layer));
}

void init_screen_home(void) {
    screen_home = lv_scr_act();
    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    label_volume_home = lv_label_create(screen_home);
    lv_label_set_text(label_volume_home, "Ergohaven");

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, EH_SHORT_PRODUCT_NAME);
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, 0);
    use_flex_row(mods);

    label_gui   = create_button(mods, "GUI", &style_button, &style_button_active);
    label_alt   = create_button(mods, "ALT", &style_button, &style_button_active);
    label_ctrl  = create_button(mods, "CTL", &style_button, &style_button_active);
    label_shift = create_button(mods, "SFT", &style_button, &style_button_active);

    label_caps = create_button(mods, "CAPS", &style_button, &style_button_active);
    label_num  = create_button(mods, "NUM", &style_button, &style_button_active);

    lv_obj_t *bottom_row = lv_obj_create(screen_home);
    lv_obj_add_style(bottom_row, &style_container, 0);
    use_flex_row(bottom_row);

    label_layer = lv_label_create(bottom_row);
    lv_label_set_text(label_layer, "");
    lv_obj_align(label_layer, LV_ALIGN_LEFT_MID, 20, 0);
    update_layer_home(0);

    label_layout = lv_label_create(bottom_row);
    lv_label_set_text(label_layout, "");
    lv_obj_align(label_layout, LV_ALIGN_RIGHT_MID, -20, 0);

    label_version = lv_label_create(screen_home);
    lv_label_set_text(label_version, "v" EH_VERSION_STR);
}

void load_screen_home(void) {
    lv_scr_load(screen_home);
}

void update_hid_home(hid_data_t *hid) {
    lv_label_set_text_fmt(label_time, "%02d:%02d", hid->hours, hid->minutes);
    lv_label_set_text_fmt(label_volume_home, "Vol: %02d%%", hid->volume);
    lv_label_set_text_fmt(label_time, "%02d:%02d", hid->hours, hid->minutes);
}

void update_layout_home(uint8_t layout) {
    switch (layout) {
        case LANG_EN:
            lv_label_set_text(label_layout, "EN");
            break;

        case LANG_RU:
            lv_label_set_text(label_layout, "RU");
            break;
    }
}

void update_leds_home(led_t led_state) {
    toggle_state(label_caps, LV_STATE_PRESSED, led_state.caps_lock);
    toggle_state(label_num, LV_STATE_PRESSED, led_state.num_lock);
}

void update_mods_home(uint8_t mods) {
    toggle_state(label_shift, LV_STATE_PRESSED, mods & MOD_MASK_SHIFT);
    toggle_state(label_ctrl, LV_STATE_PRESSED, mods & MOD_MASK_CTRL);
    toggle_state(label_alt, LV_STATE_PRESSED, mods & MOD_MASK_ALT);
    toggle_state(label_gui, LV_STATE_PRESSED, mods & MOD_MASK_GUI);
}

const eh_screen_t eh_screen_home = {
    .init          = init_screen_home,
    .load          = load_screen_home,
    .update_hid    = update_hid_home,
    .update_layout = update_layout_home,
    .update_layer  = update_layer_home,
    .update_leds   = update_leds_home,
    .update_mods   = update_mods_home,
    .housekeep     = dummy_housekeep,
};

/* Screen HID */

static lv_obj_t *screen_hid;

static lv_obj_t *label_hid_time;
static lv_obj_t *label_hid_layer;
static lv_obj_t *label_hid_media_artist;
static lv_obj_t *label_hid_media_title;
static lv_obj_t *label_hid_layout;

void init_screen_hid(void) {
    screen_hid = lv_obj_create(NULL);
    lv_obj_add_style(screen_hid, &style_screen, 0);
    lv_obj_set_layout(screen_hid, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(screen_hid, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen_hid, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(screen_hid, LV_SCROLLBAR_MODE_OFF);

    label_hid_time = lv_label_create(screen_hid);
    lv_label_set_text(label_hid_time, "HH:MM");
    lv_obj_set_style_text_font(label_hid_time, &lv_font_montserrat_48, LV_PART_MAIN);
    lv_obj_set_style_pad_top(label_hid_time, 40, 0);
    lv_obj_set_style_pad_bottom(label_hid_time, 20, 0);

    lv_obj_t *bottom_row = lv_obj_create(screen_hid);
    lv_obj_add_style(bottom_row, &style_container, 0);
    use_flex_row(bottom_row);

    label_hid_layer = lv_label_create(bottom_row);
    lv_label_set_text(label_hid_layer, "");
    lv_obj_set_size(label_hid_layer, 110, 20);
    lv_obj_set_style_text_align(label_hid_layer, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label_hid_layer, &ergohaven_symbols_20, LV_PART_MAIN);

    label_hid_layout = lv_label_create(bottom_row);
    lv_label_set_text(label_hid_layout, "");
    lv_obj_set_size(label_hid_layout, 110, 20);
    lv_obj_set_style_text_align(label_hid_layout, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label_hid_layout, &ergohaven_symbols_20, LV_PART_MAIN);

    label_hid_media_title = lv_label_create(screen_hid);
    lv_label_set_text(label_hid_media_title, "");
    lv_label_set_long_mode(label_hid_media_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_hid_media_title, lv_pct(95));
    lv_obj_set_style_text_align(label_hid_media_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label_hid_media_title, &ergohaven_symbols_28, LV_PART_MAIN);
    lv_obj_set_style_pad_top(label_hid_media_title, 10, 0);
    lv_obj_set_style_pad_bottom(label_hid_media_title, 0, 0);

    label_hid_media_artist = lv_label_create(screen_hid);
    lv_label_set_text(label_hid_media_artist, "");
    lv_label_set_long_mode(label_hid_media_artist, LV_LABEL_LONG_WRAP);
    lv_obj_set_width(label_hid_media_artist, lv_pct(95));
    lv_obj_set_style_text_align(label_hid_media_artist, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(label_hid_media_artist, &ergohaven_symbols_20, LV_PART_MAIN);

    lv_obj_set_style_pad_top(label_hid_media_artist, 0, 0);
    lv_obj_set_style_pad_bottom(label_hid_media_artist, 20, 0);
    lv_obj_set_style_text_color(label_hid_media_artist, accent_color_blue, 0);
}

void load_screen_hid(void) {
    lv_scr_load(screen_hid);
}

void update_hid_hid(hid_data_t *hid) {
    lv_label_set_text_fmt(label_hid_time, "%02d:%02d", hid->hours, hid->minutes);
    lv_label_set_text(label_hid_media_artist, hid->media_artist);
    lv_label_set_text(label_hid_media_title, hid->media_title);
}

void update_layout_hid(uint8_t layout) {
    lv_label_set_text(label_hid_layout, get_layout_label(layout));
}

void update_layer_hid(uint8_t layer) {
    lv_label_set_text(label_hid_layer, get_layer_label(layer));
}

const eh_screen_t eh_screen_hid = {
    .init          = init_screen_hid,
    .load          = load_screen_hid,
    .update_hid    = update_hid_hid,
    .update_layout = update_layout_hid,
    .update_layer  = update_layer_hid,
    .update_leds   = dummy_update_leds,
    .update_mods   = dummy_update_mods,
    .housekeep     = dummy_housekeep,
};
