#define X_MIN 288
#define X_MAX 576
#define Y_MIN 32
#define Y_MAX 320
#define NULL 0
#define TRUE 1
#define FALSE 0
#define MAX_BULLETS 20
#define MAX_SNAKES 30

void move_bullet(Bullet *bullet);

void delete_bullet (Bullet *bullet, int index);

void move_snake(Snake *snake);

void snake_death(Snake *snake, int index);

void move_cowboy(Cowboy *cowboy);

void cowboy_death (int *lives_count);

void update_lives (UINT8 *base, int lives_count);

void respawn();

void game_over((UINT8 *)base, bool isPlaying);

void game_quit(bool *isPlaying);

void print_message(UINT8 *base, char message[], int x_pos, int y_pos);

typedef struct Model
{ /* to be continued...*/
Bullet bullet[MAX_BULLETS];
Cowboy cowboy;
Snake snake[MAX_SNAKES];
Score score;
Lives lives;
};

typedef struct Position
{
unsigned int x;
unsigned int y;
};

typedef struct Size
{
int height;
int width;
};

typedef struct BoundingBox
{
Size size;
Position position;
};

typedef struct Lives          /* type definition for lives object */
{
int lives;		  /* default starting lives = 3 */
Position position;        /* position coordinates (player 1 lives position begins at  (80,320)
                              player 2 lives position begins at  (80,252)) */
};

typedef struct Score          /* type definition for score object */
{
int score;		  /* default initial score is 00000 */
Position position;        /* position coordinates (player 1 lives position begins at  (80,300)
                              player 2 lives position begins at  (80,232))*/
};

typedef struct Bullet           /* type definition for bullet object */
{
Position position;         /* position coordinates */
int y_dir, x_dir;	   /* horiz. & vert. direction for displacement */
			   /* x = -1 (traveling left), x = 1 (traveling right),
      			      y = -1 (traveling up), y = 1 (traveling down) */
int speed = 3;      	   /* displacement per clock tick for x and y displacement*/
BoundingBox boundingBox;
};

typedef struct Cowboy            /* type definition for cowboy object */
{
Position position;        /* position coordinates, 1 player cowboy's initial position is (424, 184) */
Size size;
int horizontalDirection;   
int verticalDirection;
int y_dir, x_dir;	   /* direction the cowboy is facing for displacement */
			   /* x = -1 (traveling left), x = 1 (traveling right),
      			      y = -1 (traveling up), y = 1 (traveling down) */
int speed = 2;		   /* displacement per clock tick for x and y displacement*/
int horizontalVelocity;    /* horiz. & vert. displacement per clock tick */
int verticalVelocity;
bool isMoving;
bool isFiring;
int verticalFiringDirection;	/*fire_x = 1 & fire_y = 0 = firing right, fire_x = 1 & fire_y = 1 = firing 45 degree angle towards bottom right */
int horizontalFiringDirection;	/*fire_x = 0 & fire_y = 1 = firing down, fire_x = -1 & fire_y = 1 = firing 45 degree angle towards bottom left */
				/*fire_x = -1 & fire_y = 0 = firing left, fire_x = -1 & fire_y = -1 = firing 45 degree angle towards top left*/
    				/*fire_x = 0 & fire_y = -1 = firing up, fire_x = 1 & fire_y = -1 = firing 45 degree angle towards top right */
int state; 		        /* state used for bitmap printing {0 - not moving, 1 & 2 (alternating) - moving down
							           3 - moving right, 4 - moving left, 5 moving up} 
	     						           example: cowboy_bitmap[state*32]*/
Score score;		   /* default initial score is 00000 */
Lives lives;		   /* default starting lives = 3 */
BoundingBox boundingBox;
const UINT32 bitmap = cowboy_bitmap;
};

typedef struct Snake           /* type definition for snake object */
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
int state; 		   /* state used for bitmap printing {0 - not moving/ moving down, 1 - moving left
							      2 - moving right, 3 - moving up} */
BoundingBox boundingBox;
int isDead;
const UINT32 bitmap = snake_bitmap;
};
