#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#includes "types.h"

#define REST 0
#define C3 130
#define C4 261
#define F3 174
#define E4 349
#define A4 440
#define C5 523

#define SPLASH_SONG_LENGTH 20
#define MAIN_SONG_LENGTH 48


void start_music();

int update_music(UINT32 time_elapsed, int last_note, int num_notes);

#endif