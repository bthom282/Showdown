#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "effects.h"
#include "psg.h" 
#include "music.h"

/******CONSTANTS******/

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define X_MIN 288
#define X_MAX 575
#define Y_MIN 32
#define Y_MAX 320
#define BULLET_X_MIN 256
#define BULLET_X_MAX 632
#define BULLET_Y_MIN 0
#define BULLET_Y_MAX 380
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
#define WAVE_COUNT 30
#define PLAYER_1_START_X 424
#define PLAYER_1_START_Y 184
#define PLAYER_1_SCORE_X 80
#define PLAYER_1_SCORE_Y 300
#define PLAYER_1_LIVES_X 80
#define PLAYER_1_LIVES_Y 320
#define START_LIVES 3
#define TEXT_ALIGN 32
#define PLAYER_1_TEXT 280
#define PLAYER_1_SCORE_TEXT 300
#define PLAYER_1_LIVES_TEXT 320
#define PLAYER_2_TEXT 212
#define PLAYER_2_SCORE_TEXT 232
#define PLAYER_2_LIVES_TEXT 252

/******SPLASH CONSTANTS*****/

#define LETTER_HEIGHT 8
#define LETTER_WIDTH 8
#define ONE_PLAYER_GAME 1
#define TWO_PLAYER_GAME 2
#define EXIT 3
#define WAIT '0'
#define MENU_CLEAR_1 4
#define MENU_CLEAR_2 5
#define MENU_CLEAR_X 272
#define MENU_CLEAR_Y 200
#define MENU_CLEAR_HEIGHT 56
#define ANYKEY_X 272
#define ANYKEY_Y 224
#define ONE_X 288
#define ONE_Y 200
#define TWO_X 288
#define TWO_Y 216
#define SOON_X 272
#define SOON_Y 224
#define QUIT_X 308
#define QUIT_Y 240
#define CHOOSE_X 232
#define CHOOSE_Y 224
#define CURSOR_HEIGHT 64
#define CONFIRM_X 240
#define CONFIRM_Y 240
#define COWBOY_CURSOR_X 338
#define COWBOY_CURSOR_Y 285
#define COWGIRL_CURSOR_X 241
#define COWGIRL_CURSOR_Y 282

#define COWBOY_WRITING_X 408
#define COWBOY_WRITING_Y 308
#define COWGIRL_WRITING_X 176
#define COWGIRL_WRITING_Y 308

#define ARROW_ONE_X 280
#define ARROW_ONE_Y 200
#define ARROW_TWO_X 280
#define ARROW_TWO_Y 216
#define ARROW_QUIT_X 292
#define ARROW_QUIT_Y 240

/*EXTRA INFO FOR MOUSE CLICK COORDINATES*/
#define COWBOY_SPLASH_X 341
#define COWBOY_SPLASH_Y 284
#define COWBOY_SPLASH_HEIGHT 64
#define COWBOY_SPLASH_WIDTH 64
#define COWGIRL_SPLASH_X 244
#define COWGIRL_SPLASH_Y 284
#define COWGIRL_SPLASH_HEIGHT 64
#define COWGIRL_SPLASH_WIDTH 64
#define ANYKEY_LENGTH 104
#define ONE_LENGTH 64
#define TWO_LENGTH 64
#define QUIT_LENGTH 40
#define CONFIRM_LENGTH 274

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
int avatar; /*0 = cowboy, 1 = cowgirl*/	   
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

void move_snakes(struct Snake active_snakes[], int snakes_fill, const struct Cowboy *cowboy);

void move_cowboy(struct Cowboy *cowboy);

void increase_score(struct Scoreboard *scoreboard,int value);

void decrement_lives (struct Cowboy *cowboy);

void respawn();

void process_synchronous(struct Model *model);

struct Model init_Model();

struct Cowboy init_Cowboy();

struct Snake init_Snake(int x_p, int y_p, int x_d, int y_d, int s);

struct Bullet init_Bullet(int x_pos, int y_pos, int x_dir, int y_dir);

#endif
