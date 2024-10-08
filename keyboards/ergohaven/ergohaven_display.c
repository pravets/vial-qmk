#include "ergohaven_display.h"
#include "ergohaven.h"
#include "lvgl_helpers.h"
#include "gpio.h"

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
