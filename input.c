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

/********************************************************************************************
Function Name: 	check_input

Details: 	This function check to see if there is keypress input to read.

*********************************************************************************************/

int check_input()
{
	int has_input = FALSE;
	
	if (ikbd_waiting())
		has_input = TRUE;
	
	return has_input;
}

/********************************************************************************************
Function Name: 	get_input

Details: 	This function retrieves the next input in the buffer.

*********************************************************************************************/

UINT32 get_input()
{
	UINT32 input;
	
	input = read_ikbd_buffer();
	
	return input;
}

/********************************************************************************************
Function Name: 	check_mouse_input

Details: 	This function checks to see if the user has moved the mouse.

*********************************************************************************************/

int check_mouse_input()
{
	int has_input = FALSE;
	
	if (ikbd_mouse_moved())
		has_input = TRUE;
	
	return has_input;
}
