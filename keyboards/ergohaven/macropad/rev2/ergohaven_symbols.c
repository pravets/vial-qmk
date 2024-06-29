/*******************************************************************************
 * Size: 20 px
 * Bpp: 2
 * Opts: --bpp 2 --size 20 --no-compress --font fa-solid-900.woff --range 63145,62761,61453,63692,61829,61932,61664,61442,61705,61829 --format lvgl -o ergohaven_symbols.c
 ******************************************************************************/

#include "qp_lvgl.h"

#ifndef ERGOHAVEN_SYMBOLS
#define ERGOHAVEN_SYMBOLS 1
#endif

#if ERGOHAVEN_SYMBOLS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F002 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xfe,
    0x0, 0x0, 0x3, 0xff, 0xff, 0xc0, 0x0, 0xf,
    0xff, 0xff, 0xf0, 0x0, 0x2f, 0xe0, 0x7, 0xfc,
    0x0, 0x7f, 0x40, 0x0, 0xfe, 0x0, 0xbe, 0x0,
    0x0, 0x7f, 0x0, 0xfd, 0x0, 0x0, 0x3f, 0x0,
    0xfc, 0x0, 0x0, 0x3f, 0x0, 0xfc, 0x0, 0x0,
    0x3f, 0x0, 0xfd, 0x0, 0x0, 0x3f, 0x0, 0xbf,
    0x0, 0x0, 0xbf, 0x0, 0x3f, 0xc0, 0x2, 0xfd,
    0x0, 0x1f, 0xf9, 0x5f, 0xfc, 0x0, 0xb, 0xff,
    0xff, 0xff, 0x40, 0x1, 0xff, 0xff, 0xbf, 0xd0,
    0x0, 0x1b, 0xe4, 0x1f, 0xf4, 0x0, 0x0, 0x0,
    0xb, 0xfd, 0x0, 0x0, 0x0, 0x2, 0xff, 0x0,
    0x0, 0x0, 0x0, 0xbd, 0x0, 0x0, 0x0, 0x0,
    0x14,

    /* U+F00D "" */
    0x14, 0x0, 0x2, 0x47, 0xe0, 0x0, 0xfd, 0xff,
    0x80, 0x3f, 0xe7, 0xfe, 0xf, 0xfd, 0x1f, 0xfb,
    0xff, 0x40, 0x7f, 0xff, 0xd0, 0x1, 0xff, 0xf4,
    0x0, 0xf, 0xff, 0x0, 0x3, 0xff, 0xf8, 0x0,
    0xff, 0xff, 0xe0, 0x3f, 0xf5, 0xff, 0x8f, 0xfd,
    0x7, 0xfe, 0xff, 0x40, 0x1f, 0xe3, 0xd0, 0x0,
    0x7c, 0x0, 0x0, 0x0, 0x0,

    /* U+F0E0 "" */
    0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0xff, 0xff, 0xff, 0xfd, 0xf, 0xff, 0xff, 0xff,
    0xf0, 0xc2, 0xff, 0xff, 0xff, 0x83, 0xf4, 0x7f,
    0xff, 0xfd, 0x1f, 0xfe, 0xf, 0xff, 0xf0, 0xbf,
    0xff, 0xd2, 0xff, 0x87, 0xff, 0xff, 0xf8, 0x7d,
    0x2f, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xfd,

    /* U+F109 "" */
    0x0, 0x6a, 0xaa, 0xaa, 0xaa, 0x40, 0x0, 0xff,
    0xff, 0xff, 0xff, 0xfc, 0x0, 0x7f, 0xff, 0xff,
    0xff, 0xff, 0x40, 0x2f, 0x0, 0x0, 0x0, 0x3,
    0xe0, 0xb, 0xc0, 0x0, 0x0, 0x0, 0xf8, 0x2,
    0xf0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0xbc, 0x0,
    0x0, 0x0, 0xf, 0x80, 0x2f, 0x0, 0x0, 0x0,
    0x3, 0xe0, 0xb, 0xc0, 0x0, 0x0, 0x0, 0xf8,
    0x2, 0xf0, 0x0, 0x0, 0x0, 0x3e, 0x0, 0xbc,
    0x0, 0x0, 0x0, 0xf, 0x80, 0x2f, 0x0, 0x0,
    0x0, 0x3, 0xe0, 0xb, 0xc0, 0x0, 0x0, 0x0,
    0xf8, 0x2, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x0,
    0xbf, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1a, 0xaa,
    0xaa, 0xaa, 0xaa, 0x90, 0x15, 0x55, 0x40, 0x1,
    0x55, 0x55, 0x3f, 0xff, 0xfd, 0x1, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfd, 0x6, 0xaa, 0xaa,
    0xaa, 0xaa, 0xa4, 0x0,

    /* U+F185 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf,
    0x0, 0x0, 0x0, 0x0, 0x7, 0xd0, 0x0, 0x0,
    0x4, 0x3, 0xfc, 0x1, 0x0, 0x3, 0xf9, 0xff,
    0xaf, 0xc0, 0x0, 0xff, 0xff, 0xff, 0xf0, 0x0,
    0x1f, 0xd1, 0x47, 0xf4, 0x0, 0x3, 0xd7, 0xfd,
    0x3c, 0x0, 0x7, 0xe3, 0xff, 0xd7, 0xd0, 0xf,
    0xf2, 0xff, 0xf8, 0xff, 0x4f, 0xfc, 0xbf, 0xff,
    0x3f, 0xf0, 0xbf, 0x2f, 0xff, 0x8f, 0xe0, 0x2,
    0xd3, 0xff, 0xc7, 0x80, 0x0, 0x3c, 0x3f, 0xc3,
    0xc0, 0x0, 0x1f, 0x80, 0x2, 0xf4, 0x0, 0xb,
    0xfe, 0x5b, 0xff, 0x0, 0x3, 0xff, 0xff, 0xff,
    0xc0, 0x0, 0xe4, 0x3f, 0xc1, 0xb0, 0x0, 0x0,
    0x7, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x14, 0x0, 0x0, 0x0,

    /* U+F1EC "" */
    0x1a, 0xaa, 0xaa, 0xa9, 0xb, 0xff, 0xff, 0xff,
    0xfc, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x80, 0x0,
    0x0, 0x3e, 0xf8, 0x0, 0x0, 0x3, 0xef, 0x80,
    0x0, 0x0, 0x3e, 0xf8, 0x0, 0x0, 0x3, 0xef,
    0x80, 0x0, 0x0, 0x3e, 0xff, 0xff, 0xff, 0xff,
    0xef, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xbf, 0xaf,
    0xeb, 0xef, 0x83, 0xe0, 0xf8, 0x3e, 0xf8, 0x3e,
    0xf, 0x83, 0xef, 0xff, 0xff, 0xf8, 0x3e, 0xff,
    0xff, 0xff, 0x83, 0xef, 0xeb, 0xfa, 0xf8, 0x3e,
    0xf8, 0x3e, 0xf, 0x83, 0xef, 0x83, 0xe0, 0xf8,
    0x3e, 0xff, 0xff, 0xff, 0xff, 0xdb, 0xff, 0xff,
    0xff, 0xfc, 0x1a, 0xaa, 0xaa, 0xa9, 0x0,

    /* U+F529 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0x40,
    0x0, 0x0, 0xb, 0xfc, 0x0, 0x0, 0x0, 0xbf,
    0xc0, 0x0, 0x0, 0x7, 0xfc, 0x0, 0x0, 0x0,
    0x1e, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6,
    0xaa, 0xaa, 0xaa, 0xa8, 0xff, 0xff, 0xff, 0xff,
    0xdf, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff,
    0xff, 0xd0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0,
    0x7, 0xfc, 0x0, 0x0, 0x0, 0xbf, 0xc0, 0x0,
    0x0, 0xb, 0xfc, 0x0, 0x0, 0x0, 0x3f, 0x40,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+F6A9 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3c,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x0,
    0x0, 0x3f, 0xc0, 0x0, 0x0, 0x55, 0x7f, 0xf0,
    0x0, 0x4, 0x3f, 0xff, 0xfc, 0xf, 0x4b, 0x8f,
    0xff, 0xff, 0x7, 0xff, 0xf3, 0xff, 0xff, 0xc0,
    0x7f, 0xf0, 0xff, 0xff, 0xf0, 0xf, 0xf4, 0x3f,
    0xff, 0xfc, 0xb, 0xff, 0x4f, 0xff, 0xff, 0x7,
    0xf7, 0xf3, 0xff, 0xff, 0xc0, 0xa0, 0x74, 0x0,
    0x2f, 0xf0, 0x0, 0x0, 0x0, 0x2, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x2f, 0x0, 0x0, 0x0, 0x0,
    0x2, 0x80, 0x0, 0x0,

    /* U+F8CC "" */
    0x0, 0x14, 0x50, 0x0, 0xf, 0xf3, 0xfc, 0x1,
    0xff, 0xcf, 0xfd, 0xf, 0xff, 0x3f, 0xfc, 0xbf,
    0xfc, 0xff, 0xfb, 0xff, 0xf3, 0xff, 0xff, 0xff,
    0xcf, 0xff, 0xff, 0xff, 0x3f, 0xff, 0x0, 0x0,
    0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xf4,
    0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xfc, 0x0,
    0xbf, 0xff, 0x80, 0x0, 0x5, 0x40, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_w = 20, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 105, .adv_w = 220, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 320, .box_w = 20, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 400, .box_w = 25, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 365, .adv_w = 320, .box_w = 21, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 476, .adv_w = 280, .box_w = 18, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 571, .adv_w = 280, .box_w = 18, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 657, .adv_w = 320, .box_w = 21, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 240, .box_w = 15, .box_h = 21, .ofs_x = 0, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xb, 0xde, 0x107, 0x183, 0x1ea, 0x527, 0x6a7,
    0x8ca
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61442, .range_length = 2251, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 9, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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

extern const lv_font_t lv_font_montserrat_20;


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ergohaven_symbols = {
#else
lv_font_t ergohaven_symbols = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 21,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &lv_font_montserrat_20,
#endif
    .user_data = NULL,
};



#endif /*#if ERGOHAVEN_SYMBOLS*/
