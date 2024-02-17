/*******************************************************************************************
Names:		Adam Cole, Brooklyn Thomson

Purpose:	A library containing routines for plotting or clearing static images to the 
		frame buffer.
*******************************************************************************************/
#include "raster.h"

/*******************************************************************************************
Function Name: 	plot_bitmap_16

Details: 	This function plots a 16x16 bitmap with XOR to specifically print white onto 
		our black side panel for lives and possibly other details. It can be modified 
		to print black onto white by changing the "^=" to "=" if we need any 16x16 
		bitmaps in our play area.

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
Function Name: 	clear_bitmap_16

Details: 	This function clearing a 16x16 bitmap with OR to specifically clear white 
		bitmaps (cowboy lives) on our black side panel for lives and possibly other 
		details. It can be modified to clear black text on white background by changing 
		the "|=" to "^=" if we need to clear any 16x16 bitmaps in our play area.

*********************************************************************************************/

void clear_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap16, unsigned int height)
{ 
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		for (i = 0; i < height; i++) {
			*(base + (y*40) + (x >> 4) + (i*40)) |= bitmap16[i];
		}
	}
}

/********************************************************************************************
Function Name: 	plot_bitmap_32
Details: 	This function is used to plot a size 32 bitmap to the screen by ORing. This will
		be used for the cowboy, snakes, and cacti in the game as they appear and travel 
		across the screen.

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
Function Name: 	clear_bitmap_32
Details: 	This function is used to clear a size 32 bitmap from the screen by XORing over 
		the previously plotted bitmap.

*********************************************************************************************/

void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height)
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
Function Name:	plot_bitmap_8

Details: 	This function is used to plot a size 8 bitmap to the screen by ORing. This will 
		be used for the bullets in the game as they appear and travel across the screen.

*********************************************************************************************/

void plot_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x/8) + y * 80;
		for(i = 0; i < height; i++)
		{
			*base |= bitmap8[i] >> x % 8;
			*(base + 1) |= bitmap8[i] << 8 - (x % 8);
			base += 80;
		}
	}
	return;
}

/********************************************************************************************
Function Name: 	clear_bitmap_8
Details: 	This function is used to clear a size 8 bitmap from the screen by XORing over 
		the previously plotted bitmap. This will be used for the bullets in the game 
		as they travel across the screen.

*********************************************************************************************/

void clear_bitmap_8(UINT8 *base, int x, int y, const UINT8 *bitmap8, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x/8) + y * 80;
		for(i = 0; i < height; i++)
		{
			*base ^= bitmap8[i] >> x % 8;
			*(base + 1) ^= bitmap8[i] << 8 - (x % 8);
			base += 80;
		}
	}
	return;
}

/********************************************************************************************
Function Name: 	plot_char
Details: 	This function is used to plot white text to the black side panel. It can be 
		modified to print black onto white by changing the "^=" to "=" if we need any 
		text bitmaps in our play area.

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

/********************************************************************************************
Function Name: 	clear_screen
Details: 	This function clears the entire screen to white.

*********************************************************************************************/


