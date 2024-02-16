/*******************************************************************************************
Names:    Adam Cole, Brooklyn Thomson

Purpose:  Implements event-handling functions for each of the specified asynchronous,
          synchronous and condition-based events.
*******************************************************************************************/
#include "events.h"

int checkCollision(BoundingBox box1, BoundingBox box2) {
    /* Calculate the sides of the first box */
    int left1 = box1.position.x;
    int right1 = box1.position.x + box1.size.width;
    int top1 = box1.position.y;
    int bottom1 = box1.position.y + box1.size.height;

    /* Calculate the sides of the second box*/
    int left2 = box2.position.x;
    int right2 = box2.position.x + box2.size.width;
    int top2 = box2.position.y;
    int bottom2 = box2.position.y + box2.size.height;

    /*Check for intersection*/ 
    if (bottom1 < top2 || top1 > bottom2 || right1 < left2 || left1 > right2) {
        /*No intersection*/ 
        return 0;
    } else {
        /*Intersection*/ 
        return 1;
    }
}

void shooting(UINT8 *base, struct Cowboy *cowboy, const UINT8 *bitmap8, 
				struct Bullet *active_bullets, int *bullets_fill) {
	if (cowboy->isFiring == TRUE && (cowboy->yFireDir != 0 || cowboy->xFireDir != 0)) {
		active_bullets[*bullets_fill].position.x = cowboy->position.x;
        active_bullets[*bullets_fill].position.y = cowboy->position.y;
		active_bullets[*bullets_fill].x_dir = cowboy->xFireDir;
		active_bullets[*bullets_fill].y_dir = cowboy->yFireDir;
		active_bullets[*bullets_fill].speed = 3;
		
		if (cowboy->yFireDir == -1 && cowboy->xFireDir == -1) {
			active_bullets[*bullets_fill].position.x -= 2;
			active_bullets[*bullets_fill].position.y -= 2;
		}
		else if (cowboy->yFireDir == -1 && cowboy->xFireDir == 0) {
			active_bullets[*bullets_fill].position.x += 12;
			active_bullets[*bullets_fill].position.y -= 6;
		}
		else if (cowboy->yFireDir == -1 && cowboy->xFireDir == 1) {
			active_bullets[*bullets_fill].position.x += 26;
			active_bullets[*bullets_fill].position.y -= 2;
		}
		else if (cowboy->yFireDir == 0 && cowboy->xFireDir == 1) {
			active_bullets[*bullets_fill].position.x += 26;
			active_bullets[*bullets_fill].position.y += 12;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == 1) {
			active_bullets[*bullets_fill].position.x += 26;
			active_bullets[*bullets_fill].position.y += 26;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == 0) {
			active_bullets[*bullets_fill].position.x += 12;
			active_bullets[*bullets_fill].position.y += 30;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == -1) {
			active_bullets[*bullets_fill].position.x -= 2;
			active_bullets[*bullets_fill].position.y += 26;
		}
		else if (cowboy->yFireDir == 0 && cowboy->xFireDir == -1) {
			active_bullets[*bullets_fill].position.x -= 2;
			active_bullets[*bullets_fill].position.y += 12;
		}
		plot_bitmap_8((UINT8 *) base, (int)active_bullets[*bullets_fill].position.x, 
		(int)active_bullets[*bullets_fill].position.y, bitmap8, BITMAP_8_HEIGHT);
		(*bullets_fill)++;
	}
}

void spawn_snakes(UINT32 *base, struct Snake *active_snakes, int spawn_x[], int spawn_y[], int *snakes_fill, UINT32 *seed) {
	int spawn_loc;

	spawn_loc = randInRange(seed, 0, 15);
	active_snakes[*snakes_fill].position.x = spawn_x[spawn_loc];
	active_snakes[*snakes_fill].position.y = spawn_y[spawn_loc];
	if (spawn_loc >= 0 && spawn_loc <= 3) {
		plot_bitmap_32((UINT32 *) base, spawn_x[spawn_loc], spawn_y[spawn_loc], front_snake_bitmap, BITMAP_32_HEIGHT);
		}
	else if (spawn_loc >= 4 && spawn_loc <= 7) {
		plot_bitmap_32((UINT32 *) base, spawn_x[spawn_loc], spawn_y[spawn_loc], right_snake_bitmap, BITMAP_32_HEIGHT);
		}
	else if (spawn_loc >= 8 && spawn_loc <= 11) {
		plot_bitmap_32((UINT32 *) base, spawn_x[spawn_loc], spawn_y[spawn_loc], left_snake_bitmap, BITMAP_32_HEIGHT);
		}
	else {
		plot_bitmap_32((UINT32 *) base, spawn_x[spawn_loc], spawn_y[spawn_loc], backwards_snake_bitmap, BITMAP_32_HEIGHT);
		}
	(*snakes_fill)++;
}
