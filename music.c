#include "music.h"
#include <stdio.h>

int splash_song[] = {
};

int main_song[] = {
};

/********************************************************************************************
Function Name: 	start_music

Details: 	Uses the PSG module to starts the music.

*********************************************************************************************/

void start_music()
{
	enable_channel(CH_A,1,0);
	set_envelope(4,10);
	set_volume(CH_A,8)
	return;
}


/********************************************************************************************
Function Name: 	update_music

Details: 	Changes the note in the music.

*********************************************************************************************/

int update_music(UINT32 time_elapsed, int last_note, int song_length)
{
	if(time_elapsed >= 35)
	{
		if(last_note == song_length)
			last_note = 0;
		
		set_tone(CH_A, song[last_note];
		last_note++;
	}
	retuen last_note;
}