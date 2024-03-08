#ifndef EVENTS_H
#define EVENTS_H

#include "model.h"
#include "TYPES.H"

#define MAX_BULLETS 20
#define MAX_SNAKES 30
#define COWBOY_HEIGHT 32
#define COWBOY_WIDTH 30
#define SNAKE_HEIGHT 30
#define SNAKE_WIDTH 28
#define BULLET_HEIGHT 4
#define BULLET_WIDTH 4

int checkCollision(struct Cowboy *cowboy, struct Snake snake[]);

void shooting(UINT8 *base, struct Cowboy *cowboy, const UINT8 *bitmap8, 
				struct Bullet *active_bullets, int *bullets_fill);

void delete_bullet (struct Bullet *active_bullets[], int *bullet_fill, int index);

unsigned int rand_in_range(UINT32 *seed, UINT16 min, UINT16 max);

void spawn_snakes(struct Snake active_snakes[], int *snakes_fill, UINT32 *seed);

void snake_death(struct Snake *snake[], int index, int snakes_fill, struct Scoreboard *scoreboard);

void cowboy_death (struct Cowboy *cowboy);

/*void game_over((UINT8 *)base, int *isPlaying);*/

/*void game_quit(int *isPlaying);*/

#endif
