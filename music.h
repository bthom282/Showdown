#ifndef MUSIC_H
#define MUSIC_H

#include "PSG.h"
#includes "types.h"

#define REST 0

/*define the rest of notes needed*/

void start_music();

int update_music(UINT32 time_elapsed, int last_note, int num_notes);

#endif