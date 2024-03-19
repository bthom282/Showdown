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
#define BULLET_SPEED 20
#define COWBOY_SPEED 10
#define SNAKE_WIDTH 32
#define SNAKE_HEIGHT 32
#define COWBOY_WIDTH 32
#define COWBOY_HEIGHT 32
#define BULLET_WIDTH 4
#define BULLET_HEIGHT 4

struct Position
{
int x;
int y;
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
int isRendered;
};

struct Bullet           /* type definition for bullet object */
{
struct Position position;         /* position coordinates */
int y_dir, x_dir;	   /* horiz. & vert. direction for displacement */
			   /* x = -1 (traveling left), x = 1 (traveling right),
      			      y = -1 (traveling up), y = 1 (traveling down) */
int speed;      	   /* displacement per clock tick for x and y displacement*/

/* just have a postion and velocity, compute the bounding box and not have speed*/
};

struct Cowboy         /* type definition for cowboy object */
{
struct Position position;	/* position coordinates, 1 player cowboy's initial position is (424, 184) */
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
};

struct Snake           /* type definition for snake object */
{
struct Position position;         
int y_dir;    		
int x_dir;
int state; 		   /* state used for bitmap printing {0 - not moving/ moving down, 1 - moving left
							      2 - moving right, 3 - moving up} */
};

struct Model
{
int players;
int bullets_fill;
int snakes_fill;
struct Cowboy cowboy;
struct Snake active_snakes[MAX_SNAKES];
struct Bullet active_bullets[MAX_BULLETS];
};

void move_bullets(struct Bullet active_bullets[], int *bullets_fill, struct Snake active_snakes[], 
	int *snakes_fill, const struct Cowboy *cowboy);

void move_bullet(struct Bullet *bullet, struct Bullet active_bullets[], int index, int *bullets_fill, 
				struct Snake active_snakes[], int *snakes_fill, const struct Cowboy *cowboy);

void move_snakes(struct Snake active_snakes[], int snakes_fill, const struct Cowboy *cowboy);

void move_snake(struct Snake *snake, const struct Cowboy *cowboy);

void move_cowboy(struct Cowboy *cowboy);

void increase_score(struct Scoreboard *scoreboard,int value);

void wave_bonus(struct Scoreboard *scoreboard);

void decrement_lives (struct Cowboy *cowboy);

void respawn();

struct Model init_Model();

struct Cowboy init_Cowboy();

struct Snake init_Snake(int x_p, int y_p, int x_d, int y_d, int s);

struct Bullet init_Bullet(int x_pos, int y_pos, int x_dir, int y_dir);

#endif
