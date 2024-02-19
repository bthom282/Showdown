/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: Implements functions for manipulating objects according to their specified 
	 behaviours.

*******************************************************************************************/
#include "model.h"

/*******************************************************************************************
Function Name: 	init_bullet

Details: 	This function initializes a bullet in the active_bullets array, set values
		as enter in the parameters.

Sample Call: 	init_bullet(active_bullets, &bullets_fill, 360, 170, 1, 0, 3);

*********************************************************************************************/

void init_bullet(struct Bullet active_bullets[], int *bullets_fill, int initial_x, int initial_y, int initial_x_dir, int initial_y_dir, int initial_speed) {
    
    if (*bullets_fill < MAX_BULLETS) {
        active_bullets[*bullets_fill].position.x = initial_x;
        active_bullets[*bullets_fill].position.y = initial_y;
        active_bullets[*bullets_fill].x_dir = initial_x_dir;
        active_bullets[*bullets_fill].y_dir = initial_y_dir;
        active_bullets[*bullets_fill].speed = initial_speed;

        (*bullets_fill)++;
    } else {
        printf("Error: No space to add a new bullet!\n");
    }
}

/*******************************************************************************************
Function Name: 	move_bullets

Details: 	This function is called every cycle to move any active bullets int the active_
		bullets array at their constant speed in the direction they were fired. After 
  		the new position is calculated, it checks to see if the bullet is out of bounds. 
    		If out of bounds, bullet is deleted from the array by calling the delete_bullet
      		function.

Sample Call: 	move_bullet(active_bullets, bullets_fill);

*********************************************************************************************/

void move_bullets(struct Bullet *active_bullets[], int *bullets_fill)
{
	int i;
	for (i = 0; i < (*bullets_fill); i++) {
		if (active_bullets[i] != NULL) {
			active_bullets[i]->position.x += active_bullets[i]->speed * active_bullets[i]->x_dir;
			active_bullets[i]->position.y += active_bullets[i]->speed * active_bullets[i]->y_dir;

			if (active_bullets[i]->position.y<=0||active_bullets[i]->position.y>=380||
				active_bullets[i]->position.x<=256||active_bullets[i]->position.x>=632) {
				delete_bullet(active_bullets[i], i);
			}
		}
	}
}

/*******************************************************************************************
Function Name: 	move_snakes

Details: 	This function is called every cycle to move any active snakes in the active_
		snakes array. If a particular snake is still in the spawning area, it will first
  		move them into the play area.

Sample Call:	move_snake(active_snakes, &snakes_fill, &cowboy1);

*********************************************************************************************/

void move_snakes(struct Snake *active_snakes[], int *snakes_fill, struct Cowboy *cowboy)
{
	int i;
	for (i = 0; i < (*snakes_fill); i++) {
		/*conditions to exit the spawning areas*/
		if(active_snakes[i]->position.x < X_MIN)
			{active_snakes[i]->position.x++;}
		else if(active_snakes[i]->position.x > X_MAX) 
			{active_snakes[i]->position.x--;}
		else if(active_snakes[i]->position.y < Y_MIN)
			{active_snakes[i]->position.y++;}
		else if(active_snakes[i]->position.y > Y_MAX)
			{active_snakes[i]->position.y--;}
		/*conditions for snake movement once in play*/
		else {
			if (active_snakes[i]->position.x < cowboy->position.x)
                		{ active_snakes[i]->position.x++; }
            		else if (active_snakes[i]->position.x > cowboy->position.x)
                		{ active_snakes[i]->position.x--; }
            
           		if (active_snakes[i]->position.y < cowboy->position.y)
                		{ active_snakes[i]->position.y++; }
            		else if (active_snakes[i]->position.y > cowboy->position.y)
                		{ active_snakes[i]->position.y--; }
		}
	}		
}

/*******************************************************************************************
Function Name: 	move_cowboy

Details: 	This function is called every cycle to check is the cowboy isMoving, the move
		them the appropriate in the correct direction based on direction and speed. It
  		also checks the play boundaries and won't allow them to exit the play area.

Sample Call:	move_cowboy(cowboy1);

*********************************************************************************************/

void move_cowboy(struct Cowboy *cowboy)
{
	if ((cowboy->isMoving) == TRUE) {
		(cowboy->position->x) += (cowboy->x_dir)*(cowboy->speed);
		(cowboy->position->y) += (cowboy->y_dir)*(cowboy->speed);
		/*conditions keeping the cowboy in the play area*/
		if ((cowboy->position->x) > X_MAX)
			{cowboy->position->x = X_MAX;}
		if ((cowboy->position->x) < X_MIN)
			{cowboy->position->x = X_MIN;}
		if ((cowboy->position->y) > Y_MAX)
			{cowboy->position->y = Y_MAX;}
		if ((cowboy->position->y) < Y_MIN)
			{cowboy->position->y = Y_MIN;}
	}
}

/*******************************************************************************************
Function Name: 	increase_score

Details: 	This function is called every time a snake dies through the snake_death
		function. It increases the score value inside the scorebaord struct.

Sample Call:	increase_score(cowboy1.scoreboard, 100);

*********************************************************************************************/

void increase_score(struct Scoreboard *scoreboard,int value) {
	scoreboard->score += value;
	scoreboard->digit[2] = (scoreboard->score%1000)/100;
	scoreboard->digit[3] = (scoreboard->score%10000)/1000;
	scoreboard->digit[4] = (scoreboard->score/10000);
}

/*******************************************************************************************
Function Name: 	wave_bonus

Details: 	This function is called every time a wave is successfully completed to give
		the player's score a bonus.

Sample Call:	wave_bonus(cowboy1.scoreboard);

*********************************************************************************************/

void wave_bonus(struct Scoreboard *scoreboard) {
	increase_score(scoreboard, 1000);
}

/*******************************************************************************************
Function Name: 	decrement_lives

Details: 	This function is called when the player dies to update the lives shown on the 
		side panel display.

Sample Call:	decrement_lives (cowboy1);

*********************************************************************************************/
	
void decrement_lives (struct Cowboy *cowboy) {
	cowboy->Lives.lives_left--;
}

/*******************************************************************************************
Function Name: 	respawn

Details: 	This function is passes in the player instance so it can resets the cowboy's 
		position to the game start location (x = 424, y = 184), then reprints the 
  		cowboy bitmap.

Sample Call:	respawn(player1);

*********************************************************************************************/

void respawn(struct Cowboy *cowboy) {
	cowboy->position.x = 424;
	cowboy->position.y = 184;
	/* invulnerability frames code here, asking Marc */
}	
