#include "isr.h"

int music_timer;
int game_timer;

int render_request = TRUE;
int render_mouse_request = FALSE;
int spawn_snake_request = FALSE;

int game_state = 0; /*states are 0 = splash, 1 = main game, 2 = game over*/

Vector vbl_vector;
Vector ikbd_vector;

volatile UINT8* const IKBD_Control = 0xfffc00;
volatile UINT8* const IKBD_Status = 0xfffc00;
volatile UINT8* const IKBD_RDR = 0xfffc02;
volatile UINT8* const ISRB_MFP_Register = 0xfffa11;
volatile UINT8* const ASCIITable = 0xFFFE829C;

UINT8 IKBD_buffer[IKBD_BUFFER_SIZE];
unsigned int buffer_head = 0;
unsigned int buffer_tail = 0;

int mouse_state = 0;
UINT8 mouse_button;
int mouse_delta_X;
int mouse_delta_Y;
int mouse_moved = FALSE;

int mouse_X = 0;
int mouse_Y = 0;
int mouse_left_click = FALSE;
int prev_mouse_X = 0;
int prev_mouse_Y = 0;


/********************************************************************************************
Function Name: 	vblisrC

Details: 	This function updates timer on VBL IRQ
			VBL ISR does following:
				• Times the flipping for double buffered graphics.
				• Times the playing of music.
				• Times when snakes should spawn
				• Provides a game timer for other times events

*********************************************************************************************/

void vblisrC()
{
	game_timer++;
	  
	render_request = TRUE;
	render_mouse_request = TRUE;
	
	if ((game_timer%35) == 0)
	{
		music_timer++;
	}
	
	if ((game_timer%70) == 0)
	{
		spawn_snake_request = TRUE;
	}
}

/********************************************************************************************
Function Name: 	ikbd_isr_c

Details: This function processes keyboard and mouse input on IKBD IRQ.

*********************************************************************************************/

void ikbdisrC() 
{
	SCANCODE scancode;
/*
	*IKBD_Control = ENABLE;
*/
	if (*IKBD_Status & 0x1) /* Check if data was received. */
	{
		scancode = *IKBD_RDR;
		if (mouse_state == MOUSE_STATE_FIRST_PACKET) 
		{      
			if (scancode == MOUSE_MOVE_CODE) /* Check if scancode is mouse event. */
			{
				mouse_button = scancode;
				mouse_state = MOUSE_STATE_DELTA_X;
				mouse_moved = scancode == MOUSE_MOVE_CODE;
			} 
			else if ((scancode & 0x80) == 0x00) /* Check if it is a make code. */
			{ 
				write_ikbd_buffer(scancode);
			} 
			else if ((scancode & 0x80) == 0x80) /* Check if it is a break code. */
			{ 
				write_ikbd_buffer(scancode);
			}
		} 
		else if (mouse_state == MOUSE_STATE_DELTA_X) 
		{ 
			mouse_state = MOUSE_STATE_DELTA_Y;
			mouse_delta_X = scancode;
			prev_mouse_X = mouse_X;
			mouse_X += mouse_delta_X;
		} 
		else if (mouse_state == MOUSE_STATE_DELTA_Y) 
		{ 
			mouse_state = MOUSE_STATE_FIRST_PACKET;
			mouse_delta_Y = scancode;
			prev_mouse_Y = mouse_Y;
			mouse_Y += mouse_delta_Y;
		}	
		mouse_check();

		*ISRB_MFP_Register &= MFB_BIT_6_MASK_OFF; /* Clears the 6th bit. */
	}
/*
	*IKBD_Control = DISABLE;
*/
}

/********************************************************************************************
Function Name: 	install_vectors

Details: This function installs vbl and ikbd vectors.

*********************************************************************************************/

void install_vectors() 
{
  vbl_vector = install_vector(VBL_VEC, vbl_isr);
  /*ikbd_vector = install_vector(IKBD_VEC, ikbd_isr);*/
}

/********************************************************************************************
Function Name: 	remove_vectors

Details: This function resets the vbl and ikbd vectors.

*********************************************************************************************/

void remove_vectors() 
{
  install_vector(VBL_VEC, vbl_vector);
  /*install_vector(IKBD_VEC, ikbd_vector);*/
}

/********************************************************************************************
Function Name: 	install_vector

Details: This function installs a vector at designated vector number.

*********************************************************************************************/

Vector install_vector(int num, Vector vector) 
{
	Vector orig;
	Vector* vect_ptr = (Vector *) ((long) num << 2);

	long old_ssp = Super(0);

	orig = *vect_ptr;
	*vect_ptr = vector;

	Super(old_ssp);
	return orig;
}

/********************************************************************************************
Function Name: 	ikbd_waiting

Details: This function checks if the keyboard is waiting for input.

*********************************************************************************************/

int ikbd_waiting() 
{
  return buffer_head != buffer_tail;
}

/********************************************************************************************
Function Name: 	ikbd_mouse_moved

Details: This function checks if mouse has moved.

*********************************************************************************************/

int ikbd_mouse_moved() 
{
  return mouse_moved;
}

/********************************************************************************************
Function Name: 	write_ikbd_buffer

Details: This function writes keyboard values to the keyboard buffer.

*********************************************************************************************/

void write_ikbd_buffer(UINT8 scancode) 
{
  if (buffer_tail == IKBD_BUFFER_SIZE - 1)
  {
    buffer_tail = 0;
  }

  IKBD_buffer[buffer_tail] = scancode;
  buffer_tail++;
}

/********************************************************************************************
Function Name: 	read_ikbd_buffer

Details: This function reads keyboard values from the keyboard buffer.

*********************************************************************************************/

UINT32 read_ikbd_buffer() 
{
  UINT32 ch;
  long old_ssp = Super(0);

  if (buffer_head == IKBD_BUFFER_SIZE - 1)
  {
    buffer_head = 0;
  }

  *ISRB_MFP_Register &= MFB_BIT_6_MASK_OFF;

  ch = IKBD_buffer[buffer_head];
  ch = ch << 16;
  ch = ch + *(ASCIITable + IKBD_buffer[buffer_head++]);

  *ISRB_MFP_Register |= MFB_BIT_6_MASK_ON; /* Turns the 6th but back on. */

  Super(old_ssp);
  return ch;
}

/********************************************************************************************
Function Name: 	read_ikbd_buffer

Details: This function clears the keyboard buffer.

*********************************************************************************************/

void clear_ikbd_buffer() {
  while(ikbd_waiting()) {
    buffer_head++;
  }

  IKBD_buffer[buffer_tail] = 0x00;
}

/********************************************************************************************
Function Name: 	mouse_check

Details: This function checks the bounds of the mouse cursor.

*********************************************************************************************/

void mouse_check()
{
	if(mouse_X > 624)
		mouse_X = 624;
	if(mouse_X < 0)
		mouse_X = 0;
	if(mouse_Y > 384)
		mouse_Y = 384;
	if(mouse_Y < 0)
		mouse_Y = 0;
}