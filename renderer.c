/**************************************************************************************
Names:		Adam Cole, Brooklyn Thomson

Purpose:	Links the model with the low-level graphics library, so that it is 
		possible to render an individual, static frame of animation based on 
  		a static snapshot of the world.
**************************************************************************************/
#include "renderer.h"

/********************************************************************************************
Function Name: 	full_render

Details: 	renders a whole frame based on the current state of the model.

*********************************************************************************************/

void full_render(UINT32 *base, struct Model *model, int avatar)
{ 
	
	fill_screen((UINT32 *) base, 0);
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, model->players);
	render_score((UINT8 *) base, &model->cowboy.scoreboard);
	model->cowboy.scoreboard.isRendered = TRUE;
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_snakes((UINT32 *) base, model->active_snakes, model->snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, model->active_bullets, bullet_bitmap, model->bullets_fill);
	
	if(avatar == 0)
	{
		render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowboy_bitmap);
		render_lives((UINT16 *) base, &model->cowboy.lives, (UINT16 *)cowboy_lives);
	}
	else
	{
		render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowgirl_bitmap);
		render_lives((UINT16 *) base, &model->cowboy.lives, (UINT16 *)cowgirl_lives);
	}
}

/********************************************************************************************
Function Name: 	update_render

Details: 	updates the render of any moving object

*********************************************************************************************/

void render(UINT32 *base, struct Model *model, int avatar)
{
	clear_rec(base, 256, 0, 384, 12);
	fill_rec((UINT16 *)base, 80, 300, 64, 4);
	render_score((UINT8 *) base, &model->cowboy.scoreboard);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_snakes((UINT32 *) base, model->active_snakes, model->snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, model->active_bullets, bullet_bitmap, model->bullets_fill);
	if(avatar == 0)
	{
		render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowboy_bitmap);
		render_lives((UINT16 *) base, &model->cowboy.lives, (UINT16 *)cowboy_lives);
	}
	else
	{
		render_cowboy((UINT32 *) base, model->cowboy, (UINT32 *) cowgirl_bitmap);
		render_lives((UINT16 *) base, &model->cowboy.lives, (UINT16 *)cowgirl_lives);
	}
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

Details: 	prints the initial play instructions and other text based on number of players.

*********************************************************************************************/
void render_side_text(UINT8 *base, int players) 
{
	print_message((UINT8 *)base, (UINT8 *)"QUIT", TEXT_ALIGN, 20);
	plot_bitmap_32_white((UINT32 *)base, 64, 10, key_Q, BITMAP_32_HEIGHT);
	print_message((UINT8 *)base, (UINT8 *)"MOVE", TEXT_ALIGN, 60);
	
	plot_bitmap_32_white((UINT32 *)base, 64, 30, key_A, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 96, 15, key_W, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 96, 30, key_S, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 128, 30, key_D, BITMAP_32_HEIGHT);
	
	print_message((UINT8 *)base, (UINT8 *)"SHOOT", TEXT_ALIGN, 100);
	
	plot_bitmap_32_white((UINT32 *)base, 64, 55, blank_key, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 96, 55, key_8, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 128, 55, blank_key, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 64, 70, key_4, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 96, 70, key_5, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 128, 70, key_6, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 64, 85, blank_key, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 96, 85, blank_key, BITMAP_32_HEIGHT);
	plot_bitmap_32_white((UINT32 *)base, 128, 85, blank_key, BITMAP_32_HEIGHT);
	
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 1", TEXT_ALIGN, PLAYER_1_TEXT);
	print_message((UINT8 *)base, (UINT8 *)"SCORE", TEXT_ALIGN, PLAYER_1_SCORE_TEXT);
	print_message((UINT8 *)base, (UINT8 *)"LIVES", TEXT_ALIGN, PLAYER_1_LIVES_TEXT);
	
	if (players == 2) {
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 2", TEXT_ALIGN, PLAYER_2_TEXT);
	print_message((UINT8 *)base, (UINT8 *)"SCORE", TEXT_ALIGN, PLAYER_2_SCORE_TEXT);
	print_message((UINT8 *)base, (UINT8 *)"LIVES", TEXT_ALIGN, PLAYER_2_LIVES_TEXT);
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

/********************************************************************************************
Function Name: 	render_mouse

Details: 	Using the plot_screen function, this will render a full screen image for the game's
			splash screen.

*********************************************************************************************/

void render_mouse(UINT16 *base, int prev_mouse_X, int prev_mouse_Y, int mouse_X, int mouse_Y, const UINT16 *mouse_bitmap)
{
	clear_bitmap_16((UINT16 *)base, prev_mouse_X, prev_mouse_Y, mouse_bitmap, BITMAP_HEIGHT);
	plot_bitmap_16((UINT16 *)base, mouse_X, mouse_Y, mouse_bitmap, BITMAP_HEIGHT);
}
