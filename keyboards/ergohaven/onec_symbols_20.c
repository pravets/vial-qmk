/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts: --bpp 2 --size 20 --no-compress --font FontAwesome5-Solid+Brands+Regular.woff --range 61465 --format lvgl -o onec_symbols_20.c
 ******************************************************************************/

#include "qp_lvgl.h"

#ifndef ONEC_SYMBOLS_20
#define ONEC_SYMBOLS_20 1
#endif

#if ONEC_SYMBOLS_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F019 "" */
    0x0, 0x0, 0x55, 0x0, 0x0, 0x0, 0x1, 0xff,
    0x40, 0x0, 0x0, 0x2, 0xff, 0x80, 0x0, 0x0,
    0x2, 0xff, 0x80, 0x0, 0x0, 0x2, 0xff, 0x80,
    0x0, 0x0, 0x2, 0xff, 0x80, 0x0, 0x0, 0x2,
    0xff, 0x80, 0x0, 0x0, 0x2, 0xff, 0x80, 0x0,
    0x1, 0xff, 0xff, 0xff, 0x40, 0x1, 0xff, 0xff,
    0xff, 0x40, 0x0, 0x7f, 0xff, 0xfd, 0x0, 0x0,
    0x1f, 0xff, 0xf4, 0x0, 0x0, 0x7, 0xff, 0xd0,
    0x0, 0x0, 0x1, 0xff, 0x40, 0x0, 0x6a, 0xa8,
    0x7d, 0x2a, 0xa9, 0xff, 0xff, 0x0, 0xff, 0xff,
    0xff, 0xff, 0xeb, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0x6f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x15, 0x55, 0x55, 0x55,
    0x54
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61465, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t onec_symbols_20 = {
#else
lv_font_t onec_symbols_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 21,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -7,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if ONEC_SYMBOLS_20*/

