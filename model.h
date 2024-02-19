#ifndef MODEL_H
#define MODEL_H

#define X_MIN 288
#define X_MAX 576
#define Y_MIN 32
#define Y_MAX 320
#define NULL 0
#define TRUE 1
#define FALSE 0

struct Position
{
UINT16 x;
UINT16 y;
};

struct Size
{
UINT16 height;
UINT16 width;
};

struct BoundingBox
{
struct Size size;
struct Position position;
};

struct Lives          /* type definition for lives object */
{
int lives_left;		  /* default starting lives = 3 */
struct Position position;        /* position coordinates (player 1 lives position begins at  (80,320)
                              player 2 lives position begins at  (80,252)) */
};

struct Scoreboard          /* type definition for score object */
{
UINT16 score;		  /* default initial score is 00000 */
char digit[5];		
struct Position position;        /* position coordinates (player 1 score position begins at  (80,300)
                              player 2 score position begins at  (80,232))*/
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
const UINT32* bitmap;
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
const UINT32* bitmap;
};

struct Model
{
struct Bullet bullet[MAX_BULLETS];
struct Cowboy cowboy;
struct Snake snake[MAX_SNAKES];
struct Scoreboard score;
struct Lives lives;
};

void init_bullet(struct Bullet active_bullets[], int *bullets_fill, int initial_x, int initial_y, int initial_x_dir, int initial_y_dir, int initial_speed);

void move_bullets(struct Bullet *bullet,struct Bullet *active_bullets, int *bullets_fill);

void move_snakes(struct Snake *snake, struct Cowboy *cowboy);

void move_cowboy(UINT32 *base, struct Cowboy *cowboy, const UINT32 *bitmap32);

void increase_score(struct Scoreboard *scoreboard,int value);

void wave_bonus(struct Scoreboard *scoreboard);

void decrement_lives (struct Cowboy *cowboy);

void respawn();

#endif
