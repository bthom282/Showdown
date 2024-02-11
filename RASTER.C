#include "raster.h"

void plot_something_1(UINT16 *base, int x, int y, ...)
{
	/* [TO DO] delete this example function */
}

/********************************************************************************************
Function Name: plot_pixel
Details: 

*********************************************************************************************/

void plot_pixel(char *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
		}
		
/********************************************************************************************
Function Name: plot_vline
Details: This function plots a vertical line

*********************************************************************************************/

void plot_vline(char *base, int x, int s_y, int e_y)
{
	int i; 
	for (i = s_y; i < (e_y - s_y); i--) {
		if (x >= 0 && x < SCREEN_WIDTH && s_y >= 0 && e_y >= 0 && s_y < SCREEN_HEIGHT && e_y < SCREEN_HEIGHT) {
			*(base + s_y * 80 + (x >> 3)) ^= 1 << 7 - (x & 7);
			base += 80;
		}
	}
	return;
}

/********************************************************************************************
Function Name: plot_bitmap_16
Details: This function plots a 16x16 bitmap with XOR to specifically print white onto our black
side panel for lives and possibly other deatils. It can be modified to print white onto black 
by changing the "^=" to "=" if we need any 16x16 bitmaps in our play area.



*********************************************************************************************/

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap16, unsigned int height)
{ 
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		for (i = 0; i < height; i++) {
			*(base + (y*40) + (x >> 4) + (i*40)) ^= bitmap16[i];
		}
	}
}

/********************************************************************************************
Function Name: plot_bitmap_32
Details: 

*********************************************************************************************/

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x/32) + y * 20;
		for(i = 0; i < height; i++)
		{
			*base |= bitmap32[i] >> x % 32;
			*(base + 1) |= bitmap32[i] << 32 - (x % 32);
			base += 20;
		}
	}
	return;
}

/********************************************************************************************
Function Name: clear_bitmap_32
Details: This function is used to clear a size 32 bitmap from the screen by XORing over the 
previously plotted bitmap.

*********************************************************************************************/

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x/32) + y * 20;
		for(i = 0; i < height; i++)
		{
			*base ^= bitmap32[i] >> x % 32;
			*(base + 1) ^= bitmap32[i] << 32 - (x % 32);
			base += 20;
		}
	}
	return;
}

/********************************************************************************************
Function Name: plot_char
Details: 

*********************************************************************************************/

void plot_char(UINT8 *base, int x, int y, char c) {
    /* Calculates the index in the font array */
    int charIndex = (c - 32) * 8;

    /* Print character bitmap at specified position */
    int i;
    for (i = 0; i < 8; i++) {
		*(base + (y*80) + (x >> 3) + (i*80)) ^= font[charIndex+i];
	}
}
