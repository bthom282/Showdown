/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: Implements functions for manipulating objects according to their specified 
	 behaviours.

*******************************************************************************************/
#include "model.h"

Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
int bullets_fill = 0;
int snakes_fill = 0;
UINT32 seed = 12345;
/*arrays of spawn positions for snake enemies*/
const int spawn_x[16] = {384,416,448,480,256,256,256,256,608,608,608,608,384,416,448,480};
const int spawn_y[16] = {0,0,0,0,128,160,192,224,128,160,192,224,352,352,352,352};

/*******************************************************************************************
Function Name: 	move_bullet

Details: 	This function is called every cycle to move any active bullets at their constant
		speed in the direction they were fired. After the movement is calculated, if checks
  		to see if the bullet is out of bounds, and therefore not replotted, or if there is a 
    		collision with a snake. 

Sample Call: 
		int i;
		for(i = 0; i < bullets_fill; i++) {
			move_bullet(active_bullets[i]);
 		}
*********************************************************************************************/

void move_bullet(struct Bullet *bullet)
{
	clear_bitmap_8((UINT8 *) base, bullet->position->x, bullet->position->y, bullet_bitmap, BITMAP_8_HEIGHT);
	bullet->position.x += bullet->x_dir*bullet->speed;
  	bullet->position.y += bullet->y_dir*bullet->speed;
	if ((380>=bullet->position.y>=0)||(256>=bullet->position.x>=632)) {
		plot_bitmap_8((UINT8 *) base, bullet->position.x, bullet->position.y, bullet_bitmap, BITMAP_8_HEIGHT);
	}
	else {
		delete_bullet(bullet);
	}
	/*[colission detection here]*/
	int i;
	for(i = 0; i < bullets_fill; i++) {
		if(checkCollision(Bullet boundingBox, active_snakes[i] boundingBox)) {
			snake_death(active_snake[i], i);
		}
	}
}

/*******************************************************************************************
Function Name: 	delete_bullet

Details: 	This function is called every time a bullet leaves the play area by going out 
		of bounds or by striking an enemy.

Sample Call: 	delete_bullet(active_bullets[i]);
*********************************************************************************************/

void delete_bullet (struct Bullet *bullet, int index) {
	if (index >= 0 && index < bullet_fill) {
        	active_bullets[index] = active_bullets[bullet_fill - 1];
        	bullet_fill--;
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
Function Name: 	snake_death

Details: 	This function is called every time a snake is killed by a bullet and is removed
		from play.

Sample Call:	snake_death(active_snakes[i]);
*********************************************************************************************/

void snake_death(struct Snake *snake, int index) {
    /*possible snake death animation here*/
    if (index >= 0 && index < snakes_fill) {
        active_snakes[index] = active_snakes[snakes_fill - 1];
        snakes_fill--;
    }
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
Function Name: 	cowboy_death

Details: 	This function updates the lives count, called the update lives function, then
		checks if there are lives remaining. If none, trigger game over sequence by 
  		calling the game_over function. If lives remaining, triggers the respawn
    		function.

Sample Call:	cowboy_death (*cowboy->lives_count);	

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
	player->y = 184;
	/* invulnerability frames code here, asking Marc */
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
/*******************************************************************************************
Function Name: 	print_message

Details: 	This function takes in a character array and prints it to the screen starting 
		at the designated area. It advances automatically to print the full message,
  		while using the provided font.c file for each character's bitmap.

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
Function Name: 	spawn_snakes

Details: 	This function

Sample Call:	spawn_snakes(Snake *active_snakes[], int spawn_x[], int spawn_y[], &snakes_fill, &seed) 
*********************************************************************************************/
void spawn_snakes(Snake *active_snakes[], int spawn_x[], int spawn_y[], int *snakes_fill, int *seed) {
	int spawn_loc;
	active_snakes[fill_level] = struct Snake snake;
	snakes_fill++;
	spawn_loc = randInRange(&seed, 0, 15);
	active_snakes[spawn_loc].position.x = spawn_x[spawn_loc];
	active_snakes[spawn_loc].position.y = spawn_y[spawn_loc];
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
}
	
	
