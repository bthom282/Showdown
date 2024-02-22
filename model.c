/******************************************************************************************
Names: Adam Cole, Brooklyn Thomson

Purpose: Implements functions for manipulating objects according to their specified 
	 behaviours.

*******************************************************************************************/
#include "model.h"

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
				delete_bullet(active_bullets[i], bullets_fill, i);
			}
		}
	}
}

/*******************************************************************************************
Function Name: 	move_snakes

Details: 	This function is called every cycle to move any active snakes in the active_
		snakes array. If a particular snake is still in the spawning area, it will first
  		move them into the play area.

Sample Call:	move_snakes(&active_snakes[0], snakes_fill, &cowboy1);

*********************************************************************************************/

void move_snakes(struct Snake active_snakes[], int snakes_fill, const struct Cowboy *cowboy)
{
	int i;
	for (i = 0; i < snakes_fill; i++) {
		/*conditions to exit the spawning areas*/
		if(active_snakes[i].position.x < X_MIN)
			{active_snakes[i].position.x++;}
		else if(active_snakes[i].position.x > X_MAX) 
			{active_snakes[i].position.x--;}
		else if(active_snakes[i].position.y < Y_MIN)
			{active_snakes[i].position.y++;}
		else if(active_snakes[i].position.y > Y_MAX)
			{active_snakes[i].position.y--;}
		/*conditions for snake movement once in play*/
		else {
			if (active_snakes[i].position.x < cowboy->position.x)
                		{ active_snakes[i].position.x++; }
            else if (active_snakes[i].position.x > cowboy->position.x)
                		{ active_snakes[i].position.x--; }
            
           	if (active_snakes[i].position.y < cowboy->position.y)
                		{ active_snakes[i].position.y++; }
            else if (active_snakes[i].position.y > cowboy->position.y)
                		{ active_snakes[i].position.y--; }
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
		(cowboy->position.x) += cowboy->x_dir*cowboy->speed;
		(cowboy->position.y) += cowboy->y_dir*cowboy->speed;
		
		/*conditions keeping the cowboy in the play area*/
		if ((cowboy->position.x) > X_MAX)
			{cowboy->position.x = X_MAX;}
		if ((cowboy->position.x) < X_MIN)
			{cowboy->position.x = X_MIN;}
		if ((cowboy->position.y) > Y_MAX)
			{cowboy->position.y = Y_MAX;}
		if ((cowboy->position.y) < Y_MIN)
			{cowboy->position.y = Y_MIN;}
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
	cowboy->lives.lives_left--;
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

/*******************************************************************************************
Function Name: 	init_Cowboy

Details: 	This function initializes the Cowboy struct to it's default starting values.

Sample Call:	cowboy1 = init_Cowboy();

*********************************************************************************************/

struct Cowboy init_Cowboy() {
    	struct Cowboy cowboy; 

    	cowboy.position.x = 424;
    	cowboy.position.y = 184;
    	cowboy.size.height = 32;
    	cowboy.size.width = 32;
    	cowboy.y_dir = 0;
    	cowboy.x_dir = 0;
    	cowboy.speed = 2;
    	cowboy.isMoving = FALSE;
    	cowboy.isFiring = FALSE;
    	cowboy.yFireDir = 0;
    	cowboy.xFireDir = 0;
    	cowboy.state = 0;
	cowboy.scoreboard.score = 0;
    	cowboy.scoreboard.position.x = 80;
    	cowboy.scoreboard.position.y = 300;
	cowboy.lives.lives_left = 3;
    	cowboy.lives.position.x = 80;
    	cowboy.lives.position.y = 320;
	cowboy.boundingBox.top = cowboy.position.y;
    	cowboy.boundingBox.bottom = cowboy.position.y + cowboy.size.height;
    	cowboy.boundingBox.left = cowboy.position.x;
    	cowboy.boundingBox.right = cowboy.position.x + cowboy.size.width;

	return cowboy;
}

/*******************************************************************************************
Function Name: 	init_Snake

Details: 	This function initializes the Snake struct to it's default spawning values.

Sample Call:	cowboy1 = init_Snake(spawn_x, spawn_y);

*********************************************************************************************/

struct Snake init_Snake(int x, int y); {
	struct Snake snake;
	
	snake.position.x = int x;   
	snake.position.y = int y; 	
	snake.size.height = 32;
	snake.size.width = 32;
	snake.y_dir = 0;    		
	snake.x_dir = 0;
	snake.state = 0;
	snake.boundingBox.top = snake.position.y;
    	snake.boundingBox.bottom = snake.position.y + snake.size.height;
    	snake.boundingBox.left = snake.position.x;
    	snake.boundingBox.right = snake.position.x + snake.size.width;
	
	return snake;
}

/*******************************************************************************************
Function Name: 	init_Bullet

Details: 	This function initializes a bullet in the active_bullets array, set values
		as enter in the parameters.

Sample Call: 	init_bullet(active_bullets, &bullets_fill, 360, 170, 1, 0, 3);

*********************************************************************************************/

struct Bullet init_Bullet(int *bullets_fill, int x_pos, int y_pos, int x_dir, int y_dir) {
    
       	bullet.position.x = x_pos;
        bullet.position.y = y_pos;
        bullet.x_dir = x_dir;
        bullet.y_dir = y_dir;
        bullet.speed = BULLET_SPEED;
    }
}
