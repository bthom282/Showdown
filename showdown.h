#ifndef SHOWDOWN_H
#define SHOWDOWN_H

#include <osbind.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "types.h"
#include "raster.h"
#include "splash.h"
#include "input.h"
#include "video.h"
#include "isr.h"
#include "ikbd.h"
#include "effects.h"
#include "psg.h" 
#include "music.h"

extern int mouse_enabled;

void swap_buffers (UINT32** base32, UINT32** back_buffer_ptr);

void splash_menu(UINT32 *base, UINT32 *base2);

void main_game(UINT32 *base, UINT32 *base2, const int avatar, const int players);

void print_menu(UINT32 *base);

void menu_sel(UINT32 *base, int *players, int *quit);

void print_avatar_sel(UINT32 *base);

void avatar_sel(UINT32 *base, int *avatar);

UINT32 get_time();

UINT32* get_buffer();

#endif
