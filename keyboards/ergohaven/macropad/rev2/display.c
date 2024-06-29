#include "display.h"
#include "qp.h"
#include "lvgl_helpers.h"
#include "ergohaven_ruen.h"
#include "hid.h"
#include "ergohaven.h"

static uint16_t home_screen_timer = 0;

static bool display_enabled;

static painter_device_t display;

/* shared styles */
lv_style_t style_screen;
lv_style_t style_container;
lv_style_t style_button;
lv_style_t style_button_active;

/* screens */
static lv_obj_t *screen_test;
static lv_obj_t *screen_home;
static lv_obj_t *screen_volume;
static lv_obj_t *screen_media;

/* home screen content */
static lv_obj_t *label_time;
static lv_obj_t *label_volume_home;
static lv_obj_t *txt_layer;
static lv_obj_t *label_layer;
static lv_obj_t *label_version;

static lv_obj_t *key_labels[15];
static lv_obj_t *label_layer_small;

/* volume screen content */
static lv_obj_t *arc_volume;
static lv_obj_t *label_volume_arc;

/* media screen content */
static lv_obj_t *label_media_artist;
static lv_obj_t *label_media_title;

/* public function to be used in keymaps */
bool is_display_enabled(void) {
    return display_enabled;
}

void init_styles(void) {
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
    lv_style_set_text_color(&style_button, lv_palette_main(LV_PALETTE_TEAL));

    lv_style_init(&style_button_active);
    lv_style_set_bg_color(&style_button_active, lv_palette_main(LV_PALETTE_TEAL));
    lv_style_set_bg_opa(&style_button_active, LV_OPA_100);
    lv_style_set_text_color(&style_button_active, lv_color_black());
}

void init_screen_home(void) {
    screen_test = lv_scr_act();
    lv_obj_add_style(screen_test, &style_screen, 0);
    use_flex_column(screen_test);
    lv_obj_set_scrollbar_mode(screen_test, LV_SCROLLBAR_MODE_OFF);

    label_layer_small = lv_label_create(screen_test);
    lv_label_set_text(label_layer_small, "layer");
    lv_obj_set_style_pad_top(label_layer_small, 10, 0);
    lv_obj_set_style_pad_bottom(label_layer_small, 5, 0);
    lv_obj_set_style_text_color(label_layer_small, lv_palette_main(LV_PALETTE_TEAL), 0);

    lv_obj_t *cont = lv_obj_create(screen_test);
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
            lv_obj_set_size(obj, 231, 20);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_add_style(obj, &style_screen, 0);
            lv_obj_set_style_border_opa(obj, 0, 0);
        }
        lv_obj_t *obj = lv_obj_create(cont);
        lv_obj_set_size(obj, 77, 40);
        lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_style(obj, &style_screen, 0);

        key_labels[i] = lv_label_create(obj);
        lv_obj_center(key_labels[i]);
    }

    screen_home = lv_obj_create(NULL);
    lv_obj_add_style(screen_home, &style_screen, 0);
    use_flex_column(screen_home);

    label_volume_home = lv_label_create(screen_home);
    lv_label_set_text(label_volume_home, "Ergohaven");

    label_time = lv_label_create(screen_home);
    lv_label_set_text(label_time, "Macropad");
    lv_obj_set_style_text_font(label_time, &lv_font_montserrat_40, LV_PART_MAIN);

    txt_layer = lv_label_create(screen_home);
    lv_label_set_text(txt_layer, "Layer:");

    label_layer = lv_label_create(screen_home);
    lv_label_set_text(label_layer, "");
    lv_obj_set_style_text_font(label_layer, &lv_font_montserrat_40, LV_PART_MAIN);
    display_process_layer_state(0);

    lv_obj_t *mods = lv_obj_create(screen_home);
    lv_obj_add_style(mods, &style_container, 0);
    use_flex_row(mods);

    lv_obj_t *bottom_row = lv_obj_create(screen_home);
    lv_obj_add_style(bottom_row, &style_container, 0);
    use_flex_row(bottom_row);

    label_version = lv_label_create(screen_home);
    lv_label_set_text(label_version, EH_VERSION_STR);
}

void init_screen_volume(void) {
    screen_volume = lv_obj_create(NULL);
    lv_obj_add_style(screen_volume, &style_screen, 0);

    arc_volume = lv_arc_create(screen_volume);
    lv_obj_set_size(arc_volume, 200, 200);
    lv_obj_center(arc_volume);

    label_volume_arc = lv_label_create(screen_volume);
    lv_label_set_text(label_volume_arc, "00");
    lv_obj_set_style_text_font(label_volume_arc, &lv_font_montserrat_40, LV_PART_MAIN);
    lv_obj_center(label_volume_arc);

    lv_obj_t *volume_text_label = lv_label_create(screen_volume);
    lv_label_set_text(volume_text_label, "Volume");
    lv_obj_align(volume_text_label, LV_ALIGN_BOTTOM_MID, 0, -50);
}

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

