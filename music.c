#include "music.h"
#include <stdio.h>

int splash_song_bass[SPLASH_SONG_LENGTH] = {
	C3, REST, F3, REST, 
	F3, REST, F3, REST, 
	F3, REST, F3, REST, 
	F3, REST, F3, REST, 
	REST, REST, REST, REST,
	REST, REST, REST, REST
	
};
int splash_song_treble[SPLASH_SONG_LENGTH] = {
	C4, REST, REST, E4,
	REST, E4, REST, E4,
	REST, E4, REST, E4,
	REST, E4, REST, E4,
	A4, C5, C5, C5,
	REST, REST, REST, REST
};

int main_song_bass[MAIN_SONG_LENGTH] = {
	REST, REST, REST, REST, REST, F3 , REST, G3,
	REST, REST, REST, REST, REST, REST, REST, REST,
	G3, REST, REST, REST, F3, REST, REST, REST,
	F3, REST, REST, REST, F3, REST, REST, G3,
	REST, C3, REST, REST, REST, REST, REST, REST,
	REST, REST, REST, REST, F3, REST, G3, REST,
	REST, REST, REST, REST, REST, REST, G3, REST,
	REST, REST, F3, REST, D3, REST, REST, REST,
	G3, REST, REST, REST, REST, REST, REST, REST	
};
int main_song_treble[MAIN_SONG_LENGTH] = {
	E6, E6, G6, A6, A6, A6, A6, G6,
	REST, REST, C6, D6, D6, E6, G6, E6,
	C6, A5, REST, A5, A5, G5, A5, C6,
	C6, A5, C6, REST, A5, C6, C6, D6,
	D6, C6, REST, G5, G5, C6, C6, E6,
	E6, G6, A6, A6, A6, A6, G6, REST,
	C6, C6, D6, D6, E6, G6, E6, C6,
	A5, REST, A5, A5, G5, E5, C6, D6,
	E5, REST, REST, REST, REST, REST, REST, REST
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
	set_volume(CH_A,16);
		
	/* begin treble */
	enable_channel(CH_B,1,0);
	set_envelope(4,10);
	set_volume(CH_B,16);
	
	return;
}

/********************************************************************************************
Function Name: 	update_music

Details: 	Changes the note in the music.

*********************************************************************************************/

int update_music(UINT32 time_elapsed, int last_note, int bass[], int treble[],  int song_length)
{
	if((time_elapsed % 70) == 0)
	{
		if(last_note == song_length)
			last_note = 0;
		
		set_tone(CH_A, bass[last_note]);
		set_tone(CH_B, treble[last_note]);
		last_note++;
	}
	return last_note;
}