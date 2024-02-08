
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

typedef struct             /* type definition for bullet object */
{
Position position;         /* position coordinates */
int delta_x, delta_y;      /* horiz. & vert. displacement per clock tick */
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
} Cowboy;

typedef struct 
{
Position position;
Size size;
int horizontalDirection;
int verticalDirection;
int horizontalVelocity;
int verticalVelocity;
Position target;
} Snake;
