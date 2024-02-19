#ifndef RASTER_H
#define RASTER_H

#include "types.h"
#include "font.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_SCREEN 32000
#define WORDS_PER_SCREEN 16000
#define LONGS_PER_SCREEN 8000
#define BITMAP_HEIGHT 16
#define BITMAP_8_HEIGHT 8
#define BITMAP_32_HEIGHT 32
#define CLEAR32 0x00000000

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void clear_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap16, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height, int state);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height);
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height);
void clear_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height);
void plot_char(UINT8 *base, int x, int y, char c);
void fill_screen(UINT32 *base, char pattern);
void clear_screen(UINT32 *base);
void fill_rec(UINT32 *base,int x, int y, int height, int width);
void print_message(UINT8 *base, char message[], int x_pos, int y_pos);

#endif
