#include <osbind.h>
#include "renderer.h"

int main()
{
  /* series of snapshots, press any key to move cowboy. Score and lives changes as well as the cowboys position */

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
  
  return 0;
}
