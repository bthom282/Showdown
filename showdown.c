#include "showdown.h"

const UINT32 * const timer = (UINT32 *)0x462;
const UINT8 buffer2[32256]; 
const UINT8 buffer[32000];

int quit = FALSE;
int mouse_enabled = FALSE;

/*const UINT16 *lives_tokens = cowboy_lives;
const UINT32 avatar[][BITMAP_32_HEIGHT] = (UINT32 *) cowgirl_bitmap;*/

int main() {
	
	UINT32 *start_base = get_video_base();
	UINT32 *base = get_video_base();
	UINT32 *base2 = get_buffer();
	
	install_vectors();
	
	splash_menu(base, base2);
	
	remove_vectors();

	stop_sound();
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
Function Name: 	splash_menu

Details: 	This function takes the user to the splash screen to choose 1 or 2 player mode and
			select an avatar.

*********************************************************************************************/

void splash_menu(UINT32 *base, UINT32 *base2)
{
	char input = WAIT;
	int has_input = FALSE;
	int quit = FALSE;
	/*initial screen*/
	int players = 1;
	int menu_select = 1;
	mouse_enabled = TRUE;
	render_splash((UINT32 *) base, splash_bitmap);
	print_message((UINT8 *)base, (UINT8 *)"PRESS ANY KEY", ANYKEY_X, ANYKEY_Y);
	start_music();
	
	/*mouse cursor test - work in progress */
	/*while (!Cconis())
	{
		render_mouse((UINT16 *)base, prev_mouse_X, prev_mouse_Y, mouse_X, mouse_Y, mouse_cursor2);
	}*/
	
	/* mode selection */
	/*while (!has_input)
	{
		has_input = check_input();
		if (has_input == TRUE)
		{
			input = get_input();
		}
	}*/
	Cnecin();
	clear_rec((UINT32 *)base, ANYKEY_X, ANYKEY_Y, LETTER_HEIGHT, MENU_CLEAR_1);
	
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 1", ONE_X, ONE_Y);
	print_message((UINT8 *)base, (UINT8 *)"PLAYER 2", TWO_X, TWO_Y);
	print_message((UINT8 *)base, (UINT8 *)"[COMING SOON]", SOON_X, SOON_Y);
	print_message((UINT8 *)base, (UINT8 *)"QUIT", QUIT_X, QUIT_Y);
		
	/*while (input != SPACE_MAKE)
	{
		has_input = check_input();
		if (has_input == TRUE)
		{
			input = get_input();
		}
		
		switch (menu_select)
		{
			case 1:
				plot_bitmap_8((UINT8 *)base, ARROW_ONE_X, ARROW_ONE_Y, arrow1_cursor, BITMAP_8_HEIGHT);
				plot_bitmap_8((UINT8 *)base, ARROW_ONE_X + ONE_LENGTH + LETTER_WIDTH, ARROW_ONE_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				if(input == DOWN_MAKE)
				{
					menu_select = 2;
					clear_bitmap_8((UINT8 *)base, ARROW_ONE_X, ARROW_ONE_Y, arrow1_cursor, BITMAP_8_HEIGHT);
					clear_bitmap_8((UINT8 *)base, ARROW_ONE_X + ONE_LENGTH + LETTER_WIDTH, ARROW_ONE_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				}
				else if (input == SPACE_MAKE)
				{
					players = 1;
				}
				break;
			
			case 2:
				plot_bitmap_8((UINT8 *)base, ARROW_TWO_X, ARROW_TWO_Y, arrow1_cursor, BITMAP_8_HEIGHT);
				plot_bitmap_8((UINT8 *)base, ARROW_TWO_X + TWO_LENGTH + LETTER_WIDTH, ARROW_TWO_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				if(input == DOWN_MAKE)
				{
					menu_select = 3;
					clear_bitmap_8((UINT8 *)base, ARROW_TWO_X, ARROW_TWO_Y, arrow1_cursor, BITMAP_8_HEIGHT);
					clear_bitmap_8((UINT8 *)base, ARROW_TWO_X + TWO_LENGTH + LETTER_WIDTH, ARROW_TWO_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				}
				else if (input == UP_MAKE)
				{
					menu_select = 1;
					clear_bitmap_8((UINT8 *)base, ARROW_TWO_X, ARROW_TWO_Y, arrow1_cursor, BITMAP_8_HEIGHT);
					clear_bitmap_8((UINT8 *)base, ARROW_TWO_X + TWO_LENGTH + LETTER_WIDTH, ARROW_TWO_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				}
				else if (input == SPACE_MAKE)*/
					/*players = 2;*/
				/*break;
			
			case 3:
				plot_bitmap_8((UINT8 *)base, ARROW_QUIT_X, ARROW_QUIT_Y, arrow1_cursor, BITMAP_8_HEIGHT);
				plot_bitmap_8((UINT8 *)base, ARROW_QUIT_X + QUIT_LENGTH + LETTER_WIDTH, ARROW_QUIT_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				if(input == UP_MAKE)
				{
					menu_select = 2;
					clear_bitmap_8((UINT8 *)base, ARROW_QUIT_X, ARROW_QUIT_Y, arrow1_cursor, BITMAP_8_HEIGHT);
					clear_bitmap_8((UINT8 *)base, ARROW_QUIT_X + QUIT_LENGTH + LETTER_WIDTH, ARROW_QUIT_Y, arrow2_cursor, BITMAP_8_HEIGHT);
				}
				else if (input = SPACE_MAKE)
					quit == TRUE;
				break;
		}
		input = WAIT;
	}*/
	/*}*/
	/* avatar selection */
	Cnecin(); 
	
	clear_rec((UINT32 *)base, MENU_CLEAR_X, MENU_CLEAR_Y, MENU_CLEAR_HEIGHT, MENU_CLEAR_2);
	
	print_message((UINT8 *)base, (UINT8 *)"CHOOSE A CHARACTER (<- ->)", CHOOSE_X, CHOOSE_Y);
	print_message((UINT8 *)base, (UINT8 *)"PRESS SPACE TO CONFIRM", CONFIRM_X, CONFIRM_Y);
	
	plot_bitmap_64((UINT32 *)base, COWBOY_CURSOR_X, COWBOY_CURSOR_Y, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, COWGIRL_CURSOR_X, COWGIRL_CURSOR_Y, cursor, CURSOR_HEIGHT);
	
	Cnecin(); 
	clear_bitmap_64((UINT32 *)base, COWGIRL_CURSOR_X, COWGIRL_CURSOR_Y, cursor, CURSOR_HEIGHT);
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", COWBOY_WRITING_X, COWBOY_WRITING_Y);
	
	Cnecin(); 
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", COWBOY_WRITING_X, COWBOY_WRITING_Y);
	clear_bitmap_64((UINT32 *)base, COWBOY_CURSOR_X, COWBOY_CURSOR_Y, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, COWGIRL_CURSOR_X, COWGIRL_CURSOR_Y, cursor, CURSOR_HEIGHT);
	print_message((UINT8 *)base, (UINT8 *)"COWGIRL", COWGIRL_WRITING_X, COWGIRL_WRITING_Y);
	
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
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	UINT32 time_now, time_then, time_elapsed;
	char ch = NULL;
	int count = 0;
	UINT32 seed = 1245;
	UINT32 music_timer;
	UINT32 last_note_change = 0;
	int last_note = 0;
	int current_note;

	mouse_enabled = FALSE;

	render((UINT32 *)base, &model);
	render((UINT32 *)base2, &model);
	while(ch != 'q') {
		time_now = get_time();
		time_elapsed = time_now - time_then;
		
		if (Cconis()){
			ch = (char)Cnecin();
			input_handler(ch, &model, &quit);
		}

		if(ch!='q')
			ch = NULL;
		
		if(model.cowboy.lives.lives_left == 0)
		{
			gameover(base, &ch);
		}

		if(spawn_snake_request == TRUE && count < WAVE_COUNT) {
			spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
			play_spawn();
			count++;
			spawn_snake_request = FALSE;
		}
			
		if (count == WAVE_COUNT && model.snakes_fill == 0) {
			/* wave complete */
			wave_bonus((UINT8 *)base, &game_timer, &model.cowboy.scoreboard);
			
			/* cowboy special move */
			count = 0;
		}
		
		if (render_request == TRUE)
		{	
			render_request = FALSE;
			if (current == base2)
				current = base;
			else
				current = base2;
		
			process_synchronous(&model);
			update_render((UINT32 *)current, &model);
		
			set_video_base(current);
			
		}
		music_timer = game_timer - last_note_change;
		current_note = update_music(music_timer, last_note, main_song_bass, main_song_treble, MAIN_SONG_LENGTH);

		if (current_note != last_note)
		{
			last_note_change = game_timer;
			last_note = current_note;
		}
	}
	return;
}

/*******************************************************************************************
Function Name: 	gameover

Details: 	This function is triggered when the player has run out of lives. It will 
			print "game over" many times, then indicate the final score somehow, fill
			the screen black, then print a message promting the user to either continue
    		or quit. 	

Sample Call:

*********************************************************************************************/

void gameover(UINT32 *base, char *ch) {
	int i, j;
	int count = 0;
	while(count != 10)
	{
		for (i = 0; i < 276; i += 12) {
				for (j = 0; j < 200; j += 80) {
					print_message((UINT8 *) base, (UINT8 *)"GAME OVER! ", j, i);
				}
			}
		count++;
	}
	
	ch = 'q';
	return;
}
