#include "model.h"

void move_bullet(Bullet *bullet)
{
  bullet->x += bullet->delta_x;
  bullet->y += bullet->delta_y;
}

void move_snake(Snake *snake)
{

}

void move_cowboy(Cowboy *cowboy)
{

}

void game_over()
{

}

void game_quit()
{

}

void print_message(UINT8 *base, char message[], int x_pos, int y_pos) {
	int i = 0;
	if (x_pos >= 0 && x_pos < SCREEN_WIDTH && y_pos >= 0 && y_pos < SCREEN_HEIGHT) {
		while (message[i] != '\0') {
			plot_char((UINT8 *) base, x_pos, y_pos, message[i]);
			x_pos += 8;
			i++;
		}
	}
}
