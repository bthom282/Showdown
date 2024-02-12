#ifndef RASTER_H
#define RASTER_H

#include "types.h"

#define INVADER_HEIGHT 16
#define BITMAP_HEIGHT 16
#define BITMAP_8_HEIGHT 8
#define BITMAP_32_HEIGHT 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

/* [TO DO] the functions below are examples. Replace them! */

void plot_something_1(UINT16 *base, int x, int y, ...);
void plot_something_2(UINT32 *base, int x, int y, ...);

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void clear_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap16, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height);
void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height);
void clear_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height);
void plot_pixel(char *base, int x, int y);
void plot_char(UINT8 *base, int x, int y, char c);
void plot_vline(char *base, int x, int s_y, int e_y);

#endif
