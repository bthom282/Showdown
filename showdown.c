#include "showdown.h"

const UINT32 * const timer = (UINT32 *)0x462;
const UINT8 buffer2[32256]; 
const UINT8 buffer[32000];

int quit = FALSE;
int game_state = 0; /*states are 0 = splash, 1 = main game, 2 = game over*/
/*const UINT16 *lives_tokens = cowboy_lives;
const UINT32 avatar[][BITMAP_32_HEIGHT] = (UINT32 *) cowgirl_bitmap;*/

int main() {
	
	UINT32 *start_base = get_video_base();
	UINT32 *base = get_video_base();
	UINT32 *base2 = get_buffer();
	
	splash_menu(base, base2);

	set_video_base(start_base);
	return 0;
}

/********************************************************************************************
Function Name: 	get_time

Details: 	Using supervisor mode, this function gets the current clock time.

*********************************************************************************************/

UINT32 get_time()
{
	UINT32 time, old_ssp;

	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);

	return time;
}

/********************************************************************************************
Function Name: 	get_buffer

Details: 	This function gets the back buffer and aligns it to a multiple of 256.

*********************************************************************************************/

UINT32* get_buffer()
{
	UINT32 *base;
	UINT32 buff2_addr;
	UINT32 align;

	/* initializes the back buffer to be 256 aligned */
	buff2_addr = (UINT32)buffer2;
	align = buff2_addr % 256;
	base = (UINT32 *)(buffer2 + (256 - align));

	return base;
}

/********************************************************************************************
Function Name: 	swap_buffers

Details: 	This function swaps the back buffer with the front buffer.

*********************************************************************************************/

void swap_buffers (UINT32** base32, UINT32** back_buffer_ptr)
{
	UINT32* temp = * base32;
	* base32 = * back_buffer_ptr;
	* back_buffer_ptr = temp;
	return;
}

/********************************************************************************************
Function Name: 	splash_menu

Details: 	This function takes the user to the splash screen to choose 1 or 2 player mode and
			select an avatar.

*********************************************************************************************/

void splash_menu(UINT32 *base, UINT32 *base2)
{
	int players = 1;
	render_splash((UINT32 *) base, splash_bitmap);
	print_message((UINT8 *)base, (UINT8 *)"PRESS ANY KEY", 272, 224);

	Cnecin(); 
	
	
	clear_rec((UINT32 *)base, 272, 224, 8, 4);
	
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 1", 288, 200);
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 2", 288, 216);
	print_message((UINT8 *)base, (UINT8 *)"[COMING SOON]", 272, 224);
	print_message((UINT8 *)base, (UINT8 *)"QUIT", 308, 240);

	Cnecin(); 
	
	clear_rec((UINT32 *)base, 272, 200, 56, 5);
	
	print_message((UINT8 *)base, (UINT8 *)"CHOOSE A CHARACTER (<- ->)", 232, 224);
	print_message((UINT8 *)base, (UINT8 *)"PRESS SPACE TO CONFIRM", 240, 240);
	
	plot_bitmap_64((UINT32 *)base, 338, 285, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	
	Cnecin(); 
	clear_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", 408, 308);
	
	Cnecin(); 
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", 408, 308);
	clear_bitmap_64((UINT32 *)base, 338, 285, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	print_message((UINT8 *)base, (UINT8 *)"COWGIRL", 160, 308);
	print_message((UINT8 *)base, (UINT8 *)"[COMING SOON]", 136, 316);
	
	Cnecin(); 
	main_game(base, base2, players);
	return;
}

/********************************************************************************************
Function Name: 	main_game

Details: 	This function starts the game loop.

*********************************************************************************************/

void main_game(UINT32 *base, UINT32 *base2, int players)
{
	struct Model model = init_Model();
	struct Model prev_model = init_Model();
	UINT32 *current;
	struct Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	UINT32 time_now, time_then, time_elapsed;
	char ch = NULL;
	int count = 0;
	UINT32 seed = 1245;
	
	fill_screen((UINT32 *) base, 0);

	render((UINT32 *)base, &model);
	render((UINT32 *)base2, &model);
	while(ch != 'q') {
		time_now = get_time();
		time_elapsed = time_now - time_then;
		
		if (Cconis()){
			ch = (char)Cnecin();
			input_handler(ch, &model, &quit);
		}

		if (time_elapsed > 0)
		{
			if (current == base2)
				current = base;
			else
				current = base2;
		
			update_model(&model);
			update_render((UINT32 *)current, &model);
			/*model.cowboy.isMoving = FALSE;
			model.cowboy.isFiring = FALSE;*/
			set_video_base(current);
		}

		if(ch!='q')
			ch = NULL;

		if(time_elapsed >= 70 && count < WAVE_COUNT) {
			spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
			count++;
			time_then = get_time();
		}
			
		if (count == WAVE_COUNT && model.snakes_fill == 0) {
			/* wave complete */
			wave_bonus(&model.cowboy.scoreboard);
			/* cowboy special move */
			count = 0;
		}
	}
	return;
}