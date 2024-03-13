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
	int i;

	struct Model model = init_Model();

	/*struct Model testModelSnapshot = {

	{},
	{},
	{},
	{},
	{},
	{}

	};*/
		
	/*render initial state*/

	render((UINT32 *)base, &model); 

	model.cowboy.state = 6;
	
	/*test rendering of different cowboy bitmaps*/
	
	Cnecin(); 
	
	clear_bitmap_32((UINT32 *) base, model.cowboy.position.x, model.cowboy.position.y, blank, BITMAP_32_HEIGHT);
	model.cowboy.state = 9;
	
	Cnecin(); 

	fill_screen((UINT32 *) base, 0);
	model.cowboy.state = 4;
	increase_score(&model.cowboy.scoreboard, 100);	

	spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
	spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
	spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);
	spawn_snakes(model.active_snakes, &model.snakes_fill, &seed);

	/*show snake movement*/
	
	model.cowboy.isMoving = TRUE;
	model.cowboy.y_dir = -1;
    model.cowboy.x_dir = 1;
	
	for (i = 0; i < 40; i++)  {
		move_snakes(model.active_snakes, model.snakes_fill, model.cowboy);
		move_cowboy(&model.cowboy);
	}

	render((UINT32 *)base, &model);
	
	Cnecin(); 

	fill_screen((UINT32 *) base, 0);
	
	model.cowboy.lives.lives_left = 2;
	
	model.cowboy.state = 11;
	
	/*shows cowboy firing in all directions*/
	
	model.cowboy.isFiring = TRUE;
	model.cowboy.yFireDir = -1;
    model.cowboy.xFireDir = -1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = 0;
    model.cowboy.xFireDir = -1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = 1;
    model.cowboy.xFireDir = -1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = -1;
    model.cowboy.xFireDir = 0;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = 1;
    model.cowboy.xFireDir = 1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/
	
	model.cowboy.yFireDir = 0;
    model.cowboy.xFireDir = 1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = -1;
    model.cowboy.xFireDir = 1;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	/*render((UINT32 *)base, &model);*/

	model.cowboy.yFireDir = -1;
    model.cowboy.xFireDir = 0;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	
	model.cowboy.yFireDir = 1;
    model.cowboy.xFireDir = 0;
	shooting((UINT8 *) base, &model.cowboy, model.active_bullets, &model.bullets_fill);
	
	
	render((UINT32 *)base, &model);

	/*to show bullet movement*/
	move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes);
	move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes);
	move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes);
	move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes);
	move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes);
	
	Cnecin(); 
	
	model.cowboy.lives.lives_left = 1;
	wave_bonus(&model.cowboy.scoreboard);
	fill_screen((UINT32 *) base, 0);
	
	model.cowboy.state = 1;
	
	render((UINT32 *)base, &model);


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