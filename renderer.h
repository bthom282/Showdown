#ifndef RENDERER_H
#define RENDERER_H

#include "TYPES.H"
#include "model.h"
#include "BITMAPS.H"
#include "RASTER.H"

void game_start();

void render(UINT32 *base, struct Model *model);

void render_cowboy(UINT32 *base, struct Cowboy cowboy, const UINT32 *bitmap);

void render_bullets(UINT8 *base, struct Bullet *active_bullets, const UINT8 *bitmap8, int bullets_fill);

void render_snakes(UINT32 *base, const struct Snake *active_snakes, int snakes_fill);

void render_side_panel(UINT16 *base);

void render_level1(UINT32 *base, const UINT32 *bitmap);

void render_side_text(UINT8 *base, int players);

void render_score(UINT8 *base, struct Scoreboard *scoreboard);

void render_lives(UINT16 *base, struct Lives lives, const UINT16 *bitmap16);

#endif
