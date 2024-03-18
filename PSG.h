#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include "types.h"

#define CH_A 0
#define CH_B 1
#define CH_C 2
#define A_TONE_FINE 0x0
#define A_TONE_ROUGH 0x1
#define B_TONE_FINE 0x2
#define B_TONE_ROUGH 0x3
#define C_TONE_FINE 0x4
#define C_TONE_ROUGH 0x5
#define NOISE_REG 0x6
#define MIXER_REG 0x7
#define A_VOLUME 0x8
#define B_VOLUME 0x9
#define C_VOLUME 0xA
#define ENV_FINE 0xB
#define ENV_COARSE 0xC
#define ENV_SHAPE 0xD
#define OFF 0xFF

extern volatile char *PSG_reg_select = 0xFF8800;
extern volatile char *PSG_reg_write = 0xFF8802;

void write_psg(int reg, UINT8 value);

UINT8 read_psg(int reg);

void set_tone(int channel, int tuning);

void set_volume(int channel, int volume);

void set_noise(int tuning);

void enable_channel(int channel, int tone_on, int noise_on);

void disable_channel(int channel);

void set_envelope(int shape, unsigned int sustain);

void stop_sound();

#endif