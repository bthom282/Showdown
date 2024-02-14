/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: 

*******************************************************************************************/
#include "model.h"

/*******************************************************************************************
Function Name: 	move_bullet

Details: 		

Sample Call:

*********************************************************************************************/

void move_bullet(Bullet *bullet)
{
  bullet->x += bullet->delta_x;
  bullet->y += bullet->delta_y;
	
  /*check for collision.*/
  checkcollision(Bullet bounding box, Snake bounding box);
}

/*******************************************************************************************
Function Name: 	move_snake

Details: 	This function 	

Sample Call:

*********************************************************************************************/

/*Need to check with Marc if we need to pass in bitmaps and bounding boxes for the move_snake function*/

void move_snake(Snake *snake)
{
	int x_distance;
	int y_distance;
	clear_bitmap_32((UINT32 *) base, snake->x, snake->y, snake_bitmap_32, BITMAP_32_HEIGHT);
	
	/*conditions to exit the spawning areas*/
	if(snake->x < X_MIN) {
		snake->x++;
		}
	else if(snake->x > X_MAX) {
		snake->x--;
		}
	else if(snake->y < Y_MIN) {
		snake->y++;
	else if(snake->y > Y_MAX) {
		snake->y--;
		}
	/*conditions for snake movement once in play*/
	else {
		x_distance = snake->x - cowbow->x
		
		if (x_distance > 0)
			{snake->x--;}
		if (x_distance < 0)
			{snake->x++}
		
		y_distance = snake->y - cowbow->y
		
		if (y_distance > 0)
			{snake->y--;}
		if (y_distance < 0)
			{snake->y++}
		
	/*replot snake bitmap at new coordinates*/
	plot_bitmap_32((UINT32 *) base, snake->x, snake->y, snake_bitmap_32, BITMAP_32_HEIGHT);
	
	/*check for collision.*/
	checkcollision(Snake bounding box, Cowboy bounding box);
		
}

/*******************************************************************************************
Function Name: 	move_cowboy

Details: 	This function 	

Sample Call:

*********************************************************************************************/

void move_cowboy(Cowboy *cowboy)
{

}

/*******************************************************************************************
Function Name: 	cowboy_death

Details: 	This function updates the lives count, called the update lives function, then
		checks if there are lives remaining. If none, trigger game over sequence by 
  		calling the game_over function. If lives remaining, triggers the respawn
    		function.

Sample Call:

*********************************************************************************************/

void cowboy_death (int *lives_count) {
	/* possible death animation here */
	if (lives_count == 1) {
		lives_count--;
		update_lives(lives);
		gameover();
	}
	else {
		lives_count--;
		update_lives(lives);
		respawn();
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
	player->y = 184
	plot_bitmap_32((UINT32 *) base, 424, 184, cowboy_bitmap_32, BITMAP_32_HEIGHT;
	/* invulnerability frames code here, asking Marc */

/*******************************************************************************************
Function Name: 	game_over

Details: 	This function is triggered when the player has run out of lives. It will 
		print "game over" many times, then indicate the final score somehow, fill
  		the screen black, then print a message promting the user to either continue
    		or quit. 	

Sample Call:

*********************************************************************************************/

void game_over((UINT8 *)base, bool isPlaying) {
	int i,j;
	for (i = 0; i < 284; i += 12) {
		for (j = 0; j < 200; j += 80) {
			print_message((UINT8 *) base, gameover, j, i);
		}
	}
	
	/* flash score a few times (clear, print, 5-times)*/
	
	/* clear screen */
	
	/* wait a few seconds */
	
	/* print message based on score */
	
	/* Ask player if they want to continue */
	
	print_message((UINT8 *) base, continue, [x], [y]);
	if (y pressed) {
		game_start();
	}
	if (n pressed) {
		game_quit(isPlaying)
	}
}

/*******************************************************************************************
Function Name: 	game_quit

Details: 	This function sets the isPlaying bool to false to exit the game loop. 	

Sample Call:

*********************************************************************************************/

void game_quit(bool *isPlaying)
{
	isPlaying = FALSE;
}

/*******************************************************************************************
Function Name: 	print_message

Details: 	 	

Sample Call:

*********************************************************************************************/

void print_message(UINT8 *base, char message[], int x_pos, int y_pos) {
	int i = 0;
	if (x_pos >= 0 && x_pos < SCREEN_WIDTH && y_pos >= 0 && y_pos < SCREEN_HEIGHT) {
		while (message[i] != '\0') {
			plot_char((UINT8 *) base, x_pos, y_pos, message[i]);
			x_pos += 8;
			i++;
		}
	}
}
