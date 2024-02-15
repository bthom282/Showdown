#define X_MIN 288
#define X_MAX 576
#define Y_MIN 32
#define Y_MAX 320

void move_bullet(Bullet *bullet);

void move_snake(Snake *snake);

void move_cowboy(Cowboy *cowboy);

void cowboy_death (int *lives_count);

void update_lives (UINT8 *base, int lives_count);

void respawn();

void game_over((UINT8 *)base, bool isPlaying);

void game_quit(bool *isPlaying);

void print_message(UINT8 *base, char message[], int x_pos, int y_pos);

typedef struct 
{
unsigned int x;
unsigned int y;
} Position;

typedef struct 
{
int height;
int width;
} Size;

typedef struct 
{
Position position;
Size size; 
} BoundingBox;

typedef struct            /* type definition for lives object */
{
int lives;
Position position;        /* position coordinates (player 1 lives position begins at  (80,320)
                              player 2 lives position begins at  (80,252)) */
} Lives;

typedef struct            /* type definition for score object */
{
int score;
Position position;        /* position coordinates (player 1 lives position begins at  (80,300)
                              player 2 lives position begins at  (80,232))*/
} Score;

typedef struct            /* type definition for cactus object */
{
Position position;         /* position coordinates */
BoundingBox boundingBox;
} Cactus;

typedef struct             /* type definition for bullet object */
{
Position position;         /* position coordinates */
int delta_x, delta_y;      /* horiz. & vert. displacement per clock tick */
BoundingBox boundingBox;
} Bullet;

typedef struct             /* type definition for cowboy object */
{
Position position;        /* position coordinates, 1 player cowboy's initial position is (424, 184) */
Size size;
int horizontalDirection;   /* direction the cowboy is facing*/
int verticalDirection;
int horizontalVelocity;    /* horiz. & vert. displacement per clock tick */
int verticalVelocity;
bool isMoving;
bool isFiring;
int verticalFiringDirection;
int horizontalFiringDirection;
BoundingBox boundingBox;
} Cowboy;

typedef struct             /* type definition for snake object */
{
Position position;         /* position coordinates, snakes initially spawn in locations based on a randomizer */
	                         /* 16 spawn coordinates = {(384,0),(416,0),(448,0),(480,0),
								                              (256,128),(256,160),(256,192),(256,224),
								                              (608,128),(608,160),(608,192),(608,224),
								                              (384,352),(416,352),(448,352),(480,352)} */
Size size;
int horizontalDirection;    /* direction the snake is facing*/
int verticalDirection;
int horizontalVelocity;    /* horiz. & vert. displacement per clock tick */
int verticalVelocity;
Position target;
BoundingBox boundingBox;
int isDead;
} Snake;
