/*Modelling*/

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

	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1 = init_Cowboy();

	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);

	/*show snake spawning*/
	
	printf("Snakes fill: %d\n", snakes_fill);
	
	/*show snake movement*/
	
	for (i = 0; i < snakes_fill; i++) {
		printf("Snakes position x: %d\n", active_snakes[i].position.x);
		printf("Snakes position y: %d\n", active_snakes[i].position.y);
	}
	
	move_snakes(&active_snakes[0], snakes_fill, &cowboy1);
	
	for (i = 0; i < snakes_fill; i++) {
		printf("Snakes position x: %d\n", active_snakes[i].position.x);
		printf("Snakes position y: %d\n", active_snakes[i].position.y);
	}
	
	move_snakes(&active_snakes[0], snakes_fill, &cowboy1);
	
	for (i = 0; i < snakes_fill; i++) {
		printf("Snake position x: %d\n", active_snakes[i].position.x);
		printf("Snake position y: %d\n", active_snakes[i].position.y);
	}
	
	/* show firing of bulets */
	
	cowboy1.isFiring = TRUE;
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);

	for (i = 0; i < bullets_fill; i++) {
		printf("Bullet position x: %d\n", active_bullets[i].position.x);
		printf("Bullet position y: %d\n", active_bullets[i].position.y);
	}
	
	/*to show bullet movement*/
	
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	for (i = 0; i < bullets_fill; i++) {
		printf("Bullet position x: %d\n", active_bullets[i].position.x);
		printf("Bullet position y: %d\n", active_bullets[i].position.y);
	}
	

/*With Rendering*/

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
	
	/*initializing the player1 cowboy*/
	struct Cowboy cowboy1 = init_Cowboy();
	
	/*render initial state*/
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, active_snakes, (UINT32 *) snake_bitmap, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	/*test rendering of different cowboy bitmaps*/
	
	clear_bitmap_32((UINT32 *) base, cowboy1.position.x, cowboy1.position.y, blank, BITMAP_32_HEIGHT);
	cowboy1.state = 9;
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);
	spawn_snakes(active_snakes, &snakes_fill, &seed);

	render_snakes((UINT32 *) base, active_snakes, (UINT32 *) snake_bitmap, snakes_fill);
	
	/*show snake movement*/
	
	for (i = 0; i < 20; i++)  {
		move_snakes(&active_snakes[0], snakes_fill, &cowboy1);
	}
	
	fill_screen((UINT32 *) base, -1);
	
	render_side_panel((UINT16 *)base);
	render_side_text((UINT8 *) base, players);
	render_score((UINT8 *) base, &cowboy1.scoreboard);
	render_lives((UINT16 *) base, cowboy1.lives, cowboy_lives);
	render_level1((UINT32 *) base, (UINT32 *) cactus_bitmap);
	render_cowboy((UINT32 *) base, cowboy1, (UINT32 *) cowboy_bitmap);
	render_snakes((UINT32 *) base, active_snakes, (UINT32 *) snake_bitmap, snakes_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	/*shows cowboy firing in all directions*/
	
	cowboy1.isFiring = TRUE;
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = -1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = 0;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 1;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	cowboy1.yFireDir = -1;
    cowboy1.xFireDir = 0;
	shooting((UINT8 *) base, cowboy1, bullet_bitmap, active_bullets, &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
	
	
	/*to show bullet movement*/
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	move_bullets(&active_bullets[0], &bullets_fill);
	render_bullets((UINT8 *) base, active_bullets, bullet_bitmap, bullets_fill);
