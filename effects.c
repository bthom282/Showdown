#include "effects.h"

/********************************************************************************************
Function Name: 	play_chime

Details: 	Plays a chiming sound when the score increases.

*********************************************************************************************/

void play_chime()
{
	disable_channel(CH_C);
	enable_channel(CH_C,1,0);
	set_tone(CH_C, 0x010);
	set_volume(CH_C,16);
	set_envelope(0,48);
	
	return;
}

/********************************************************************************************
Function Name: 	play_pop

Details: 	Plays pop sound for shooting.

*********************************************************************************************/

void play_pop()
{
	disable_channel(CH_C);
	enable_channel(CH_C,0,1);
	set_volume(CH_C,16);
	set_envelope(0,10);

	return;
}

/********************************************************************************************
Function Name: 	play_spawn

Details: 	plays white noise sound whenever a snake spawns.

*********************************************************************************************/

void play_spawn()
{
	disable_channel(CH_C);
	enable_channel(CH_C,1,0);
	set_tone(CH_C, 0x327);
	set_volume(CH_C,16);
	set_envelope(4,1);

	return;
}