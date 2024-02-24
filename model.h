#ifndef MODEL_H
#define MODEL_H

/******CONSTANTS******/

#define BITMAP_HEIGHT 16
#define BITMAP_8_HEIGHT 8
#define BITMAP_32_HEIGHT 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define X_MIN 288
#define X_MAX 575
#define Y_MIN 32
#define Y_MAX 320
#define NULL 0
#define TRUE 1
#define FALSE 0
#define MAX_BULLETS 20
#define MAX_SNAKES 30
#define MAX_SPAWN_LOC 16
#define TEXT_X 32
#define ONE_SCORE_Y 232
#define TWO_SCORE_Y 300
#define TWO_LIVES_Y 252
#define TWO_LIVES_Y 320
#define ONE_Y 212
#define TWO_Y 280
#define MAX_BULLETS 20
#define MAX_SNAKES 30
#define BYTES_PER_SCREEN 32000
#define WORDS_PER_SCREEN 16000
#define LONGS_PER_SCREEN 8000
#define BITMAP_HEIGHT 16
#define BITMAP_8_HEIGHT 8
#define BITMAP_32_HEIGHT 32
#define CLEAR32 0x00000000
#define BULLET_SPEED 3

struct Position
{
int x;
int y;
};

struct Size
{
int height;
int width;
};

struct BoundingBox
{
    int top;
    int bottom;
    int left;
    int right;
};

struct Lives          /* type definition for lives object */
{
int lives_left;		  /* default starting lives = 3 */
struct Position position;        /* position coordinates (player 1 lives position begins at  (80,320)
                              player 2 lives position begins at  (80,252)) */
};

struct Scoreboard          /* type definition for score object */
{
int score;		  /* default initial score is 00000 */
char digit[5];		
struct Position position;
};

struct Bullet           /* type definition for bullet object */
{
struct Position position;         /* position coordinates */
int y_dir, x_dir;	   /* horiz. & vert. direction for displacement */
			   /* x = -1 (traveling left), x = 1 (traveling right),
      			      y = -1 (traveling up), y = 1 (traveling down) */
int speed;      	   /* displacement per clock tick for x and y displacement*/
struct BoundingBox boundingBox;
};

struct Cowboy         /* type definition for cowboy object */
{
struct Position position;	/* position coordinates, 1 player cowboy's initial position is (424, 184) */
struct 	Size size;
int y_dir; 	   		/* direction the cowboy is facing for displacement */
int x_dir;			/* x = -1 (traveling left), x = 1 (traveling right),
				y = -1 (traveling up), y = 1 (traveling down) */
int speed;		   /* displacement per clock tick for x and y displacement*/
int isMoving;
int isFiring;
int yFireDir;	/*fire_x = 1 & fire_y = 0 = firing right, fire_x = 1 & fire_y = 1 = firing 45 degree angle towards bottom right */
int xFireDir;	/*fire_x = 0 & fire_y = 1 = firing down, fire_x = -1 & fire_y = 1 = firing 45 degree angle towards bottom left */
		/*fire_x = -1 & fire_y = 0 = firing left, fire_x = -1 & fire_y = -1 = firing 45 degree angle towards top left*/
    		/*fire_x = 0 & fire_y = -1 = firing up, fire_x = 1 & fire_y = -1 = firing 45 degree angle towards top right */
int state; 		 /* state used for bitmap printing {0 - not moving, 1 & 2 (alternating) - moving down
							    3 - moving right, 4 - moving left, 5 moving up} */
struct Scoreboard scoreboard;		  
struct Lives lives;		   
struct BoundingBox boundingBox;
const unsigned long bitmap;
};

struct Snake           /* type definition for snake object */
{
struct Position position;         /* position coordinates, snakes initially spawn in locations based on a randomizer */
	                         /* 16 spawn coordinates = {(384,0),(416,0),(448,0),(480,0),
								                              (256,128),(256,160),(256,192),(256,224),
								                              (608,128),(608,160),(608,192),(608,224),
								                              (384,352),(416,352),(448,352),(480,352)} */
struct Size size;
int horizontalDirection;    /* direction the snake is facing*/
int verticalDirection;
int horizontalVelocity;    /* horiz. & vert. displacement per clock tick */
int verticalVelocity;
struct Position target;
int state; 		   /* state used for bitmap printing {0 - not moving/ moving down, 1 - moving left
							      2 - moving right, 3 - moving up} */
struct BoundingBox boundingBox;
const unsigned long *bitmap;
};

struct Model
{
struct Bullet bullet[MAX_BULLETS];
struct Cowboy cowboy;
struct Snake snake[MAX_SNAKES];
struct Scoreboard score;
struct Lives lives;
};

void move_bullets(struct Bullet active_bullets[], int *bullets_fill);

void move_snakes(struct Snake active_snakes[], int snakes_fill, const struct Cowboy *cowboy);

struct Cowboy initializeCowboy();

void move_cowboy(struct Cowboy *cowboy);

void increase_score(struct Scoreboard *scoreboard,int value);

void wave_bonus(struct Scoreboard *scoreboard);

void decrement_lives (struct Cowboy *cowboy);

void respawn();

struct Cowboy init_Cowboy();

struct Snake init_Snake(int x_p, int y_p, int x_d, int y_d, int s);

struct Bullet init_Bullet(int *bullets_fill, int x_pos, int y_pos, int x_dir, int y_dir);

#endif
