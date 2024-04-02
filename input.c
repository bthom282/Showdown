#include "input.h"

/********************************************************************************************
Function Name: 	input_handler

Details: 	When a keypress is sensed, the char inputted is passed to the input handler for
			interpretation.

*********************************************************************************************/

void input_handler(char input, struct Model *model, int *quit)
{
	int y_dir;
	int x_dir;
	char ch = input;
	
	if (ch == 'q')
	{
		quit = TRUE;
	}
	
	if (ch == 'w')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 10)
		{model->cowboy.state = 10;}
		else
		{model->cowboy.state = 11;}
		model->cowboy.y_dir = -1;
		model->cowboy.x_dir = 0;	
	}
	if (ch == 'a')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 4)
		{model->cowboy.state = 4;}
		else
		{model->cowboy.state = 5;}
		model->cowboy.y_dir = 0;
		model->cowboy.x_dir = -1;	
	}
	if (ch == 's')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 1)
		{model->cowboy.state = 1;}
		else
		{model->cowboy.state = 2;}
		model->cowboy.y_dir = 1;
		model->cowboy.x_dir = 0;	
	}
	if (ch == 'd')
	{
		model->cowboy.isMoving = TRUE;
		if (model->cowboy.state != 7)
		{model->cowboy.state = 7;}
		else
		{model->cowboy.state = 8;}
		model->cowboy.y_dir = 0;
		model->cowboy.x_dir = 1;	
	}	

	if (ch == '8')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = -1;
		x_dir = 0;	
	}
	if (ch == '4')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 0;
		x_dir = -1;	
	}
	if (ch == '5')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 1;
		x_dir = 0;	
	}
	if (ch == '6')
	{
		model->cowboy.isFiring = TRUE;
		y_dir = 0;
		x_dir = 1;	
	}	
	model->cowboy.yFireDir = y_dir;
	model->cowboy.xFireDir = x_dir;
}