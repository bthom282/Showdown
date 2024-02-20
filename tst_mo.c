#include <stdio.h>
#include <osbind.h>
#include "types.h"
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "raster.h"
#include "font.h"
#include "bitmaps.h"

struct Cowboy initializeCowboy() {
    struct Cowboy cowboy;

    cowboy.position.x = 424;
    cowboy.position.y = 184;
    cowboy.size.height = 16;
    cowboy.size.width = 16;
    cowboy.y_dir = 0;
    cowboy.x_dir = 0;
    cowboy.speed = 2;
    cowboy.isMoving = FALSE;
    cowboy.isFiring = FALSE;
    cowboy.yFireDir = 0;
    cowboy.xFireDir = 0;
    cowboy.state = 0;
	cowboy.scoreboard.score = 0;
    cowboy.scoreboard.position.x = 80;
    cowboy.scoreboard.position.y = 300;
	cowboy.lives.lives_left = 3;
    cowboy.lives.position.x = 80;
    cowboy.lives.position.y = 320;
	cowboy.boundingBox.top = cowboy.position.y;
    cowboy.boundingBox.bottom = cowboy.position.y + cowboy.size.height;
    cowboy.boundingBox.left = cowboy.position.x;
    cowboy.boundingBox.right = cowboy.position.x + cowboy.size.width;
	cowboy.bitmap = cowboy_bitmap;

	return cowboy;
}

int main()
{
/* black screen displaying cowboy movement, press any key to move cowboy */

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

	fill_screen((UINT32 *) base, -1);
	
	sprintf(buffer, "cowboy x = %d", cowboy1.position.x);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 340);
	sprintf(buffer, "cowboy y = %d", cowboy1.position.y);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 360);
	
	cowboy1.y_dir = 0;
    cowboy1.x_dir = 1;
	cowboy1.isMoving = TRUE;
	
	Cnecin(); 
	fill_screen((UINT32 *) base, -1);
	move_cowboy(&cowboy1);
	sprintf(buffer, "cowboy x = %d", cowboy1.position.x);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 340);
	sprintf(buffer, "cowboy y = %d", cowboy1.position.y);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 360);
	
	Cnecin(); 
	fill_screen((UINT32 *) base, -1);
	move_cowboy(&cowboy1);
	sprintf(buffer, "cowboy x = %d", cowboy1.position.x);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 340);
	sprintf(buffer, "cowboy y = %d", cowboy1.position.y);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 360);
	
	Cnecin(); 
	fill_screen((UINT32 *) base, -1);
	move_cowboy(&cowboy1);
	sprintf(buffer, "cowboy x = %d", cowboy1.position.x);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 340);
	sprintf(buffer, "cowboy y = %d", cowboy1.position.y);
	print_message((UINT8 *)base, (UINT8 *)buffer, 32, 360);

	Cnecin(); 
  
  return 0;
}
