#include "showdown.h"

const UINT32 * const timer = (UINT32 *)0x462;
const UINT8 buffer2[32256]; 
const UINT8 buffer[32000];

int main() {
	
	UINT32 *start_base = Physbase();
	UINT32 *base = Physbase();
	UINT32 *base2 = get_buffer();
	UINT32 *current;
	UINT32 seed = 1245;
	int players = 1;
	struct Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	int i;
	UINT32 time_now, time_then, time_elapsed;
	int state;
	int quit = FALSE;
	char ch = NULL;
	int count = 0;
	int back_buffer = FALSE;
	
	struct Model model = init_Model();
	struct Model prev_model = init_Model();
	
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
	
	print_message((UINT8 *)base, (UINT8 *)"CHOOSE A CHARACTER", 256, 224);
	
	plot_bitmap_64((UINT32 *)base, 338, 285, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	
	Cnecin(); 
	clear_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", 408, 308);
	
	Cnecin(); 
	
	print_message((UINT8 *)base, (UINT8 *)"COWBOY", 408, 308);
	/*clear_rec((UINT32 *)base, 416, 308, 8, 2);*/
	clear_bitmap_64((UINT32 *)base, 338, 285, cursor, CURSOR_HEIGHT);
	plot_bitmap_64((UINT32 *)base, 241, 282, cursor, CURSOR_HEIGHT);
	print_message((UINT8 *)base, (UINT8 *)"COWGIRL", 160, 308);
	print_message((UINT8 *)base, (UINT8 *)"[COMING SOON]", 136, 316);
	
	Cnecin(); 

	/*initializing the model*/

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
		
			
			/*fill_screen((UINT32 *) current, 0);*/
			clear_rec(current, 256, 0, 384, 12);
			fill_rec((UINT16 *)current, 80, 300, 64, 4);
			update_render((UINT32 *)current, &model);
			/*render((UINT32 *)current, &model);*/
			update_movement(&model);
			/*update_render((UINT32 *)base, &model);*/
			move_cowboy(&model.cowboy);
			shooting(&model.cowboy, model.active_bullets, &model.bullets_fill);
			model.cowboy.isMoving = FALSE;
			model.cowboy.isFiring = FALSE;
			Setscreen (-1,current,-1);
			/*Vsync();*/
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
	Setscreen(-1, start_base, -1);
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
	UINT32 buff2Addr;
	UINT32 align;

	/* initializes the back buffer to be 256 aligned */
	buff2Addr = (UINT32)buffer2;
	align = buff2Addr % 256;
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
}


/********************************************************************************************
Function Name: 	input_handler

Details: 	When a keypress is sensed, the char inputted is passed to the input handler for
			interpretation.

*********************************************************************************************/

void input_handler(char input, struct Model *model, int *quit)
{
	int y_dir;
	int x_dir;
	char ch = input;
	
	if (ch == 'q')
	{
		quit = TRUE;
	}
	
	if (ch == 'w')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 10)
		{model->cowboy.state = 10;}
		else
		{model->cowboy.state = 11;}
		model->cowboy.y_dir = -1;
		model->cowboy.x_dir = 0;	
	}
	if (ch == 'a')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 4)
		{model->cowboy.state = 4;}
		else
		{model->cowboy.state = 5;}
		model->cowboy.y_dir = 0;
		model->cowboy.x_dir = -1;	
	}
	if (ch == 's')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 1)
		{model->cowboy.state = 1;}
		else
		{model->cowboy.state = 2;}
		model->cowboy.y_dir = 1;
		model->cowboy.x_dir = 0;	
	}
	if (ch == 'd')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 7)
		{model->cowboy.state = 7;}
		else
		{model->cowboy.state = 8;}
		model->cowboy.y_dir = 0;
		model->cowboy.x_dir = 1;	
	}	

	if (ch == '8')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = -1;
		x_dir = 0;	
	}
	if (ch == '4')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 0;
		x_dir = -1;	
	}
	if (ch == '5')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 1;
		x_dir = 0;	
	}
	if (ch == '6')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 0;
		x_dir = 1;	
	}	
	model->cowboy.yFireDir = y_dir;
	model->cowboy.xFireDir = x_dir;
}
