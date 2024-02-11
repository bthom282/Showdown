#include "model.h"

void move_bullet(Bullet *bullet)
{
  bullet->x += bullet->delta_x;
  bullet->y += bullet->delta_y;
}
