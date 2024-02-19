/*******************************************************************************************
Names:    Adam Cole, Brooklyn Thomson

Purpose:  Implements event-handling functions for each of the specified asynchronous,
          synchronous and condition-based events.
*******************************************************************************************/
#include "events.h"

Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
int bullets_fill = 0;
int snakes_fill = 0;
UINT32 seed = 12345;
/*arrays of spawn positions for snake enemies*/
const int spawn_x[16] = {384,416,448,480,256,256,256,256,608,608,608,608,384,416,448,480};
const int spawn_y[16] = {0,0,0,0,128,160,192,224,128,160,192,224,352,352,352,352};

/*******************************************************************************************
Function Name: 	checkCollision

Details: 	This function will compare bounding boxs of object to see if there is a collision.

Sample Call:	
*********************************************************************************************/

int checkCollision(struct BoundingBox box1, struct BoundingBox box2) {
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
		(*bullets_fill)++;
	}
}

/*******************************************************************************************
Function Name: 	delete_bullet

Details: 	This function is called every time a bullet leaves the play area by going out 
		of bounds or by striking an enemy.

Sample Call: 	delete_bullet(active_bullets[i], i);
*********************************************************************************************/

void delete_bullet (struct Bullet *active_bullets[], int *bullet_fill, int index) {
	if (index >= 0 && index < *bullet_fill) {
        	active_bullets[index] = active_bullets[*bullet_fill - 1];
        	(*bullet_fill)--;
   	 }
}

/*******************************************************************************************
Function Name: 	rand_in_range

Details: 	Given a range and a seed value, this function will return a pseudo-random 
		number in the given range. This will be used for the random snake spawning
  		during enemy waves.

Sample Call:	spawn_loc = rand_in_range(seed, 0, 15);
*********************************************************************************************/

unsigned int rand_in_range(unsigned long *seed, unsigned int min, unsigned int max) {
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

Details: 	This function uses the rand_in_range function to "spawn" a new snake struct is 
		created and slotted into the active_snakes struct array.

Sample Call:	spawn_snakes(active_snakes, spawn_x, spawn_y, &snakes_fill, (UINT32 *)&seed);
*********************************************************************************************/

void spawn_snakes(struct Snake *active_snakes[], int spawn_x[], int spawn_y[], int *snakes_fill, UINT32 *seed) {
	int spawn_loc;

	spawn_loc = rand_in_range(seed, 0, 15);
	active_snakes[*snakes_fill]->position.x = spawn_x[spawn_loc];
	active_snakes[*snakes_fill]->position.y = spawn_y[spawn_loc];

	(*snakes_fill)++;
}

/*******************************************************************************************
Function Name: 	snake_death

Details: 	This function is called every time a snake is killed by a bullet and is removed
		from play.

Sample Call:	snake_death(active_snakes[i], i, snakes_fill, &cowboy1.scoreboard);
*********************************************************************************************/

void snake_death(struct Snake *active_snakes[], int index, int snakes_fill, struct Scoreboard *scoreboard) {
    /*possible call to snake death animation here*/
    	if (index >= 0 && index < snakes_fill) {
       		active_snakes[index] = active_snakes[snakes_fill - 1];
        	snakes_fill--;
    	}
	increase_score(scoreboard,100);
}

/*******************************************************************************************
Function Name: 	cowboy_death

Details: 	This function updates the lives count, called the update lives function, then
		checks if there are lives remaining. If none, trigger game over sequence by 
  		calling the game_over function. If lives remaining, triggers the respawn
    		function.

Sample Call:	cowboy_death (*cowboy->lives_count);	

*********************************************************************************************/

void cowboy_death (struct Cowboy *cowboy) {
	/* possible death animation here */
	decrement_lives(cowboy);
	if (cowboy->lives == 0) {
		/*gameover();*/
		respawn(); /*temporary*/
	}
	else {
		respawn();
	}

/*******************************************************************************************
Function Name: 	game_over

Details: 	This function is triggered when the player has run out of lives. It will 
		print "game over" many times, then indicate the final score somehow, fill
  		the screen black, then print a message promting the user to either continue
    		or quit. 	

Sample Call:

*********************************************************************************************/
/*
void game_over((UINT8 *)base, int *isPlaying) {
	int i,j;
	for (i = 0; i < 284; i += 12) {
		for (j = 0; j < 200; j += 80) {
			print_message((UINT8 *) base, gameover, j, i);
		}
	}*/
	
	/* flash score a few times (clear, print, 5-times)*/
	
	/* clear screen */
	
	/* wait a few seconds */
	
	/* print message based on score */
	
	/* Ask player if they want to continue */
	
/*	print_message((UINT8 *) base, continue, [x], [y]);
	if (y pressed) {
		game_start();
	}
	if (n pressed) {
		game_quit(isPlaying)
	}
}
*/
/*******************************************************************************************
Function Name: 	game_quit

Details: 	This function sets the isPlaying bool to false to exit the game loop. 	

Sample Call:	game_quit(isPlaying)

*********************************************************************************************/
/*
void game_quit(int *isPlaying)
{
	isPlaying = FALSE;
}
*/
