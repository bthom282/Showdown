#include <stdio.h>
#include <osbind.h>
#include <assert.h>
#include "types.h"
#include "model.h"
#include "events.h"
#include "renderer.h"
#include "raster.h"
#include "bitmaps.h"
#include "psg.h" 
#include "music.h" 
#include "effects.h"
#include "input.h"

int main()
{
/* black screen displaying cowboy movement, press any key to move cowboy */

	int avatar = 0;

	struct Model model = init_Model(avatar);

	printf("Stage 3 Model/Events Testing: Press any key\n\n");
	
	Cnecin();
	
	printf("No Collision detected test\n");
	/* Print initial state */
    printf("Initial Cowboy position: (%d, %d)\n", model.cowboy.position.x, model.cowboy.position.y);
    printf("Initial Cowboy score: %d\n", model.cowboy.scoreboard.score);

    /* Move cowboy */
    model.cowboy.isMoving = TRUE;
    model.cowboy.x_dir = 1;
    model.cowboy.y_dir = 0;
    process_synchronous(&model); /* Move cowboy*/

    /* Print updated state */
    printf("Updated Cowboy position: (%d, %d)\n", model.cowboy.position.x, model.cowboy.position.y);

    /* Fire bullet */
    model.cowboy.isFiring = TRUE;
    model.cowboy.xFireDir = 0;
    model.cowboy.yFireDir = -1;
    process_synchronous(&model); /* Fire bullet*/

    /* Print updated state */
    printf("Active Bullets: %d\n", model.bullets_fill);

    /* Move bullets */
    move_bullets(model.active_bullets, &model.bullets_fill, model.active_snakes, &model.snakes_fill, &model.cowboy);

    /* Print updated state */
    printf("Updated Bullet position: (%d, %d)\n", model.active_bullets[0].position.x, model.active_bullets[0].position.y);

    /* Move snakes */
    move_snakes(model.active_snakes, model.snakes_fill, &model.cowboy);

    /* Print updated state */
    printf("Updated Snake position: (%d, %d)\n", model.active_snakes[0].position.x, model.active_snakes[0].position.y);

    

	/* Check for collision between bullet and snake */
    if (checkCollision(model.active_bullets[0].position.x, model.active_bullets[0].position.y, BULLET_WIDTH, BULLET_HEIGHT,
                       model.active_snakes[0].position.x, model.active_snakes[0].position.y, SNAKE_WIDTH, SNAKE_HEIGHT)) {
        printf("Collision detected between bullet and snake!\n");
        /* Handle collision - remove bullet and snake */
        delete_bullet(model.active_bullets, &model.bullets_fill, 0);
        snake_death(model.active_snakes, 0, &model.snakes_fill);
        printf("Updated Bullet count: %d\n", model.bullets_fill);
        printf("Updated Snake count: %d\n", model.snakes_fill);
    } else {
        printf("No collision detected between bullet and snake.\n\n");
    }

	/* Wait for input */
		Cnecin();
	printf("Collision detected test\n");

	 /* Initialize snake position */
    model.active_snakes[0] = init_Snake(300, 200, 0, 0, 0); /* Snake positioned near the cowboy's firing direction*/
	model.active_bullets[0] = init_Bullet(300, 200, 0, 0);

    /* Print initial snake position */
    printf("Initial Snake position: (%d, %d)\n", model.active_snakes[0].position.x, model.active_snakes[0].position.y);

    /* Fire bullet towards the snake */
    model.cowboy.isFiring = TRUE;
    model.cowboy.xFireDir = 1;
    model.cowboy.yFireDir = 0;

    /* Move cowboy and fire bullet */
    process_synchronous(&model);

    /* Print updated bullet and snake positions */
    printf("Updated Cowboy position: (%d, %d)\n", model.cowboy.position.x, model.cowboy.position.y);
    printf("Updated Bullet position: (%d, %d)\n", model.active_bullets[0].position.x, model.active_bullets[0].position.y);
    printf("Updated Snake position: (%d, %d)\n", model.active_snakes[0].position.x, model.active_snakes[0].position.y);

    /* Check for collision between bullet and snake */
    if (checkCollision(model.active_bullets[0].position.x, model.active_bullets[0].position.y, BULLET_WIDTH, BULLET_HEIGHT,
                       model.active_snakes[0].position.x, model.active_snakes[0].position.y, SNAKE_WIDTH, SNAKE_HEIGHT)) {
        printf("Collision detected between bullet and snake!\n");
        /* Handle collision - remove bullet and snake */
        delete_bullet(model.active_bullets, &model.bullets_fill, 0);
        snake_death(model.active_snakes, 0, &model.snakes_fill);
        printf("Updated Snake count: %d\n", model.snakes_fill);
    } else {
        printf("No collision detected between bullet and snake.\n");
    }

	

  return 0;
  
}
