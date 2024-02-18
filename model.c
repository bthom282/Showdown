/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: Implements functions for manipulating objects according to their specified 
	 behaviours.

*******************************************************************************************/
#include "model.h"

/*******************************************************************************************
Function Name: 	move_bullet

Details: 	This function is called every cycle to move any active bullets at their constant
		speed in the direction they were fired. After the movement is calculated, it checks
  		to see if the bullet is out of bounds. If out of bounds, bullet is deleted.

Sample Call: 
		int i;
		for(i = 0; i < bullets_fill; i++) {
			move_bullet(active_bullets[i]);
 		}
*********************************************************************************************/

void move_bullet(struct Bullet *bullet)
{
	bullet->position.x += bullet->x_dir*bullet->speed;
  	bullet->position.y += bullet->y_dir*bullet->speed;

	if (bullet->position.y<=0||bullet->position.y>=380||bullet->position.x<=256||bullet->position.x>=632) {
		delete_bullet(bullet);
	}
}

/*******************************************************************************************
Function Name: 	move_snake

Details: 	This function is called every cycle

Sample Call:	int i;
		for(i = 0; i < snake_fill;i++) {
  			move_snake(active_snakes[i], cowboy);
     		}
*********************************************************************************************/

void move_snake(struct Snake *snake, struct Cowboy *cowboy)
{
	int x_distance;
	int y_distance;
	clear_bitmap_32((UINT32 *) base, snake->position.x, snake->position.y, snake_bitmap_32, BITMAP_32_HEIGHT);
	
	/*conditions to exit the spawning areas*/
	if(snake->position.x < X_MIN)
		{snake->position.x++;}
	else if(snake->position.x > X_MAX) 
		{snake->position.x--;}
	else if(snake->position.y < Y_MIN)
		{snake->position.y++;}
	else if(snake->position.y > Y_MAX)
		{snake->position.y--;}
	/*conditions for snake movement once in play*/
	else {
		x_distance = snake->position.x - cowbow->position.x;
		
		if (x_distance > 0)
			{snake->position.x--;}
		if (x_distance < 0)
			{snake->position.x++;}
		
		y_distance = snake->position.y - cowbow->position.y;
		
		if (y_distance > 0)
			{snake->position.y--;}
		if (y_distance < 0)
			{snake->position.y++;}
	}	
	/*replot snake bitmap at new coordinates*/
	plot_bitmap_32((UINT32 *) base, snake->position.x, snake->position.y, snake_bitmap_32, BITMAP_32_HEIGHT);
	
	/*check for collision.*/
	checkCollision(snake->boundingBox, cowboy->boundingBox);
}

/*******************************************************************************************
Function Name: 	move_cowboy

Details: 	This function is called every cycle to check is the cowboy isMoving, the move
		them the appropriate in the correct direction based on direction and speed. It
  		also checks the play boundaries and won't allow them to exit the play area.

Sample Call:	move_cowboy((UINT32 *)base, &cowboy1, cowboy_bitmap_32);

*********************************************************************************************/

void move_cowboy(UINT32 *base, struct Cowboy *cowboy, const UINT32 *bitmap32)
{
	if ((cowboy->isMoving) == TRUE) {
		Vsync();
		clear_bitmap_32((UINT32 *) base, cowboy->xposition->x, cowboy->position->y, blank, BITMAP_32_HEIGHT);
		(cowboy->position->x) += (cowboy->x_dir)*(cowboy->speed);
		(cowboy->position->y) += (cowboy->y_dir)*(cowboy->speed);
		if ((cowboy->position->x) > X_MAX)
			{cowboy->position->xs = X_MAX;}
		if ((cowboy->position->x) < X_MIN)
			{cowboy->position->x = X_MIN;}
		if ((cowboy->position->y) > Y_MAX)
			{cowboy->position->y = Y_MAX;}
		if ((cowboy->position->y) > X_MIN)
			{cowboy->position->y = X_MIN;}
		plot_bitmap_32((UINT32 *) base, cowboy->position->x, cowboy->position->y, cowboy_bitmap_32, BITMAP_32_HEIGHT);
	}
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
