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

UINT32 get_time();

UINT32* get_buffer();

void swap_buffers (UINT32** base32, UINT32** back_buffer_ptr);

void splash_menu(UINT32 *base1, UINT32 *base2);

void main_game(UINT32 *base1, UINT32 *base2, int players);

#endif
