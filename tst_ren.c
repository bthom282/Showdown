#include <osbind.h>
#include <stdio.h>
#include "model.h"
#include "renderer.h"
#include "events.h"

int main()
{
  /* series of snapshots, press any key to move cowboy. Score and lives changes as well as the cowboys position */
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
	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1 = init_Cowboy();

	struct Model model = {

	{424, 184, 32, 32, 0, 0, 4, FALSE, FALSE, 0, 0, 6, 0, 0, 0, 0, 0, 0, 80, 300, 3, 80, 320},

	};
		
	/*render initial state*/

	render((UINT32 *)base, &model, players, snakes_fill, bullets_fill);
	/*
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	cowboy1.state = 6;
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	*/
	render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);

	/*test rendering of different cowboy bitmaps*/
	
	Cnecin(); 
	
	clear_bitmap_32((UINT32 *) base, cowboy1.position.x, cowboy1.position.y, blank, BITMAP_32_HEIGHT);
	cowboy1.state = 9;
	
	Cnecin(); 

	fill_screen((UINT32 *) base, 0);

	increase_score(&cowboy1.scoreboard, 100);	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	cowboy1.state = 4;
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);

	render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);

	/*show snake movement*/
	
	cowboy1.isMoving = TRUE;
	cowboy1.y_dir = -1;
    cowboy1.x_dir = 1;
	
	for (i = 0; i < 40; i++)  {
		move_snakes(active_snakes, snakes_fill, cowboy1);
		move_cowboy(&cowboy1);
	}
	
	Cnecin(); 

	fill_screen((UINT32 *) base, 0);
	
	cowboy1.lives.lives_left = 2;
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	cowboy1.state = 11;
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	
	/*shows cowboy firing in all directions*/
	
	cowboy1.isFiring = TRUE;
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, &cowboy1, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);
	
	
	/*to show bullet movement*/
	move_bullets(active_bullets, &bullets_fill, active_snakes);
	move_bullets(active_bullets, &bullets_fill, active_snakes);
	move_bullets(active_bullets, &bullets_fill, active_snakes);
	move_bullets(active_bullets, &bullets_fill, active_snakes);
	move_bullets(active_bullets, &bullets_fill, active_snakes);
	
	Cnecin(); 
	
	cowboy1.lives.lives_left = 1;
	wave_bonus(&cowboy1.scoreboard);
	fill_screen((UINT32 *) base, 0);
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	cowboy1.state = 1;
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill, (UINT32 *) snake_bitmap);
	render_bullets((UINT8 *) base, active_bullets, (UINT8 *) bullet_bitmap, bullets_fill);

#ifdef FOO
	char *base = Physbase();
	UINT32 seed = 12345;
	int players = 1;
	struct Bullet active_bullets[MAX_BULLETS];  /*array for active bullet structs*/
	struct Snake active_snakes[MAX_SNAKES];    /*array for active snakes structs*/
	int bullets_fill = 0;
	int snakes_fill = 0;
	int i;
	char buffer[20];

	struct Cowboy cowboy1 = initializeCowboy();

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);

 	fill_screen((UINT32 *) base, 0);

	increase_score(&cowboy1.scoreboard, 100);
	cowboy1.lives.lives_left = 2;
	cowboy1.yFireDir = 0;
	cowboy1.xFireDir = 1;
	cowboy1.isFiring = TRUE;
	shooting((UINT8 *)base, &cowboy1, (UINT8 *)bullet_bitmap, active_bullets, &bullets_fill);
	
	cowboy1.position.x = 390; 
	cowboy1.position.y = 140;
	cowboy1.state = 4;
	cowboy1.yFireDir = 1;
	cowboy1.xFireDir = -1;
	cowboy1.isFiring = TRUE;
	shooting((UINT8 *)base, &cowboy1, (UINT8 *)bullet_bitmap, active_bullets, &bullets_fill);

	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	Cnecin(); 

	fill_screen((UINT32 *) base, 0); 
	
	cowboy1.position.x = 350; 
	cowboy1.position.y = 100;
	cowboy1.state = 3;
	wave_bonus(&cowboy1.scoreboard);
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1);
	render_snakes((UINT32 *) base, active_snakes, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill); 
	
	cowboy1.y_dir = 0;
  	cowboy1.x_dir = 1;
	cowboy1.isMoving = TRUE;
  #endif
  return 0;
}