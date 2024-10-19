#pragma once

#include "qp.h"
#include "hid.h"

extern lv_color_t accent_color_red;
extern lv_color_t accent_color_blue;

extern lv_style_t style_screen;
extern lv_style_t style_container;
extern lv_style_t style_button;
extern lv_style_t style_button_active;

bool display_init_kb(void);

__attribute__((weak)) void display_init_styles_kb(void);

__attribute__((weak)) void display_init_screens_kb(void);

void display_turn_on(void);

void display_turn_off(void);

bool is_display_enabled(void);

const char *get_layer_label(uint8_t layer);

const char *get_layout_label(uint8_t layer);

/* Common screens */

void dummy_update_hid(hid_data_t *hid);

void dummy_update_layout(uint8_t layout);

void dummy_update_layer(uint8_t layer);

void dummy_update_leds(led_t led_state);

void dummy_update_mods(uint8_t layout);

void dummy_housekeep(void);

typedef struct {
    void (*init)(void);
    void (*load)(void);
    void (*update_hid)(hid_data_t *hid);
    void (*update_layout)(uint8_t layout);
    void (*update_layer)(uint8_t layer);
    void (*update_leds)(led_t led_state);
    void (*update_mods)(uint8_t layout);
    void (*housekeep)(void);
} eh_screen_t;

extern const eh_screen_t eh_screen_splash;
extern const eh_screen_t eh_screen_volume;
extern const eh_screen_t eh_screen_home;
extern const eh_screen_t eh_screen_hid;

void load_screen(eh_screen_t screen);
