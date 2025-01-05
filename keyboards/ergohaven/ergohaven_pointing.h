#pragma once

#include "quantum.h"
#include "ergohaven.h"

typedef enum {
    POINTING_MODE_NORMAL = 0,
    POINTING_MODE_SNIPER,
    POINTING_MODE_SCROLL,
    POINTING_MODE_TEXT,
} pointing_mode_t;

enum {
    EH_SNP = EH_RSRV11 + 1,
    EH_SCR,
    EH_TXT,
};

bool process_record_pointing(uint16_t keycode, keyrecord_t *record);

void set_scroll_sens(int32_t sens);

void set_sniper_sens(int32_t sens);

void set_text_sens(int32_t sens);

void set_automouse(uint8_t layer);

void set_invert_scroll(bool invert);
