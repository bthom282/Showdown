#include <osbind.h>
#include <stdio.h>
#include "PSG.h"
#include "music.h"
#include "effects.h"
#include "types.h"

UINT32 get_time();

const UINT32 * const timer = (UINT32 *)0x462;

int main()
{
	
	UINT32 time_now, time_then, time_delta;
	UINT32 music_timer = 0;
	int game_timer = 0;
	UINT32 last_note_change = 0;
	int current_note;
	int last_note;
	
	time_then = get_time();
	time_now = get_time();
	time_delta = time_now - time_then;
	
	start_music();
	while (!Cconis())     /* repeat until key press... */
	{
		music_timer = game_timer - last_note_change;
		current_note = update_music(music_timer, last_note, splash_song_bass, 
									splash_song_treble[],  SPLASH_SONG_LENGTH)
		
		if (currentNote != lastNote)
			{
				last_note_change = gameTimer;
				last_note = currentNote;
			}
	}
		
	stopSound();
	
	return 0;
}

UINT32 get_time()
{
	UINT32 time, old_ssp;

	old_ssp = Super(0);
	time = *timer;
	Super(old_ssp);

	return time;
}