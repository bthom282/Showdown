/**************************************************************************************
Names:		Adam Cole, Brooklyn Thomson

Purpose:	Links the model with the low-level graphics library, so that it is 
		possible to render an individual, static frame of animation based on 
  		a static snapshot of the world.
**************************************************************************************/
#include "renderer.h"

void render(UINT32 *base, struct Model *model)
{
	
}

/********************************************************************************************
Function Name: 	render_cowboy

Details: 	renders the cowboy using his x and y position from the cowboy struct.

*********************************************************************************************/

void render_cowboy(UINT32 *base, struct Cowboy cowboy, const UINT32 *bitmap)
{
		plot_bitmap_32((UINT32 *) base, cowboy.position.x, 
						cowboy.position.y, 
						cowboy_bitmap[cowboy.state], 
						BITMAP_32_HEIGHT);
		return;
}

/********************************************************************************************
Function Name: 	render_bullets

Details: 	renders all of the active bullets.

*********************************************************************************************/

void render_bullets(UINT8 *base, struct Bullet *active_bullets, const UINT8 *bitmap8, int bullets_fill)
{
	int i;
	for (i = 0; i < bullets_fill; i++) {
		plot_bitmap_8((UINT8 *) base, active_bullets[i].position.x, active_bullets[i].position.y, bitmap8, BITMAP_8_HEIGHT);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_snakes

Details: 	renders all of the active snakes.

*********************************************************************************************/

void render_snakes(UINT32 *base, const struct Snake *active_snakes, int snakes_fill)
{
	int i;
	for (i = 0; i < snakes_fill; i++) {
		plot_bitmap_32((UINT32 *) base, active_snakes[i].position.x, active_snakes[i].position.y, snake_bitmap[active_snakes[i].state], BITMAP_32_HEIGHT);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_side_panel

Details: 	Fills side panel in black.

*********************************************************************************************/

void render_side_panel(UINT16 *base)
{
	UINT16 *loc = (UINT16 *) base;
	int k, j;
	for (k = 0; k < SCREEN_HEIGHT; k++){ 
		for (j = 0; j < 16; j++) {
			*(loc++) = -1;
		}
		loc += 24;
	}
}

/********************************************************************************************
Function Name: 	render_level1

Details: 	renders the cowboy using his x and y position from the cowboy struct.

*********************************************************************************************/

void render_level1(UINT32 *base, const UINT32 *bitmap)
{
	int i;
	for(i = 0; i < 128; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_bitmap, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_bitmap, BITMAP_32_HEIGHT, 0);
	}
	for(i = 256; i < SCREEN_HEIGHT-32; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_bitmap, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_bitmap, BITMAP_32_HEIGHT, 0);
	}
	for(i = 256; i < 384; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_bitmap, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_bitmap, BITMAP_32_HEIGHT, 0);
	}
	for(i = 512; i < 640; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_bitmap, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_bitmap, BITMAP_32_HEIGHT, 0);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_side_text

Details: 	prints the initial text based on number of players.

*********************************************************************************************/
void render_side_text(UINT8 *base, int players) 
{
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 1", 32, 280);
	print_message((UINT8 *)base, (UINT8 *)"SCORE", 32, 300);
	print_message((UINT8 *)base, (UINT8 *)"LIVES", 32, 320);
	
	if (players == 2) {
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 2", 32, 212);
	print_message((UINT8 *)base, (UINT8 *)"SCORE", 32, 232);
	print_message((UINT8 *)base, (UINT8 *)"LIVES", 32, 252);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_score

Details: 	Takes the score from a cowboy struct and prints it to the scoreboard.

*********************************************************************************************/

void render_score(UINT8 *base, struct Scoreboard *scoreboard)
{
	int i, x, y;
	x = scoreboard.position.x;
	y = scoreboard.position.y;
	for (i = 4; i >= 0; i--) {
		plot_char(base, x, y, '0' + scoreboard.digit[i]);
		x += 8;
	}
}

/********************************************************************************************
Function Name: 	render_lives

Details: 	Takes the lives from a cowboy struct and prints them to the side panel.

*********************************************************************************************/

void render_lives(UINT16 *base, struct Lives *lives, const UINT16 *bitmap16)
{
	int i, x;
	x = 80;
	for (i = 0; i < lives.lives_left; i++) {
		plot_bitmap_16((UINT16 *) base, x, lives.position.y, bitmap16, BITMAP_HEIGHT);
		x += 16;
	}
}

void game_start() {

  	char *base = Physbase();
	unsigned long seed = 300;
	UINT16 *loc = (UINT16 *) base;
	int players = 1;
	
	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1;
	cowboy1.position.x = 424; 
	cowboy1.position.y = 184;
    	cowboy1.size.height = 16; 
	cowboy1.size.width = 16;
	cowboy1.x_dir = 0;
	cowboy1.y_dir = 0;
	cowboy1.speed = 2;
	cowboy1.isMoving = FALSE;
	cowboy1.isFiring = FALSE;
	cowboy1.yFireDir = 0;
	cowboy1.xFireDir = 0;
	cowboy1.state = 0;
	cowboy1.scoreboard.score = 0;
	cowboy1.scoreboard.position.x = 80;
	cowboy1.scoreboard.position.y = 232;
	cowboy1.lives.lives_left = 3;
	cowboy1.bitmap = cowboy_bitmap_32[cowboy1.state];

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);

	Cnecin(); /* wait for key press to continue */

	fill_screen((UINT32 *) base, 0); /* clear full screen */

	spawn_snakes(active_snakes, spawn_x, spawn_y, &snakes_fill, (UINT32 *)&seed);
	cowboy1.scoreboard.score = 200;

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	Cnecin(); /* wait for key press to continue */

	fill_screen((UINT32 *) base, 0); /* clear full screen */
	
	cowboy1.position.x = 390; 
	cowboy1.position.y = 140;
	cowboy1.state = 4;
	active_snakes[0].position.x = 370;
	active_snakes[0].position.y = 160;
	active_snakes[0].state = 1;
	spawn_snakes(active_snakes, spawn_x, spawn_y, &snakes_fill, (UINT32 *)&seed);

	cowboy1.scoreboard.score = 400;

	active_bullets[bullets_fill].position.x = 360;
	active_bullets[bullets_fill].position.y = 170;
	active_bullets[bullets_fill].speed = 3;
	active_bullets[bullets_fill].x_dir = 1;
	bullets_fill++;
	cowboy1.position.x = 350; 
	cowboy1.position.y = 100;
	cowboy1.isMoving = TRUE;
	cowboy1.isFiring = TRUE;
	cowboy1.yFireDir = 1;
	cowboy1.xFireDir = -1;
	cowboy1.state = 3;
	shooting((UINT8 *)base, &cowboy1, (UINT8 *)bullet_bitmap, active_bullets, &bullets_fill);

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);

	Cnecin(); /* wait for key press to continue */
	fill_screen((UINT32 *) base, 0); /* clear full screen */

	cowboy1.lives.lives_left = 2;
	cowboy1.position.x = 424; 
	cowboy1.position.y = 184;
	cowboy1.state = 0;

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
}
