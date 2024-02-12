#include "renderer.h"

/*arrays of messages to be print in game*/
const UINT8 score[] = {'S','C','O','R','E','\0'};
const UINT8 lives[] = {'L','I','V','E','S','\0'};
const UINT8 gameover[] = {'G','A','M','E',' ','O','V','E','R','\0'};

/*arrays of spawn positions for snake enemies*/
const int spawn_x[16] = {384,416,448,480,256,256,256,256,608,608,608,608,384,416,448,480};
const int spawn_y[16] = {0,0,0,0,128,160,192,224,128,160,192,224,352,352,352,352};

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

while (isPlaying) {

	if(player_num == 1) {
		1st_x_start = 424;
		1st_y_start = 184;
	
  	game_start();







}

void game_start() {

  	char *base = Physbase();
	int i,j,k;
	unsigned long seed = 300;
	UINT16 *loc = (UINT16 *) base;
	int spawn_loc;
	int x;
	int lives_count;
	int score_value;
  	lives_count = 3;
	
	plot_bitmap_32((UINT32 *) base, 424, 184, cowboy_bitmap_32, BITMAP_32_HEIGHT);
	clear_bitmap_32((UINT32 *) base, 424, 184, cowboy_bitmap_32, BITMAP_32_HEIGHT);
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
	
	for (k = 0; k < SCREEN_HEIGHT; k++){ 
		for (j = 0; j < 16; j++) {
			*(loc++) = -1;
		}
		loc += 24;
	}
  
  	print_message((UINT8 *) base, lives, 32, 328);
	print_message((UINT8 *) base, score, 32, 300);
  
  	plot_bitmap_16((UINT16 *) base, 80, 320, cowboy_bitmap_16, BITMAP_HEIGHT);  
	plot_bitmap_16((UINT16 *) base, 96, 320, cowboy_bitmap_16, BITMAP_HEIGHT);
	plot_bitmap_16((UINT16 *) base, 112, 320, cowboy_bitmap_16, BITMAP_HEIGHT);

  	plot_char((UINT8 *) base, 80, 300, '0');
	plot_char((UINT8 *) base, 88, 300, '0');
	plot_char((UINT8 *) base, 96, 300, '0');
	plot_char((UINT8 *) base, 104, 300, '0');
	plot_char((UINT8 *) base, 112, 300, '0');
  
  
}
