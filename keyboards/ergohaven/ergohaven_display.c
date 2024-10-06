#include "ergohaven_display.h"
#include "gpio.h"

painter_device_t display;

lv_color_t accent_color_red;
lv_color_t accent_color_blue;

static bool display_enabled = false;

bool is_display_enabled(void) {
    return display_enabled;
}

__attribute__((weak)) void display_init_styles_kb(void);

__attribute__((weak)) void display_init_screens_kb(void);

bool display_init_kb(void) {
    display_enabled = false;
    dprint("display_init_kb - start\n");

    gpio_set_pin_output(EH_DISPLAY_BACKLIGHT_PIN);

    display = qp_st7789_make_spi_device(240, 280, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);
    qp_set_viewport_offsets(display, 0, 20);

    accent_color_red  = lv_color_make(248, 83, 107);
    accent_color_blue = lv_color_make(84, 189, 191);

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
