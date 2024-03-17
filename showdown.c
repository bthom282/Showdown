#include "showdown.h"

const UINT32 * const timer = (UINT32 *)0x462;
const UINT8 buffer2[32256]; /* used for double buffering */

UINT32 time_now, time_then, time_delta;
const UINT8 buffer2[32256]; 
const UINT8 snapshotBuffer[32000];

int main() {
	
	char *base = Physbase();
	UINT32 seed = 1245;
	int players = 1;
	struct Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	int bullets_fill = 0;
	int snakes_fill = 0;
	int i;
	char buffer[20];
		
	int y_dir;
	int x_dir;
	int state;
    int spawn_loc;
	int quit = FALSE;
	char ch = NULL;
	int count_sec = 0;

	/*initializing the model*/

	struct Model model = init_Model();

	render((UINT32 *)base, &model);

	while(!quit) {
		time_then = get_time();
		while (ch != 'q') {
			
			if (Cconis()){
				ch = (char)Cnecin();
			}

			if (ch == 'w')
			{
				model.cowboy.isMoving = TRUE;
				if (model.cowboy.state != 10)
				{model.cowboy.state = 10;}
				else
				{model.cowboy.state = 11;}
				model.cowboy.y_dir = -1;
				model.cowboy.x_dir = 0;	
			}
			if (ch == 'a')
			{
				model.cowboy.isMoving = TRUE;
				if (model.cowboy.state != 4)
				{model.cowboy.state = 4;}
				else
				{model.cowboy.state = 5;}
				model.cowboy.y_dir = 0;
				model.cowboy.x_dir = -1;	
			}
			if (ch == 's')
			{
				model.cowboy.isMoving = TRUE;
				if (model.cowboy.state != 1)
				{model.cowboy.state = 1;}
				else
				{model.cowboy.state = 2;}
				model.cowboy.y_dir = 1;
				model.cowboy.x_dir = 0;	
			}
			if (ch == 'd')
			{
				model.cowboy.isMoving = TRUE;
				if (model.cowboy.state != 7)
				{model.cowboy.state = 7;}
				else
				{model.cowboy.state = 8;}
				model.cowboy.y_dir = 0;
				model.cowboy.x_dir = 1;	
			}	
	
			if (ch == '8')
			{
				model.cowboy.isFiring = TRUE;
				y_dir = -1;
				x_dir = 0;	
			}
			if (ch == '4')
			{
				model.cowboy.isFiring = TRUE;
				y_dir = 0;
				x_dir = -1;	
			}
			if (ch == '2')
			{
				model.cowboy.isFiring = TRUE;
				y_dir = 1;
				x_dir = 0;	
			}
			if (ch == '6')
			{
				model.cowboy.isFiring = TRUE;
				y_dir = 0;
				x_dir = 1;	
			}	
			model.cowboy.yFireDir = y_dir;
			model.cowboy.xFireDir = x_dir;
			shooting(&model.cowboy, model.active_bullets, &model.bullets_fill);

			update_render((UINT32 *)base, &model); 
			for (i = 0; i < bullets_fill; i++) {
			clear_bitmap_8((UINT8 *) base, model.active_bullets[i].position.x, model.active_bullets[i].position.y, bullet_bitmap, BITMAP_8_HEIGHT);
			}
			move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes, &model.snakes_fill, model.cowboy);
			for (i = 0; i < snakes_fill; i++) {
			clear_bitmap_32((UINT32 *) base, model.active_snakes[i].position.x, model.active_snakes[i].position.y, blank, BITMAP_32_HEIGHT);
			}
			update_render((UINT32 *)base, &model); 
			time_now = get_time();
			time_delta = time_now - time_then;
			clear_bitmap_32((UINT32 *) base, model.cowboy.position.x, model.cowboy.position.y, blank, BITMAP_32_HEIGHT);
			move_cowboy(&model.cowboy);
			update_render((UINT32 *)base, &model); 
			/*move_snakes(model.active_snakes, model.snakes_fill, model.cowboy);*/
			model.cowboy.isMoving = FALSE;
			model.cowboy.isFiring = FALSE;
			
			if(ch!='q')
				ch = NULL;
			
			if(time_delta >= 210) {
				if (count_sec < 30) {
					spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
				} 
				time_then = time_now;
			}
			/*
			if (count_sec > 30 && snakes_fill == 0) {*/
				/* wave complete */
				/* cowboy special move */
				/*count_sec = 0;
			}
*/
			Vsync();
				}
		quit = TRUE; 
	}
	
	
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

Details: 	Using supervisor mode, this function gets the current clock time.

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
