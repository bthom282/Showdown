#include "model.h"
#include "osbind.h"

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
