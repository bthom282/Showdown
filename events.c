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

/*******************************************************************************************
Function Name: 	shooting

Details: 	This function uses to fire bullets if the isFiring bool is true. It checks the
		shooting direction of the player's avatar, and creates an instance of a bullet
  		in the active_bullets struct array, then it plot its bitmap in the appropriate
    		location around the avatar.

Sample Call:	cowboy1.yFireDir = -1;  This will be done with key inputs.
		cowboy1.xFireDir = 0;
		shooting((UINT8 *)base, &cowboy1, (UINT8 *)bullet_bitmap, active_bullets, &bullets_fill);
*********************************************************************************************/

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

/*******************************************************************************************
Function Name: 	randInRange

Details: 	Given a range and a seed value, this function will return a pseudo-random 
		number in the given range. This will be used for the random snake spawning
  		during enemy waves.

Sample Call:
*********************************************************************************************/

unsigned int randInRange(unsigned long *seed, unsigned int min, unsigned int max) {
    const unsigned long a = 1664525;
    const unsigned long c = 1013904223;
    const unsigned long m = 4294967295; /* 2^32-1 */
	unsigned int scaled; 

    *seed = (a * (*seed) + c) % m; /* Update the seed value */

    /* Scale the generated value to fit within the range [min, max] */

    scaled = (unsigned int)((double)(*seed) / (double)m * (max - min + 1) + min);
    return scaled;
}

/*******************************************************************************************
Function Name: 	snake_spawn

Details: 	This function uses the randInRange function to spawn new snake enemies in the
		play area. A new instance of snake is created and slotted into the active_snakes 
  		struct array.

Sample Call:	spawn_snakes((UINT32 *) base, active_snakes, spawn_x, spawn_y, &snakes_fill, (UINT32 *)&seed);
*********************************************************************************************/

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