bool display_init_kb(void) {
    display_enabled = false;
    dprint("display_init_kb - start\n");

    display = qp_st7789_make_spi_device(240, 280, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 16, 3);
    qp_set_viewport_offsets(display, 0, 20);

    if (!qp_init(display, QP_ROTATION_180) || !qp_power(display, true) || !qp_lvgl_attach(display)) return display_enabled;

    dprint("display_init_kb - initialised\n");

    lv_disp_t  *lv_display = lv_disp_get_default();
    lv_theme_t *lv_theme   = lv_theme_default_init(lv_display, lv_palette_main(LV_PALETTE_TEAL), lv_palette_main(LV_PALETTE_BLUE), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(lv_display, lv_theme);
    init_styles();

    init_screen_home();
    init_screen_volume();
    init_screen_media();
    display_enabled = true;

    return display_enabled;
}

void start_home_screen_timer(void) {
    dprint("start_home_screen_timer\n");
    home_screen_timer = timer_read();
}

void display_process_hid_data(struct hid_data_t *hid_data) {
    dprintf("display_process_hid_data");
    if (hid_data->time_changed) {
        lv_label_set_text_fmt(label_time, "%02d:%02d", hid_data->hours, hid_data->minutes);
        hid_data->time_changed = false;
    }
    if (hid_data->volume_changed) {
        lv_label_set_text_fmt(label_volume_home, "Vol: %02d%%", hid_data->volume);
        lv_label_set_text_fmt(label_volume_arc, "%02d", hid_data->volume);
        lv_arc_set_value(arc_volume, hid_data->volume);
        lv_scr_load(screen_volume);
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

static const char *PROGMEM LAYER_NAME[] = {
    "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN",
};

const char *keycode_to_str(uint16_t keycode) {
    static char buf[16];
    switch (keycode) {
        case KC_1 ... KC_0:
            sprintf(buf, "%d", (keycode - KC_1 + 1) % 10);
            return buf;
        case KC_A ... KC_Z:
            sprintf(buf, "%c", keycode - KC_A + 'A');
            return buf;

        case KC_ENTER:
            return LV_SYMBOL_NEW_LINE;
        case KC_ESCAPE:
            return "Escape";
        case KC_BACKSPACE:
            return LV_SYMBOL_BACKSPACE;
        case KC_TAB:
            return "Tab";
        case KC_SPACE:
            return "Space";
        case KC_MINUS:
            return "-";
        case KC_EQUAL:
            return "=";
        case KC_LEFT_BRACKET:
            return "[";
        case KC_RIGHT_BRACKET:
            return "]";
        case KC_BACKSLASH:
            return "\\";
        case KC_NONUS_HASH:
            return "#";
        case KC_SEMICOLON:
            return ";";
        case KC_QUOTE:
            return "\"";
        case KC_GRAVE:
            return "`";
        case KC_COMMA:
            return ",";
        case KC_DOT:
            return ".";
        case KC_SLASH:
            return "/";
        case KC_CAPS_LOCK:
            return "CpsLk";
        case KC_F1 ... KC_F12:
            sprintf(buf, "F%d", keycode - KC_F1 + 1);
            return buf;
        case KC_PRINT_SCREEN:
            return LV_SYMBOL_IMAGE;
        case KC_SCROLL_LOCK:
            return "ScrLk";
        case KC_PAUSE:
            return "Pause";
        case KC_INSERT:
            return "Insert";
        case KC_HOME:
            return "Home";
        case KC_PAGE_UP:
            return "Pg" LV_SYMBOL_UP;
        case KC_DELETE:
            return "Delete";
        case KC_END:
            return "End";
        case KC_PAGE_DOWN:
            return "Pg" LV_SYMBOL_DOWN;
        case KC_RIGHT:
            return LV_SYMBOL_RIGHT;
        case KC_LEFT:
            return LV_SYMBOL_LEFT;
        case KC_DOWN:
            return LV_SYMBOL_DOWN;
        case KC_UP:
            return LV_SYMBOL_UP;
        case KC_NUM_LOCK:
            return "NumLk";
        case KC_KP_SLASH:
            return "/"; //
        case KC_KP_ASTERISK:
            return "*"; //
        case KC_KP_MINUS:
            return LV_SYMBOL_MINUS;
        case KC_KP_PLUS:
            return LV_SYMBOL_PLUS;
        case KC_KP_ENTER:
            return LV_SYMBOL_NEW_LINE;
        case KC_KP_1 ... KC_KP_9:
            sprintf(buf, "%d", (keycode - KC_KP_1 + 1) % 10);
            return buf;
        case KC_KP_DOT:
            return ".";
        case KC_NONUS_BACKSLASH:
            return "\\";
        case KC_APPLICATION:
            return LV_SYMBOL_SETTINGS;
        case KC_KB_POWER:
            return LV_SYMBOL_POWER;
        case KC_KP_EQUAL:
            return "="; //
        case KC_F13:
        case KC_F24:
            sprintf(buf, "F%d", keycode - KC_F13 + 13);
            return buf;
        case KC_EXECUTE:
            return "Execute"; //
        case KC_HELP:
            return "Help"; //
        case KC_MENU:
            return "Menu"; //
        case KC_SELECT:
            return "Select"; //
        case KC_STOP:
            return "Stop"; //
        case KC_AGAIN:
            return "Again"; //
        case KC_UNDO:
            return "Undo"; //
        case KC_CUT:
            return LV_SYMBOL_CUT;
        case KC_COPY:
            return LV_SYMBOL_COPY;
        case KC_PASTE:
            return LV_SYMBOL_PASTE;
        case KC_FIND:
            return "Find";
        case KC_KB_MUTE:
            return LV_SYMBOL_MUTE;
        case KC_KB_VOLUME_UP:
            return LV_SYMBOL_VOLUME_MAX;
        case KC_KB_VOLUME_DOWN:
            return LV_SYMBOL_VOLUME_MID;
        case KC_LOCKING_CAPS_LOCK:
            return "Locking_Caps_Lock";
        case KC_LOCKING_NUM_LOCK:
            return "Locking_Num_Lock";
        case KC_LOCKING_SCROLL_LOCK:
            return "Locking_Scroll_Lock";
        case KC_KP_COMMA:
            return ",";
        case KC_KP_EQUAL_AS400:
            return "Kp_Equal_As400";
        case KC_INTERNATIONAL_1:
            return "International_1";
        case KC_INTERNATIONAL_2:
            return "International_2";
        case KC_INTERNATIONAL_3:
            return "International_3";
        case KC_INTERNATIONAL_4:
            return "International_4";
        case KC_INTERNATIONAL_5:
            return "International_5";
        case KC_INTERNATIONAL_6:
            return "International_6";
        case KC_INTERNATIONAL_7:
            return "International_7";
        case KC_INTERNATIONAL_8:
            return "International_8";
        case KC_INTERNATIONAL_9:
            return "International_9";
        case KC_LANGUAGE_1:
            return "Language_1";
        case KC_LANGUAGE_2:
            return "Language_2";
        case KC_LANGUAGE_3:
            return "Language_3";
        case KC_LANGUAGE_4:
            return "Language_4";
        case KC_LANGUAGE_5:
            return "Language_5";
        case KC_LANGUAGE_6:
            return "Language_6";
        case KC_LANGUAGE_7:
            return "Language_7";
        case KC_LANGUAGE_8:
            return "Language_8";
        case KC_LANGUAGE_9:
            return "Language_9";
        case KC_ALTERNATE_ERASE:
            return "Alternate_Erase";
        case KC_SYSTEM_REQUEST:
            return "System_Request";
        case KC_CANCEL:
            return "Cancel";
        case KC_CLEAR:
            return "Clear";
        case KC_PRIOR:
            return "Prior";
        case KC_RETURN:
            return "Return";
        case KC_SEPARATOR:
            return "Separator";
        case KC_OUT:
            return "Out";
        case KC_OPER:
            return "Oper";
        case KC_CLEAR_AGAIN:
            return "Clear_Again";
        case KC_CRSEL:
            return "Crsel";
        case KC_EXSEL:
            return "Exsel";
        case KC_SYSTEM_POWER:
            return LV_SYMBOL_POWER;
        case KC_SYSTEM_SLEEP:
            return "System_Sleep";
        case KC_SYSTEM_WAKE:
            return "System_Wake";
        case KC_AUDIO_MUTE:
            return LV_SYMBOL_MUTE;
        case KC_AUDIO_VOL_UP:
            return LV_SYMBOL_VOLUME_MAX;
        case KC_AUDIO_VOL_DOWN:
            return LV_SYMBOL_VOLUME_MID;
        case KC_MEDIA_NEXT_TRACK:
            return LV_SYMBOL_NEXT;
        case KC_MEDIA_PREV_TRACK:
            return LV_SYMBOL_PREV;
        case KC_MEDIA_STOP:
            return LV_SYMBOL_STOP;
        case KC_MEDIA_PLAY_PAUSE:
            return LV_SYMBOL_PAUSE;
        case KC_MEDIA_SELECT:
            return LV_SYMBOL_OK;
        case KC_MEDIA_EJECT:
            return LV_SYMBOL_EJECT;
        case KC_MAIL:
            return "Mail";
        case KC_CALCULATOR:
            return "Calculator";
        case KC_MY_COMPUTER:
            return "My_Computer";
        case KC_WWW_SEARCH:
            return "Www_Search";
        case KC_WWW_HOME:
            return LV_SYMBOL_HOME;
        case KC_WWW_BACK:
            return "Www_Back";
        case KC_WWW_FORWARD:
            return "Www_Forward";
        case KC_WWW_STOP:
            return "Www_Stop";
        case KC_WWW_REFRESH:
            return "Www_Refresh";
        case KC_WWW_FAVORITES:
            return "Www_Favorites";
        case KC_MEDIA_FAST_FORWARD:
            return "Media_Fast_Forward";
        case KC_MEDIA_REWIND:
            return "Media_Rewind";
        case KC_BRIGHTNESS_UP:
            return "Brightness_Up";
        case KC_BRIGHTNESS_DOWN:
            return "Brightness_Down";
        case KC_CONTROL_PANEL:
            return "Control_Panel";
        case KC_ASSISTANT:
            return "Assistant";
        case KC_MISSION_CONTROL:
            return "Mission_Control";
        case KC_LAUNCHPAD:
            return "Launchpad";
        case KC_MS_UP:
            return "M" LV_SYMBOL_UP;
        case KC_MS_DOWN:
            return "M" LV_SYMBOL_DOWN;
        case KC_MS_LEFT:
            return "M" LV_SYMBOL_LEFT;
        case KC_MS_RIGHT:
            return "M" LV_SYMBOL_RIGHT;
        case KC_MS_BTN1:
            return "M1";
        case KC_MS_BTN2:
            return "M2";
        case KC_MS_BTN3:
            return "M3";
        case KC_MS_BTN4:
            return "M4";
        case KC_MS_BTN5:
            return "M5";
        case KC_MS_BTN6:
            return "M6";
        case KC_MS_BTN7:
            return "M7";
        case KC_MS_BTN8:
            return "M8";
        case KC_MS_WH_UP:
            return "W" LV_SYMBOL_UP;
        case KC_MS_WH_DOWN:
            return "W" LV_SYMBOL_DOWN;
        case KC_MS_WH_LEFT:
            return "W" LV_SYMBOL_LEFT;
        case KC_MS_WH_RIGHT:
            return "W" LV_SYMBOL_RIGHT;
        case KC_MS_ACCEL0:
            return "Ms_Accel0";
        case KC_MS_ACCEL1:
            return "Ms_Accel1";
        case KC_MS_ACCEL2:
            return "Ms_Accel2";
        case KC_LEFT_CTRL:
            return "Ctrl";
        case KC_LEFT_SHIFT:
            return "Shift";
        case KC_LEFT_ALT:
            return "Alt";
        case KC_LEFT_GUI:
            return "Gui";
        case KC_RIGHT_CTRL:
            return "Ctrl";
        case KC_RIGHT_SHIFT:
            return "Shift";
        case KC_RIGHT_ALT:
            return "Alt";
        case KC_RIGHT_GUI:
            return "Gui";

        case QK_BOOT:
            return "Reset";
        case LAYER_NEXT:
            return LV_SYMBOL_RIGHT LV_SYMBOL_RIGHT;
        case LAYER_PREV:
            return LV_SYMBOL_LEFT LV_SYMBOL_LEFT;
        default:
            return "Unkn";
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

void display_process_layer_state(uint8_t layer) {
    if (0 <= layer && layer < 16) {
        lv_label_set_text(label_layer, LAYER_NAME[layer]);
        lv_label_set_text(label_layer_small, LAYER_NAME[layer]);
    } else {
        lv_label_set_text(label_layer, "UNDEFINED");
        lv_label_set_text(label_layer_small, "UNDEFINED");
    }

    for (int i = 0; i < 15; i++) {
        uint16_t keycode = KC_TRANSPARENT;
        if (i < 12)
            keycode = get_keycode(layer, i / 3 + 1, i % 3);
        else if (i == 13)
            keycode = get_keycode(layer, 0, 2);
        else if (i == 12)
            keycode = get_encoder_keycode(layer, 0, false);
        else if (i == 14)
            keycode = get_encoder_keycode(layer, 0, true);
        lv_label_set_text(key_labels[i], keycode_to_str(keycode));
    }
}

void display_housekeeping_task(void) {
    if (home_screen_timer && timer_elapsed(home_screen_timer) > 5000) {
        home_screen_timer = 0;
        lv_scr_load(screen_test);
    }

    if (last_input_activity_elapsed() > EH_TIMEOUT) {
        qp_power(display, false);
        return;
    } else {
        qp_power(display, true);
    }

    struct hid_data_t *hid_data = get_hid_data();
    display_process_hid_data(hid_data);
}
