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

void input_handler(char input, struct Model *model, int *quit);

#endif
