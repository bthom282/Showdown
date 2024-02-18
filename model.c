/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: Implements functions for manipulating objects according to their specified 
	 behaviours.

*******************************************************************************************/
#include "model.h"

/*******************************************************************************************
Function Name: 	move_bullet

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
		active_bullets[i]->position.x += active_bullets[i]->speed*active_bullets[i]->x_dir;
  		active_bullets[i]->position.y += active_bullets[i]->speed*active_bullets[i]->y_dir;

		if (active_bullets[i]->position.y<=0||active_bullets[i]->position.y>=380||
		    active_bullets[i]->position.x<=256||active_bullets[i]->position.x>=632) {
			delete_bullet(active_bullets[i], i);
		}
	}
}

/*******************************************************************************************
Function Name: 	move_snake

Details: 	This function is called every cycle to move any active snakes in the active_
		snakes array. If a particular snake is still in the spawning area, it will first
  		move them into the play area.

Sample Call:	move_snake(active_snakes, snakes_fill, cowboy);

*********************************************************************************************/

void move_snake(struct Snake *active_snakes[], int *snakes_fill, struct Cowboy *cowboy)
{
	int x_distance;
	int y_distance;
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
			x_distance = active_snakes[i]->position.x - cowboy->position.x;
		
			if (x_distance > 0)
				{active_snakes[i]->position.x--;}
			if (x_distance < 0)
				{active_snakes[i]->position.x++;}
		
			y_distance = active_snakes[i]->position.y - cowboy->position.y;
		
			if (y_distance > 0)
				{active_snakes[i]->position.y--;}
			if (y_distance < 0)
				{active_snakes[i]->position.y++;}
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
	scoreboard->digit3 = (scoreboard->score%1000)/100;
	scoreboard->digit4 = (scoreboard->score%10000)/1000;
	scoreboard->digit5 = (scoreboard->score/10000;
}

/*******************************************************************************************
Function Name: 	wave_bonus

Details: 	This function is called every time a wave is successfully completed to give
		the player's score a bonus.

Sample Call:	wave_bonus(cowboy1.scoreboard);

*********************************************************************************************/

void wave_bonus(struct Scoreboard scoreboard) {
	increase_score(scoreboard, 1000);
}

/*******************************************************************************************
Function Name: 	update_lives

Details: 	This function is called when the player dies to update the lives shown on the 
		side panel display.

Sample Call:	lives_count--;
		update_lives ((UINT16 *) base, p1_lives_count, 320, cowboy_bitmap_16);

*********************************************************************************************/
	
void update_lives (UINT8 *base, int lives_count, int y, const UINT16 *bitmap16) {
	int i, x;
	x = 80;
	for (i = 0; i < (lives_count+1); i++) {
		clear_bitmap_16((UINT16 *) base, x, y, bitmap16, BITMAP_HEIGHT);
		x += 16;
	}
	x = 80;
	for (i = 0; i < lives_count; i++) {
		plot_bitmap_16((UINT16 *) base, x, y, bitmap16, BITMAP_HEIGHT);
		x += 16;
	}
}

/*******************************************************************************************
Function Name: 	respawn

Details: 	This function is passes in the player instance so it can resets the cowboy's 
		position to the game start location (x = 424, y = 184), then reprints the 
  		cowboy bitmap.

Sample Call:	respawn(player1);

*********************************************************************************************/

void respawn(Cowboy *cowboy) {
	player->x = 424;
	player->y = 184;
	/* invulnerability frames code here, asking Marc */
}	
