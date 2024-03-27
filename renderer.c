/**************************************************************************************
Names:		Adam Cole, Brooklyn Thomson

Purpose:	Links the model with the low-level graphics library, so that it is 
		possible to render an individual, static frame of animation based on 
  		a static snapshot of the world.
**************************************************************************************/
#include "renderer.h"

/********************************************************************************************
Function Name: 	render

Details: 	renders a whole frame based on the current state of the model.

*********************************************************************************************/

void render(UINT32 *base, struct Model *model)
{ 
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, model->players);
	render_score((UINT8 *) base, &model->cowboy.scoreboard);
	model->cowboy.scoreboard.isRendered = TRUE;
	render_lives((UINT16 *) base, &model->cowboy.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, model->active_snakes, model->snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, model->active_bullets, bullet_bitmap, model->bullets_fill);
}

/********************************************************************************************
Function Name: 	update_render

Details: 	updates the render of any moving object

*********************************************************************************************/

void update_render(UINT32 *base, struct Model *model)
{
	/*if(model->cowboy.scoreboard.isRendered == FALSE)*/
	render_score((UINT8 *) base, &model->cowboy.scoreboard);
	render_lives((UINT16 *) base, &model->cowboy.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, model->active_snakes, model->snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, model->active_bullets, bullet_bitmap, model->bullets_fill);
}

/********************************************************************************************
Function Name: 	render_cowboy

Details: 	renders the cowboy using his x and y position from the cowboy struct.

*********************************************************************************************/

void render_cowboy(UINT32 *base, struct Cowboy cowboy, const UINT32 bitmap[][BITMAP_32_HEIGHT])
{
	plot_bitmap_32((UINT32 *) base, 
					cowboy.position.x, 
					cowboy.position.y, 
					bitmap[cowboy.state], 
					BITMAP_32_HEIGHT);
}

/********************************************************************************************
Function Name: 	render_bullets

Details: 	renders all of the active bullets.

*********************************************************************************************/

void render_bullets(UINT8 *base, struct Bullet *active_bullets, const UINT8 *bitmap, int bullets_fill)
{
	int i;
	for (i = 0; i < bullets_fill; i++) {
		plot_bitmap_8((UINT8 *) base, active_bullets[i].position.x, active_bullets[i].position.y, bitmap, BITMAP_8_HEIGHT);
	}
}

/********************************************************************************************
Function Name: 	render_snakes

Details: 	renders all of the active snakes.

*********************************************************************************************/

void render_snakes(UINT32 *base, const struct Snake active_snakes[], int snakes_fill, const UINT32 bitmap[][BITMAP_32_HEIGHT])
{
	int i;
	for (i = 0; i < snakes_fill; i++) {
		plot_bitmap_32((UINT32 *) base, active_snakes[i].position.x, active_snakes[i].position.y, 
					bitmap[active_snakes[i].state], BITMAP_32_HEIGHT);
	}
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

void render_level1(UINT32 *base, const UINT32 *cactus_bitmap)
{
	int i;
	for(i = 0; i < 128; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_bitmap, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_bitmap, BITMAP_32_HEIGHT);
	}
	for(i = 256; i < SCREEN_HEIGHT-32; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_bitmap, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_bitmap, BITMAP_32_HEIGHT);
	}
	for(i = 256; i < 384; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_bitmap, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_bitmap, BITMAP_32_HEIGHT);
	}
	for(i = 512; i < 640; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_bitmap, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_bitmap, BITMAP_32_HEIGHT);
	}
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
}

/********************************************************************************************
Function Name: 	render_score

Details: 	Takes the score from a cowboy struct and prints it to the scoreboard.

*********************************************************************************************/

void render_score(UINT8 *base, struct Scoreboard *scoreboard)
{
	int i, x, y;
	x = scoreboard->position.x;
	y = scoreboard->position.y;
	for (i = 4; i >= 0; i--) {
		plot_char(base, x, y, '0' + scoreboard->digit[i]);
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
	for (i = 0; i < lives->lives_left; i++) {
		plot_bitmap_16((UINT16 *) base, x, lives->position.y, bitmap16, BITMAP_HEIGHT);
		x += 16;
	}
}

/********************************************************************************************
Function Name: 	render_splash

Details: 	Using the plot_screen function, this will render a full screen image for the game's
			splash screen.

*********************************************************************************************/

void render_splash(UINT32 *base, const UINT32 *splash_bitmap)
{
	plot_splash((UINT32 *)base, SCREEN_HEIGHT, splash_bitmap);
}
