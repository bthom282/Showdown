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
const UINT8 p1_score_arr[] = {'0','0','0','0','0','\0'};
const UINT8 p2_score_arr[] = {'0','0','0','0','0','\0'};
const UINT8 lives[] = {'L','I','V','E','S','\0'};
const UINT8 gameover[] = {'G','A','M','E',' ','O','V','E','R','\0'};
const UINT8 player1[] = {'P','L','A','Y','E','R',' ','1','\0'};
const UINT8 player2[] = {'P','L','A','Y','E','R',' ','2','\0'};
const UINT8 cont[] = {'C','O','N','T','I','N','U','E','?','\0'};
const UINT8 yesno[] = {'P','R','E','S','S',' ','y',' ','O','R',' ','n'};

int 1st_x_start;
int 1st_y_start;
int 2nd_x_start;
int 2nd_y_start;
int player_num;
int 1st_lives_count;
int 2nd_lives_count;
int 1st_score_value;
int 2nd_score_value;

bool isPlaying = TRUE;

while (isPlaying == TRUE) {

	if(player_num == 1) {
		1st_x_start = 424;
		1st_y_start = 184;
	
  	game_start();
}

void render(const Model *model, UINT32 *base)
{


}

void render_bullet(const *Bullet, UINT8 *base)
{

}

void render_cowboy(const *Cowboy, UINT32 *base)
{

}

void render_snake(const *Snake, UINT32 *base)
{

}

void game_start() {

  	char *base = Physbase();
	int i,j,k;
	unsigned long seed = 300;
	UINT16 *loc = (UINT16 *) base;
	int spawn_loc;
	int x;
	int p1_lives_count;
	int p2_lives_count;
	int p1_score_value;
	int p2_score_value;
	
	p1_lives_count = 3;
	p2_lives_count = 3;
	p1_score_value = 0;
	p2_score_value = 0;
	
	plot_bitmap_32((UINT32 *) base, 424, 184, cowboy_bitmap_32, BITMAP_32_HEIGHT);
	/*clear_bitmap_32((UINT32 *) base, 424, 184, cowboy_bitmap_32, BITMAP_32_HEIGHT);*/
	for(i = 0; i < 128; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_32, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_32, BITMAP_32_HEIGHT);
	}
	for(i = 256; i < SCREEN_HEIGHT-32; i += 32){
		plot_bitmap_32((UINT32 *) base, 256, i, cactus_32, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, 608, i, cactus_32, BITMAP_32_HEIGHT);
	}
	for(i = 256; i < 384; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_32, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_32, BITMAP_32_HEIGHT);
	}
	for(i = 512; i < 640; i += 32){
		plot_bitmap_32((UINT32 *) base, i, 0, cactus_32, BITMAP_32_HEIGHT);
		plot_bitmap_32((UINT32 *) base, i, 352, cactus_32, BITMAP_32_HEIGHT);
	}
	
	/*Fill side panel.*/
	
	for (k = 0; k < SCREEN_HEIGHT; k++){ 
		for (j = 0; j < 16; j++) {
			*(loc++) = -1;
		}
		loc += 24;
	}
	
	/*prints player 1 lives and score label*/
	
	print_message((UINT8 *) base, player1, 32, 280);
	print_message((UINT8 *) base, score, 32, 300);
	print_message((UINT8 *) base, lives, 32, 320);
	
	/*if two player mode toggled, prints player 2 lives and score label*/
	
	print_message((UINT8 *) base, player2, 32, 212);
	print_message((UINT8 *) base, score, 32, 232);
	print_message((UINT8 *) base, lives, 32, 252);
		
	update_lives ((UINT16 *) base, p1_lives_count, 320, cowboy_lives);
	update_lives ((UINT16 *) base, p1_lives_count, 252, cowgirl_lives);

	plot_char((UINT8 *) base, 80, 300, '0');
	plot_char((UINT8 *) base, 88, 300, '0');
	plot_char((UINT8 *) base, 96, 300, '0');
	plot_char((UINT8 *) base, 104, 300, '0');
	plot_char((UINT8 *) base, 112, 300, '0');
	
	plot_char((UINT8 *) base, 80, 232, '0');
	plot_char((UINT8 *) base, 88, 232, '0');
	plot_char((UINT8 *) base, 96, 232, '0');
	plot_char((UINT8 *) base, 104, 232, '0');
	plot_char((UINT8 *) base, 112, 232, '0');
}
