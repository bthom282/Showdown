#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#include "types.h"
extern int splash_song_bass[];
extern int splash_song_treble[];
extern int main_song_bass[];
extern int main_song_treble[];

/****NOTES****/

#define REST 0
#define A3 220
#define A4 440
#define A5 880
#define A6 1760
#define C2 65
#define C3 130
#define C4 261
#define C5 523
#define C6 1046
#define D3 147
#define D4 294
#define D6 1175
#define E4 349
#define E5 659
#define E6 1319
#define F3 175
#define G3 196
#define G4 392
#define G5 784
#define G6 1568

#define SPLASH_SONG_LENGTH 24
#define MAIN_SONG_LENGTH 72

void start_music();

int update_music(int last_note, int bass[], int treble[],  int song_length);

#endif