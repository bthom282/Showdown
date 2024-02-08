
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
Position position;        /* position coordinates */
BoundingBox boundingBox;
} Lives;

typedef struct            /* type definition for score object */
{
int score;
Position position;        /* position coordinates */
BoundingBox boundingBox;
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
Position position;        /* position coordinates */
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
Position position;          /* position coordinates */
Size size;
int horizontalDirection;    /* direction the snake is facing*/
int verticalDirection;
int horizontalVelocity;    /* horiz. & vert. displacement per clock tick */
int verticalVelocity;
Position target;
BoundingBox boundingBox;
} Snake;
