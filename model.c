#include "model.h"

void move_bullet(Bullet *bullet)
{
  ball->x += ball->delta_x;
  ball->y += ball->delta_y;
}
