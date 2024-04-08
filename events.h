#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"
#include "TYPES.H"
#include "random.h"
#include "raster.h"

int checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

void shooting(struct Cowboy *cowboy, struct Bullet *active_bullets, int *bullets_fill);

void delete_bullet (struct Bullet *active_bullets[], int *bullet_fill, int index);

void spawn_snakes(struct Snake active_snakes[], int *snakes_fill, UINT32 *seed);

void snake_death(struct Snake active_snakes[], int index, int *snakes_fill);

void cowboy_death (struct Cowboy *cowboy);

void wave_bonus(UINT8 *base, int *game_timer, struct Scoreboard *scoreboard);

void gameover(UINT32 *base, char *ch);

/*void game_quit(int *isPlaying);*/

#endif
