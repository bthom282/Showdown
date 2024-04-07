#include "model.h"

#define ESC_MAKE ((SCANCODE)0x01)
#define ESC_BREAK ((SCANCODE)0x81)
#define SPACE_MAKE ((SCANCODE)0x39)
#define SPACE_BREAK ((SCANCODE)0xB9)
#define UP_MAKE ((SCANCODE)0x48)
#define UP_BREAK ((SCANCODE)0xC8)
#define DOWN_MAKE ((SCANCODE)0x50)
#define DOWN_BREAK ((SCANCODE)0xD0)
#define LEFT_MAKE ((SCANCODE)0x4B)
#define LEFT_BREAK ((SCANCODE)0xCB)
#define RIGHT_MAKE ((SCANCODE)0x4D)
#define RIGHT_BREAK ((SCANCODE)0xCD)
#define W_MAKE ((SCANCODE)0x11)
#define W_BREAK ((SCANCODE)0x91)
#define A_MAKE ((SCANCODE)0x1E)
#define A_BREAK ((SCANCODE)0x9E)
#define S_MAKE ((SCANCODE)0x1F)
#define S_BREAK ((SCANCODE)0x9F)
#define D_MAKE ((SCANCODE)0x20)
#define D_BREAK ((SCANCODE)0xA0)

void input_handler(char input, struct Model *model, int *quit);

int check_input();

UINT32 get_input();

int check_mouse_input();