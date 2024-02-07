#ifndef RASTER_H
#define RASTER_H

#include "types.h"

/* [TO DO] the functions below are examples. Replace them! */

void plot_something_1(UINT16 *base, int x, int y, ...);
void plot_something_2(UINT32 *base, int x, int y, ...);

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void plot_pixel(char *base, int x, int y);
void plot_char(UINT8 *base, int x, int y, char c);
void plot_vline(char *base, int x, int s_y, int e_y);

#endif
