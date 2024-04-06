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
UINT8 repeated_key = 0;

int mouseState = 0;
UINT8 mouse_button;
UINT8 mouse_delta_X;
UINT8 mouse_delta_Y;
int key_repeat = FALSE;
int mouse_moved = FALSE;

int mouse_X = 0;
int mouse_Y = 0;
int mouse_left_click = FALSE;
int prev_mouse_X = 0;
int prev_mouse_Y = 0;


void vblisrC()
{
	music_timer++;
	game_timer++;
	  
	render_request = TRUE;
	render_mouse_request = TRUE;
	
	if ((game_timer%70) == 0)
	{
		spawn_snake_request = TRUE;
	}
}

/*void ikbd_isr_c() 
{
  UINT8 scancode;

  *IKBD_Control = ENABLE;

  if (*IKBD_Status & 0x1)*/ /* Check if data was received. */
  /*{
    scancode = *IKBD_RDR;
    if (mouse_state == MOUSE_STATE_FIRST_PACKET) 
	{      
      if (scancode >= MOUSE_MOVE_CODE) *//* Check if scancode is mouse event. */
	  /*{
        mouse_button = scancode;
        mouse_state = MOUSE_STATE_DELTA_X;
        mouse_moved = scancode == MOUSE_MOVE_CODE;
      } 
	  else if ((scancode & 0x80) == 0x00)*/ /* Check if it is a make code. */
	  /*{ 
        write_ikbd_buffer(scancode);
        key_repeat = TRUE;
      } 
	  else if ((scancode & 0x80) == 0x80)*/ /* Check if it is a break code. */
	  /*{ 
        key_repeat = FALSE;
      }
    } 
	else if (mouseState == MOUSE_STATE_DELTA_X) 
	{ 
      mouse_state = MOUSE_STATE_DELTA_Y;
      mouse_delta_X = scancode;
    } 
	else if (mouseState == MOUSE_STATE_DELTA_Y) 
	{ 
      mouse_state = MOUSE_STATE_FIRST_PACKET;
      mouse_delta_Y = scancode;
    }

    *ISRB_MFP_Register &= MFB_BIT_6_MASK_OFF;*/ /* Clears the 6th bit. */
  /*}

  *IKBD_Control = DISABLE;
}*/

void install_vectors() 
{
  vbl_vector = install_vector(VBL_VEC, vbl_isr);
  /*ikbd_vector = install_vector(IKBD_VEC, ikbd_isr);*/
}

void remove_vectors() 
{
  install_vector(VBL_VEC, vbl_vector);
  /*install_vector(IKBD_VEC, ikbd_vector);*/
}

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

int ikbd_waiting() 
{
  return buffer_head != buffer_tail;
}

int ikbd_mouse_moved() 
{
  return mouse_moved;
}

void write_ikbd_buffer(UINT8 scancode) 
{
  if (buffer_tail == IKBD_BUFFER_SIZE - 1)
  {
    buffer_tail = 0;
  }

  IKBD_buffer[buffer_tail] = scancode;
  buffer_tail++;
}

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

void clear_ikbd_buffer() {
  while(ikbd_waiting()) {
    buffer_head++;
  }

  IKBD_buffer[buffer_tail] = 0x00;
}
