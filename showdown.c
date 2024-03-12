#include <stdio.h>
#include <osbind.h>
#include "types.h"
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "raster.h"
#include "bitmaps.h"

const UINT32 * const timer = (UINT32 *)0x462;
UINT32 time_now, time_then, time_delta;

UINT32 get_time();

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

	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1 = init_Cowboy();
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	while(!quit) {
		time_then = get_time();
		while (ch != 'q') {
			
			if (Cconis()){
				ch = (char)Cnecin();
			}

			if (ch == 'w')
			{
				cowboy1.isMoving = TRUE;
				if (cowboy1.state != 10)
				{cowboy1.state = 10;}
				else
				{cowboy1.state = 11;}
				cowboy1.y_dir = -1;
				cowboy1.x_dir = 0;	
			}
			if (ch == 'a')
			{
				cowboy1.isMoving = TRUE;
				if (cowboy1.state != 4)
				{cowboy1.state = 4;}
				else
				{cowboy1.state = 5;}
				cowboy1.y_dir = 0;
				cowboy1.x_dir = -1;	
			}
			if (ch == 's')
			{
				cowboy1.isMoving = TRUE;
				if (cowboy1.state != 1)
				{cowboy1.state = 1;}
				else
				{cowboy1.state = 2;}
				cowboy1.y_dir = 1;
				cowboy1.x_dir = 0;	
			}
			if (ch == 'd')
			{
				cowboy1.isMoving = TRUE;
				if (cowboy1.state != 7)
				{cowboy1.state = 7;}
				else
				{cowboy1.state = 8;}
				cowboy1.y_dir = 0;
				cowboy1.x_dir = 1;	
			}	
	
			if (ch == '8')
			{
				cowboy1.isFiring = TRUE;
				y_dir = -1;
				x_dir = 0;	
			}
			if (ch == '4')
			{
				cowboy1.isFiring = TRUE;
				y_dir = 0;
				x_dir = -1;	
			}
			if (ch == '2')
			{
				cowboy1.isFiring = TRUE;
				y_dir = 1;
				x_dir = 0;	
			}
			if (ch == '6')
			{
				cowboy1.isFiring = TRUE;
				y_dir = 0;
				x_dir = 1;	
			}	
			cowboy1.yFireDir = y_dir;
			cowboy1.xFireDir = x_dir;
			shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);

			render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
			for (i = 0; i < bullets_fill; i++) {
			clear_bitmap_8((UINT8 *) base, active_bullets[i].position.x, active_bullets[i].position.y, bullet_bitmap, BITMAP_8_HEIGHT);
			}
			/*move_bullets(&active_bullets[0], &bullets_fill);*/
			for (i = 0; i < snakes_fill; i++) {
			clear_bitmap_32((UINT32 *) base, active_snakes[i].position.x, active_snakes[i].position.y, blank, BITMAP_32_HEIGHT);
			}
			render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);
			time_now = get_time();
			time_delta = time_now - time_then;
			clear_bitmap_32((UINT32 *) base, cowboy1.position.x, cowboy1.position.y, blank, BITMAP_32_HEIGHT);
			move_cowboy(&cowboy1);
			render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
			move_snakes(active_snakes, snakes_fill, cowboy1);
			cowboy1.isMoving = FALSE;
			cowboy1.isFiring = FALSE;
			
			if(ch!='q')
				ch = NULL;
			
			/*if(time_delta >= 70) {
				if (count_sec < 30) {
				spawn_snakes(active_snakes, &snakes_fill, &seed);
				}  
				time_then = time_now;
			}*/
			if (count_sec > 30 && snakes_fill == 0) {
				/* wave complete */
				/* cowboy special move */
				count_sec = 0;
			}

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