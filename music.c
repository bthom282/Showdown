#include "music.h"
#include <stdio.h>

int splash_song_bass[SPLASH_SONG_LENGTH] = {
	C3, REST, F3, REST, 
	F3, REST, F3, REST, 
	F3, REST, F3, REST, 
	F3, REST, F3, REST, 
	REST, REST, REST, REST
	
};
int splash_song_treble[SPLASH_SONG_LENGTH] = {
	C4, REST, REST, E4,
	REST, E4, REST, E4,
	REST, E4, REST, E4,
	REST, E4, REST, E4,
	A4, C5, C5, C5
};

int main_song_bass[MAIN_SONG_LENGTH] = {
};

int main_song_trebel[MAIN_SONG_LENGTH] = {
};

/********************************************************************************************
Function Name: 	start_music

Details: 	Uses the PSG module to starts the music.

*********************************************************************************************/

void start_music()
{
	/* begin bass */
	enable_channel(CH_A,1,0);
	set_envelope(4,10);
	set_volume(CH_A,8)
		
	/* begin treble */
	enable_channel(CH_B,1,0);
	set_envelope(4,10);
	set_volume(CH_B,8)
	
	return;
}

/********************************************************************************************
Function Name: 	update_music

Details: 	Changes the note in the music.

*********************************************************************************************/

int update_music(UINT32 time_elapsed, int last_note, int bass[], int treble[],  int song_length)
{
	if(time_elapsed >= 35)
	{
		if(last_note == song_length)
			last_note = 0;
		
		set_tone(CH_A, bass[last_note];
		set_tone(CH_B, treble[last_note];
		last_note++;
	}
	retuen last_note;
}