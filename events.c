/*******************************************************************************************
Names:    Adam Cole, Brooklyn Thomson

Purpose:  Implements event-handling functions for each of the specified asynchronous,
          synchronous and condition-based events.
*******************************************************************************************/
#include "events.h"

/*******************************************************************************************
Function Name: 	checkCollision

Details: 	This function will compare bounding boxs of object to see if there is a collision.
			It's purposedly coded to short circuit the comparisons for quickness which is why
			there are multiple return statements.

Sample Call:	
*********************************************************************************************/

int checkCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {

	if ((x1 + width1) < x2 || x1 > (x2 + width2))
	{return FALSE;}

	if((y1 + height1) < y2 || y1 > (y2 + height2))
	{return FALSE;}

	return TRUE;
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

void shooting(struct Cowboy *cowboy, struct Bullet *active_bullets, int *bullets_fill) {
	if (cowboy->isFiring && (cowboy->yFireDir != 0 || cowboy->xFireDir != 0)) {
		int x_shift, y_shift;
		play_pop();
		
		if (cowboy->yFireDir == -1 && cowboy->xFireDir == -1) {
			x_shift = -2;
			y_shift = -2;
		}
		else if (cowboy->yFireDir == -1 && cowboy->xFireDir == 0) {
			x_shift = 12;
			y_shift = -6;
		}
		else if (cowboy->yFireDir == -1 && cowboy->xFireDir == 1) {
			x_shift = 26;
			y_shift = -2;
		}
		else if (cowboy->yFireDir == 0 && cowboy->xFireDir == 1) {
			x_shift = 26;
			y_shift = 12;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == 1) {
			x_shift = 26;
			y_shift = 26;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == 0) {
			x_shift = 12;
			y_shift = 30;
		}
		else if (cowboy->yFireDir == 1 && cowboy->xFireDir == -1) {
			x_shift = -2;
			y_shift = 26;
		}
		else if (cowboy->yFireDir == 0 && cowboy->xFireDir == -1) {
			x_shift = -2;
			y_shift = 12;
		}
		active_bullets[*bullets_fill] = init_Bullet(cowboy->position.x + x_shift, 
		cowboy->position.y + y_shift, cowboy->xFireDir, cowboy->yFireDir);
		(*bullets_fill)++;
	}
}

/*******************************************************************************************
Function Name: 	spawn_snakes

Details: 	This function uses the rand_in_range function to "spawn" a new snake struct is 
		created and slotted into the active_snakes struct array.

Sample Call:	spawn_snakes(active_snakes, &snakes_fill, &seed);
*********************************************************************************************/

void spawn_snakes(struct Snake active_snakes[], int *snakes_fill, UINT32 *seed) {
    int spawn_x[16] = {384,416,448,479,259,259,259,259,605,605,605,605,384,416,448,479};
    int spawn_y[16] = {3,3,3,3,128,160,192,224,128,160,192,224,349,349,349,349};
    int y_dir;
    int x_dir;
    int state;
    unsigned int spawn_loc;

    if (*snakes_fill >= MAX_SNAKES) {
        return;
    }

    spawn_loc = rand_in_range((UINT32 *)seed, 0, 15);
	
    if (spawn_loc < 4) {
        y_dir = 1;
        x_dir = 0;
        state = 0;
    } else if (spawn_loc < 8) {
        y_dir = 0;
        x_dir = 1;
        state = 2;
    } else if (spawn_loc < 12) {
        y_dir = 0;
        x_dir = -1;
        state = 1;
    } else {
        y_dir = -1;
        x_dir = 0;
        state = 3;
    }
    active_snakes[*snakes_fill] = init_Snake(spawn_x[spawn_loc], spawn_y[spawn_loc], y_dir, x_dir, state);
    (*snakes_fill)++;
}

/*******************************************************************************************
Function Name: 	delete_bullet

Details: 	This function is called every time a bullet leaves the play area by going out 
		of bounds or by striking an enemy.

Sample Call: 	delete_bullet(&active_bullets[0], bullets_fill, i);
*********************************************************************************************/

void delete_bullet (struct Bullet *active_bullets[], int *bullet_fill, int index) {
	if (index >= 0 && index < *bullet_fill) {
        	active_bullets[index] = active_bullets[*bullet_fill - 1];
        	(*bullet_fill)--;
   	 }
}

/*******************************************************************************************
Function Name: 	snake_death

Details: 	This function is called every time a snake is killed by a bullet and is removed
		from play.

Sample Call:	snake_death(active_snakes[i], i, snakes_fill, &cowboy1.scoreboard);
*********************************************************************************************/

void snake_death(struct Snake active_snakes[], int index, int *snakes_fill) {
    /*possible call to snake death animation here*/
    if (index >= 0 && index < *snakes_fill) {
       	active_snakes[index] = active_snakes[*snakes_fill - 1];
        (*snakes_fill)--;
    }
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

	if (cowboy->lives.lives_left == 0) {
		/*gameover();*/
		respawn(cowboy); /*temporary*/
	}
	else {
		respawn(cowboy);
	}
}

/*******************************************************************************************
Function Name: 	wave_bonus

Details: 	This function is called every time a wave is successfully completed to give
		the player's score a bonus.

Sample Call:	wave_bonus(cowboy1.scoreboard);

*********************************************************************************************/

void wave_bonus(UINT8 *base, int *game_timer, struct Scoreboard *scoreboard) {
	
	int count = 6;	
	increase_score(scoreboard, 1000);
	while(count != 0)
		{
			if(*game_timer%35 == 0)
			{
				print_message((UINT8 *) base, (UINT8 *)"WAVE BONUS! ", 104, 280);
				/*Cowperson special here*/
				play_chime();
				count--;
			}
		}
	scoreboard->isRendered = FALSE;
}

/*******************************************************************************************
Function Name: 	gameover

Details: 	This function is triggered when the player has run out of lives. It will 
			print "game over" many times, then indicate the final score somehow, fill
			the screen black, then print a message promting the user to either continue
    		or quit. 	

Sample Call:

*********************************************************************************************/

void gameover(UINT32 *base, char *ch) {
	int i, j;
	int count = 0;
	fill_rec((UINT16 *)base, 0, 0, 250, 15);
	while(count != 9)
	{
		for (i = 0; i < 276; i += 12) {
				for (j = 0; j < 200; j += 80) {
					print_message((UINT8 *) base, (UINT8 *)"GAME OVER! ", j, i);
				}
			}
		count++;
	}	
	*ch = 'q';
	return;
}
