#ifndef ISR_H
#define ISR_H

#include "vbl.h"
#include "ikbd.h"
#include "music.h"
#include "renderer.h"
#include "types.h"

#define VBL_VEC 28
#define IKBD_VEC 70

#define IKBD_RX_DEFAULT 0xFFFC96
#define IKBD_RX_INTERRUPT_OFF 0xFFFC16

#define MFB_BIT_6_MASK_ON 0x40
#define MFB_BIT_6_MASK_OFF 0xBF

#define MOUSE_STATE_FIRST_PACKET 0
#define MOUSE_STATE_DELTA_X 1
#define MOUSE_STATE_DELTA_Y 2

#define MOUSE_MOVE_CODE 0xF8
#define MOUSE_LEFT_BUTTON_CODE 0xFA

#define IKBD_BUFFER_SIZE 256

#define ESC_MAKE ((SCANCODE)0x01)
#define ESC_BREAK ((SCANCODE)0x81)
#define ENABLE 0x16
#define DISABLE 0x96

typedef void (*Vector) ();

/* Timers that are used by the VBL. */
extern int music_timer;
extern int game_timer;

/* Flags that will allow rendering when they are set to true. */
extern int render_request;
extern int render_mouse_request;
extern int spawn_snake_request;

extern int mouse_X;
extern int mouse_Y;

extern int mouse_left_click;

extern UINT8 mouse_button;
extern int prev_mouse_X;
extern int prev_mouse_Y;
extern int mouse_moved;

extern UINT8 IKBD_buffer[IKBD_BUFFER_SIZE];
extern unsigned int buffer_head;
extern unsigned int buffer_tail;

extern Vector vbl_vector;
extern Vector ikbd_vector;

extern int game_state;

void vblisrC();

void ikbdisrC();

Vector install_vector(int num, Vector vector);

void install_vectors();

void remove_vectors();

int ikbdWaiting();

int ikbd_mouse_moved();

void write_ikbd_buffer(UINT8 scancode);

UINT32 read_ikbd_buffer();

void clear_ikbd_buffer();

void mouse_check();

#endif