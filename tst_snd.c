#include <osbind.h>
#include <stdio.h>
#include <unistd.h>
#include "PSG.h"
#include "music.h"
#include "effects.h"
#include "types.h"
#define SOUND_DELAY_MICROSECONDS 500000

UINT32 get_time();

const UINT32 * const timer = (UINT32 *)0x462;

void play_sound_with_delay(void (*play_sound_function)(), const char* message);

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
	printf("Press any key to switch to the next sound.\n");
	while (!Cconis())
	{
		music_timer = game_timer - last_note_change;
		current_note = update_music(music_timer, last_note, splash_song_bass, 
									splash_song_treble,  SPLASH_SONG_LENGTH);
		
		if (current_note != last_note)
			{
				last_note_change = game_timer;
				last_note = current_note;
			}
	}
	
	play_sound_with_delay(play_chime, "Sound 1");
    play_sound_with_delay(play_chime, "Sound 2");
    play_sound_with_delay(play_chime, "Sound 3");
	play_sound_with_delay(play_pop, "Sound 4");
    play_sound_with_delay(play_pop, "Sound 5");
    play_sound_with_delay(play_pop, "Sound 6");
	play_sound_with_delay(play_spawn, "Sound 7");
    play_sound_with_delay(play_spawn, "Sound 8");
    play_sound_with_delay(play_spawn, "Sound 9");
		
	stop_sound();
	
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

void play_sound_with_delay(void (*play_sound_function)(), const char* message) {
    play_sound_function(); 
    printf("%s\n", message); 
    usleep(SOUND_DELAY_MICROSECONDS); 
}