#include "showdown.h"

const UINT32 * const timer = (UINT32 *)0x462;
const UINT8 buffer2[32256]; 

int quit = FALSE;
int mouse_enabled = FALSE;

int main() {
	
	UINT32 *start_base = get_video_base();
	UINT32 *base = get_video_base();
	UINT32 *base2 = get_buffer();
	
	install_vectors();
	
	splash_menu(base, base2);
	
	clear_ikbd_buffer();
	remove_vectors();

	stop_sound();
	set_video_base(start_base);
	return 0;
}

/********************************************************************************************
Function Name: 	splash_menu

Details: 	This function takes the user to the splash screen.

*********************************************************************************************/

void splash_menu(UINT32 *base, UINT32 *base2)
{
	char input = WAIT;
	int has_input = FALSE;
	int quit = FALSE;
	int players = 1;
	int avatar; /*0 = cowboy, 1 = cowgirl*/
	mouse_enabled = TRUE;
	prev_mouse_X = 200; 
	prev_mouse_Y = 200; 
	mouse_X = 20;
	mouse_Y = 20;
	render_splash((UINT32 *) base, splash_bitmap);
	print_message((UINT8 *)base, (UINT8 *)"PRESS ANY KEY", ANYKEY_X, ANYKEY_Y);

	start_music();
	
	/*mouse cursor test - work in progress */

	render_mouse((UINT16 *)base, prev_mouse_X, prev_mouse_Y, mouse_X, mouse_Y, mouse_cursor2);


	Cnecin();
	
	print_menu((UINT32 *)base);
		
	menu_sel((UINT32 *)base, &players, &quit);
	
	if(quit == FALSE)
	{
		print_avatar_sel((UINT32 *)base);
			
		avatar_sel((UINT32 *)base, &avatar);

		main_game((UINT32 *)base, (UINT32 *)base2, avatar, players);
	}
	return;
}

/********************************************************************************************
Function Name: 	main_game

Details: 	This function starts the game loop.

*********************************************************************************************/

void main_game(UINT32 *base, UINT32 *base2, const int avatar, const int players)
{
	struct Model model = init_Model(avatar);
	struct Model prev_model = init_Model(avatar);
	UINT32 *current;
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	UINT32 time_now, time_then, time_elapsed;
	char ch = NULL;
	int count = 0;
	UINT32 seed = 1245;
	/*UINT32 music_timer;*/
	UINT32 last_note_change = 0;
	int last_note = 0;
	int current_note;
	model.players = players;
	prev_model.players = players;

	mouse_enabled = FALSE;

	full_render((UINT32 *)base, &model, avatar);
	full_render((UINT32 *)base2, &model, avatar);
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
			
			/* cowboy special move, time permitting*/
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
			render((UINT32 *)current, &model, avatar);
		
			set_video_base(current);
			
		}
		
		if (music_change == TRUE)
		{
			music_change = FALSE;
			current_note = update_music(last_note, main_song_bass, main_song_treble, MAIN_SONG_LENGTH);
			last_note = current_note;
		}
	}
	return;
}

/********************************************************************************************
Function Name: 	print_menu

Details: 	This function prints the menu choices.

*********************************************************************************************/

void print_menu(UINT32 *base)
{
	clear_rec((UINT32 *)base, ANYKEY_X, ANYKEY_Y, LETTER_HEIGHT, MENU_CLEAR_1);
	
	print_message((UINT8 *)base, (UINT8 *)"1 PLAYER", ONE_X, ONE_Y);
	print_message((UINT8 *)base, (UINT8 *)"2 PLAYER", TWO_X, TWO_Y);
	print_message((UINT8 *)base, (UINT8 *)"[COMING SOON]", SOON_X, SOON_Y);
	print_message((UINT8 *)base, (UINT8 *)"QUIT", QUIT_MENU_X, QUIT_MENU_Y);
}

/********************************************************************************************
Function Name: 	menu_sel

Details: 	This function lets the user cycle through choose 1-player, 2-player, or quit.

*********************************************************************************************/

