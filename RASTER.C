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
		base += (x>>5) + y * 20;
		for(i = 0; i < 32; i++)
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
		base += (x>>5) + y * 20;
		for(i = 0; i < height; i++)
		{
			*base = bitmap32[i] >> x % 32;
			*(base + 1) = bitmap32[i] << 32 - (x % 32);
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
		base += (x>>3) + y * 80;
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
		base += (x>>3) + y * 80;
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
    int charIndex = (c - 32) << 3;

    /* Print character bitmap at specified position */
    int i;
    for (i = 0; i < 8; i++) {
		*(base + (y*80) + (x >> 3) + (i*80)) ^= font[charIndex+i];
	}
}

/********************************************************************************************
Function Name: 	fill_screen

Details: 	This function fills the entire screen to white if o is passed in, black if 
			-1 is passed in. It can also make various vertical patterns with different
			values passed in.
			
*********************************************************************************************/

void fill_screen(UINT32 *base, char pattern)
{
	int i = 0;
	UINT32 *loc = base;

	while (i++ < LONGS_PER_SCREEN)
		*(loc++) = pattern;
}

/********************************************************************************************
Function Name: 	clear_screen

Details: 	This function clears the entire screen to white.

*********************************************************************************************/
void clear_screen(UINT32 *base)
{
	int i, j;

	for (i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (j = 0; j < 20; j++)
		{
			*(base + j + (i * 20)) = CLEAR32;
		}
	}
	return;
}

/********************************************************************************************
Function Name: 	fill_rec

Details: 	This function fills a rectangular section of bytes on the screen by taking in
			the starting coordinates, the height, and width in bytes.
			
*********************************************************************************************/
void fill_rec(UINT16 *base, int x, int y, int height, int width) {
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i,j;
		base += (x>>4) + y * 40;
		for (i = 0; i < height; i++){ 
			for (j = 0; j < width; j++) {
				*(base++) = -1;
			}
			base += (40-width);
		}
		return;
	}
}


void clear_rec(UINT32 *base, int x, int y, int height, int width){
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i,j;
		base += (x>>5) + y * 20;
		for (i = 0; i < height; i++){ 
			for (j = 0; j < width; j++) {
				*(base++) = 0;
			}
			base += (20-width);
		}
		return;

	/*UINT16 *loc = (UINT16 *) base;
	int k, j;
	for (k = x; k < SCREEN_HEIGHT; k++){ 
		for (j = x; j < 16; j++) {
			*(loc++) = 0;
		}
		loc += 24;
	}
	return*/
	}
}

/*******************************************************************************************
Function Name: 	print_message

Details: 	This function takes in a character array and prints it to the screen starting 
			at the designated area. It advances automatically to print the full message,
			while using the provided font.c file for each character's bitmap.

Sample Call:	print_message((UINT8 *) base, lives, 32, 320);

*********************************************************************************************/

void print_message(UINT8 *base, char message[], int x_pos, int y_pos) {
	int i = 0;
	if (x_pos >= 0 && x_pos < SCREEN_WIDTH && y_pos >= 0 && y_pos < SCREEN_HEIGHT) {
		while (message[i] != '\0') {
			plot_char((UINT8 *) base, x_pos, y_pos, message[i]);
			x_pos += 8;
			i++;
		}
	}
}

/*******************************************************************************************
Function Name: 	plot_splash

Details: 	This function prints a full screen image onto the screen buffer.

Sample Call:	plot_splash((UINT32 *)base, SCREEN_HEIGHT, splash_bitmap);

*********************************************************************************************/

void plot_splash(UINT32 *base, int height, const UINT32 *bitmap)
{
	int i, j, index;
	index = 0;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < 20; j ++)
		{
		*(base + j + (i * 20)) = bitmap[index];
		index++;
		}
	}
}

/*******************************************************************************************
Function Name: 	plot_bitmap_64

Details: 	This function is used to plot a 64 by 64 bitmap and it used for the main menu
			cursor.

Sample Call:	plot_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);

*********************************************************************************************/

void plot_bitmap_64(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x>>5) + y * 20;
		for(i = 0; i < (height*2); i+=2)
		{
			*base |= bitmap32[i] >> x % 32;
			*(base + 1) |= bitmap32[i] << 32 - (x % 32);
			*(base + 1) |= bitmap32[i+1] >> x % 32;
			*(base + 2) |= bitmap32[i+1] << 32 - (x % 32);
			
			base += 20;
		}
	}
	return;
}

/*******************************************************************************************
Function Name: 	clear_bitmap_64

Details: 	This function is used to clear a 64 by 64 bitmap and it used for the main menu
			cursor.

Sample Call:	clear_bitmap_64((UINT32 *)base, 338, 285, cursor, CURSOR_HEIGHT);

*********************************************************************************************/

void clear_bitmap_64(UINT32 *base, int x, int y, const UINT32 *bitmap32, unsigned int height)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
		int i;
		base += (x>>5) + y * 20;
		for(i = 0; i < (height*2); i+=2)
		{
			*base ^= bitmap32[i] >> x % 32;
			*(base + 1) ^= bitmap32[i] << 32 - (x % 32);
			*(base + 1) ^= bitmap32[i+1] >> x % 32;
			*(base + 2) ^= bitmap32[i+1] << 32 - (x % 32);
			
			base += 20;
		}
	}
	return;
}

/*******************************************************************************************
Function Name: 	get_video_base

Details: 	This function that replaces the need for Physbase() to get the video base.

Sample Call:	get_video_base();

*********************************************************************************************/
UINT32 *get_video_base()
{
	UINT8 *videoHigh = VIDEO_REG_HIGH;
	UINT8 *videoMid = VIDEO_REG_MID;
	UINT32 base;
	UINT32 *basePtr;
	long old_ssp = Super(0);

	base = ( (UINT32) *videoHigh << 16);
	base |= ( (UINT32) *videoMid << 8);

	Super(old_ssp);

	basePtr = (UINT32 *)base;

	return basePtr;
}

/*******************************************************************************************
Function Name: 	set_video_base

Details: 	This function that replaces the need for Physbase() to get the video base.

Sample Call:	set_video_base(base);

*********************************************************************************************/
void set_video_base(UINT32 *base)
{
	UINT32 shift = (UINT32)base >> 8;
	UINT16 newBase = (UINT16)shift;
	long old_ssp = Super(0);

	/*setVBase(newBase);*/

	Super(old_ssp);

	return;
}