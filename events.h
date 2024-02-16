
int checkCollision(BoundingBox box1, BoundingBox box2);

void shooting(UINT8 *base, struct Cowboy *cowboy, const UINT8 *bitmap8, 
				struct Bullet *active_bullets, int *bullets_fill);

unsigned int randInRange(unsigned long *seed, unsigned int min, unsigned int max);

void spawn_snakes(UINT32 *base, struct Snake *active_snakes, int spawn_x[], int spawn_y[], int *snakes_fill, UINT32 *seed);