void menu_sel(UINT32 *base, int *players, int *quit)
{
	int menu_select = 1;
	char input = WAIT;
	while(input != ' ') {
	
	if (Cconis()){
		input = (char)Cnecin();
		play_pop();
	}
		
	switch (menu_select)
	{
		case 1:
			players = 1;
			clear_bitmap_16((UINT16 *)base, PISTOL_TWO_X, PISTOL_ONE_Y, menu_cursor_left, BITMAP_HEIGHT);
			clear_bitmap_16((UINT16 *)base, PISTOL_ONE_X, PISTOL_ONE_Y, menu_cursor_right, BITMAP_HEIGHT);
			if(input == 's')
			{
				menu_select = 2;
				plot_bitmap_16((UINT16 *)base, PISTOL_TWO_X, PISTOL_ONE_Y, menu_cursor_left, BITMAP_HEIGHT);
				plot_bitmap_16((UINT16 *)base, PISTOL_ONE_X, PISTOL_ONE_Y, menu_cursor_right, BITMAP_HEIGHT);
			}
			break;
		
		case 2:
			players = 2;
			clear_bitmap_16((UINT16 *)base, PISTOL_TWO_X, PISTOL_TWO_Y, menu_cursor_left, BITMAP_HEIGHT);
			clear_bitmap_16((UINT16 *)base, PISTOL_ONE_X, PISTOL_TWO_Y, menu_cursor_right, BITMAP_HEIGHT);
			if(input == 's')
			{
				menu_select = 3;
				plot_bitmap_16((UINT16 *)base, PISTOL_TWO_X, PISTOL_TWO_Y, menu_cursor_left, BITMAP_HEIGHT);
				plot_bitmap_16((UINT16 *)base, PISTOL_ONE_X, PISTOL_TWO_Y, menu_cursor_right, BITMAP_HEIGHT);
			}
			else if (input == 'w')
			{
				menu_select = 1;
				plot_bitmap_16((UINT16 *)base, PISTOL_TWO_X, PISTOL_TWO_Y, menu_cursor_left, BITMAP_HEIGHT);
				plot_bitmap_16((UINT16 *)base, PISTOL_ONE_X, PISTOL_TWO_Y, menu_cursor_right, BITMAP_HEIGHT);
			}	
			break;
		
		case 3:
			*quit = TRUE; 
			clear_bitmap_16((UINT16 *)base, PISTOL_TWO_QUIT_X, PISTOL_QUIT_Y, menu_cursor_left, BITMAP_HEIGHT);
			clear_bitmap_16((UINT16 *)base, PISTOL_ONE_QUIT_X, PISTOL_QUIT_Y, menu_cursor_right, BITMAP_HEIGHT);
			if(input == 'w')
			{
				menu_select = 2;
				*quit = FALSE;
				plot_bitmap_16((UINT16 *)base, PISTOL_TWO_QUIT_X, PISTOL_QUIT_Y, menu_cursor_left, BITMAP_HEIGHT);
				plot_bitmap_16((UINT16 *)base, PISTOL_ONE_QUIT_X, PISTOL_QUIT_Y, menu_cursor_right, BITMAP_HEIGHT);
			}	
			break;
		}
		if(input!=' ')
			input = WAIT;
	}
}

/********************************************************************************************
Function Name: 	print_avatar_sel

Details: 	This function prints the avatar choices (cowboy or cowgirl) and lets
			the user choose one of the other.

*********************************************************************************************/

void print_avatar_sel(UINT32 *base)
{
	clear_rec((UINT32 *)base, MENU_CLEAR_X, MENU_CLEAR_Y, MENU_CLEAR_HEIGHT, MENU_CLEAR_2);
	
	print_message((UINT8 *)base, (UINT8 *)"CHOOSE A CHARACTER (<-'a' 'd'->)", CHOOSE_X, CHOOSE_Y);
	print_message((UINT8 *)base, (UINT8 *)"PRESS SPACE TO CONFIRM", CONFIRM_X, CONFIRM_Y);
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", COWBOY_WRITING_X, COWBOY_WRITING_Y);
	print_message((UINT8 *)base, (UINT8 *)"COWGIRL", COWGIRL_WRITING_X, COWGIRL_WRITING_Y);
}

void avatar_sel(UINT32 *base, int *avatar)
{
	int avatar_select = 1;
	char input = WAIT;
	
	while(input != ' ') {
	
		if (Cconis()){
			input = (char)Cnecin();
			play_chime();
		}
			
		switch (avatar_select)
		{
			case 1:
				
				*avatar = 0;
				plot_bitmap_64((UINT32 *)base, COWBOY_CURSOR_X, COWBOY_CURSOR_Y, cursor, CURSOR_HEIGHT);
				if(input == 'a')
				{
					avatar_select = 2;
					*avatar = 1;
					clear_bitmap_64((UINT32 *)base, COWBOY_CURSOR_X, COWBOY_CURSOR_Y, cursor, CURSOR_HEIGHT);
				}
				break;
			
			case 2:
				
				*avatar = 1;
				plot_bitmap_64((UINT32 *)base, COWGIRL_CURSOR_X, COWGIRL_CURSOR_Y, cursor, CURSOR_HEIGHT);
				if(input == 'd')
				{
					avatar_select = 1;
					*avatar = 0;
					clear_bitmap_64((UINT32 *)base, COWGIRL_CURSOR_X, COWGIRL_CURSOR_Y, cursor, CURSOR_HEIGHT);
				}
				break;
		}
		if(input!=' ')
			input = WAIT;
		
	}
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