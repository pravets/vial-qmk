#pragma once

#include "qp.h"

extern painter_device_t display;

extern lv_color_t accent_color_red;
extern lv_color_t accent_color_blue;

bool display_init_kb(void);

__attribute__((weak)) void display_init_styles_kb(void);

__attribute__((weak)) void display_init_screens_kb(void);

void display_turn_on(void);

void display_turn_off(void);

bool is_display_enabled(void);
