#ifndef EVENTS_H
#define EVENTS_H

#define MAX_BULLETS 20
#define MAX_SNAKES 30

int checkCollision(struct BoundingBox box1, struct BoundingBox box2);

void shooting(UINT8 *base, struct Cowboy *cowboy, const UINT8 *bitmap8, 
				struct Bullet *active_bullets, int *bullets_fill);

void delete_bullet (struct Bullet *active_bullets[], int *bullet_fill, int index);

unsigned int randInRange(unsigned long *seed, unsigned int min, unsigned int max);

void spawn_snakes(struct Snake *active_snakes[], int spawn_x[], int spawn_y[], int *snakes_fill, UINT32 *seed);

void snake_death(struct Snake *snake, int index, int snakes_fill, struct Scoreboard *scoreboard);

void cowboy_death (int *lives_count);

/*void game_over((UINT8 *)base, int *isPlaying);*/

/*void game_quit(int *isPlaying);*/

#endif
