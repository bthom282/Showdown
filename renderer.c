/**************************************************************************************
Names:		Adam Cole, Brooklyn Thomson

Purpose:	Links the model with the low-level graphics library, so that it is 
		possible to render an individual, static frame of animation based on 
  		a static snapshot of the world.
**************************************************************************************/
#include "renderer.h"
#include "BITMAPS.H"

/*arrays of messages to be print in game*/
const UINT8 score[] = {'S','C','O','R','E','\0'};
const UINT8 lives[] = {'L','I','V','E','S','\0'};
const UINT8 gameover[] = {'G','A','M','E',' ','O','V','E','R','\0'};
const UINT8 player1[] = {'P','L','A','Y','E','R',' ','1','\0'};
const UINT8 player2[] = {'P','L','A','Y','E','R',' ','2','\0'};
const UINT8 cont[] = {'C','O','N','T','I','N','U','E','?','\0'};
const UINT8 yesno[] = {'P','R','E','S','S',' ','y',' ','O','R',' ','n'};

int players = 1;

void render(const Model *model, UINT32 *base)
{
	
}

/********************************************************************************************
Function Name: 	render_cowboy

Details: 	renders the cowboy using his x and y position from the cowboy struct.

*********************************************************************************************/

void render_cowboy(UINT32 *base, struct Cowboy cowboy)
{
	plot_bitmap_32((UINT32 *) base, cowboy.position.x, cowboy.position.y, cowboy.bitmap, BITMAP_32_HEIGHT, cowboy.state);
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

void render_snakes(UINT32 *base, struct Snake *active_snakes, int snakes_fill)
{
	int i;
	for (i = 0; i < snakes_fill; i++) {
		plot_bitmap_32((UINT32 *) base, active_snakes[i].position.x, active_snakes[i].position.y, active_snakes[i].bitmap, BITMAP_32_HEIGHT, active_snakes[i].state);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_side_panel

Details: 	Fills side panel in black.

*********************************************************************************************/

void render_side_panel(UINT32 *base, const UINT32 *bitmap)
{
	UINT16 *loc = (UINT16 *) base;
	int k, j;
	for (k = 0; k < SCREEN_HEIGHT; k++){ 
		for (j = 0; j < 16; j++) {
			*(loc++) = -1;
		}
		loc += 24;
	}

/********************************************************************************************
Function Name: 	render_level1

Details: 	renders the cowboy using his x and y position from the cowboy struct.

*********************************************************************************************/

void render_level1(UINT32 *base, const UINT32 *bitmap)
{
	int i;
	for(i = 0; i < 128; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_32, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_32, BITMAP_32_HEIGHT, 0);
	}
	for(i = 256; i < SCREEN_HEIGHT-32; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_32, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_32, BITMAP_32_HEIGHT, 0);
	}
	for(i = 256; i < 384; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_32, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_32, BITMAP_32_HEIGHT, 0);
	}
	for(i = 512; i < 640; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_32, BITMAP_32_HEIGHT, 0);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_32, BITMAP_32_HEIGHT, 0);
	}
	return;
}

/********************************************************************************************
Function Name: 	render_side_text

Details: 	prints the initial text based on number of players.

*********************************************************************************************/
void render_side_text(UINT8 *base, int players) {
	print_message(base, player1, 32, 280);
	print_message(base, score, 32, 300);
	print_message(base, lives, 32, 320);
	
	if (players == 2) {
	print_message(base, player2, 32, 212);
	print_message(base, score, 32, 232);
	print_message(base, lives, 32, 252);
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
	x = scoreboard->position.x;
	y = scoreboard->position.y;
	for (i = 4; i >= 0; i--) {
		plot_char(base, x, y, '0' + scoreboard->digit[i]);
		x += 8;
	}
}

void render_lives(UINT16 *base, struct *Lives, const UINT16 *bitmap16)
{
	int i, x;
	x = 80;
	for (i = 0; i < Lives.lives; i++) {
		plot_bitmap_16((UINT16 *) base, x, 252, bitmap16, BITMAP_HEIGHT);
		x += 16;
	}
}

void game_start() {

  	char *base = Physbase();
	unsigned long seed = 300;
	UINT16 *loc = (UINT16 *) base;
	
	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1;
	cowboy1.position.x = 350; 
	cowboy1.position.y = 100;
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
	cowboy1.scoreboard.position.x = 184;
	cowboy1.scoreboard.position.y = 424;
	cowboy1.lives = 3;
	cowboy1.bitmap = cowboy_bitmap_32[cowboy1.state];

	render_cowboy((UINT32 *) base, cowboy1)
}
