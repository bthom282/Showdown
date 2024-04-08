#include "PSG.h"

/********************************************************************************************
Function Name: 	write_psg

Details: 	Loads the given value to the chosen register.

*********************************************************************************************/

void write_psg(int reg, UINT8 value)
{
	UINT32 old_ssp;
	
	old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	*PSG_reg_write = value;
	
	Super(old_ssp);
	
	return;
}


/********************************************************************************************
Function Name: 	read_psg

Details: 	Reads the current value on the PSG register.

*********************************************************************************************/

UINT8 read_psg(int reg)
{
	UINT8 value;
	UINT32 old_ssp;
	
	old_ssp = Super(0);
	
	*PSG_reg_select = reg;
	value = *PSG_reg_select;
	
	Super(old_ssp);
	
	return value;
}

/********************************************************************************************
Function Name: 	set_tone

Details: 	Changes the tone of one the three channels.

*********************************************************************************************/

void set_tone(int channel, int tuning)
{
	int fine = tuning & 0xFF;
	int rough = tuning >> 8;
	switch (channel)
	{
		case CH_A:
			write_psg(A_TONE_FINE, fine);
			write_psg(A_TONE_ROUGH, rough);
			break;
			
		case CH_B:
			write_psg(B_TONE_FINE, fine);
			write_psg(B_TONE_ROUGH, rough);
			break;
			
		case CH_C:
			write_psg(C_TONE_FINE, fine);
			write_psg(C_TONE_ROUGH, rough);
			break;
	}
	return;
}

/********************************************************************************************
Function Name: 	set_volume

Details: 	Changes the volume of one of the channels.

*********************************************************************************************/

void set_volume(int channel, int volume)
{
	switch (channel)
	{
		case CH_A:
			write_psg(A_VOLUME, volume);
			break;
			
		case CH_B:
			write_psg(B_VOLUME, volume);
			break;
			
		case CH_C:
			write_psg(C_VOLUME, volume);
			break;
	}
	return;
}

/********************************************************************************************
Function Name: 	set_noise

Details: 	Chnages the noise setting of the PSG.

*********************************************************************************************/

void set_noise(int tuning)
{
	write_psg(NOISE_REG, tuning);
	
	return;
}

/********************************************************************************************
Function Name: 	enable_channel

Details: 	enables a channel of the PSG.

*********************************************************************************************/

void enable_channel(int channel, int tone_on, int noise_on)
{
	int setting = 0x3F;
	
	switch (channel)
	{
		case CH_A:
			if(tone_on == 1)
			{
				setting &= 0x3E;
			}
			if(noise_on == 1)
			{
				setting &= 0x37;
			}
			break;
			
		case CH_B:
			if(tone_on == 1)
			{
				setting &= 0x3D;
			}
			if(noise_on == 1)
			{
				setting &= 0x2F;
			}
			break;
			
		case CH_C:
			if(tone_on == 1)
			{
				setting &= 0x3B;
			}
			if(noise_on == 1)
			{
				setting &= 0x1F;
			}
			break;
	}
	
	setting &= read_psg(MIXER_REG);
	write_psg(MIXER_REG, setting);
	
	return;
}

/********************************************************************************************
Function Name: 	disable_channel

Details: 	Turns off a channel on the PSG.

*********************************************************************************************/

void disable_channel(int channel)
{
	int setting;
	setting = read_psg(MIXER_REG);
	
	switch (channel)
	{
		case CH_A:
			setting |= 0x9;
			break;
			
		case CH_B:
			setting |= 0x12;
			break;
			
		case CH_C:
			setting |= 0x24;
			break;
	}
	
	write_psg(MIXER_REG, setting);
	
	return;
}

/********************************************************************************************
Function Name: 	set_envelope

Details: 	Changes the shape and duration of the sound envelope in the PSG.

*********************************************************************************************/

void set_envelope(int shape, unsigned int sustain)
{
	write_psg(ENV_FINE, sustain);
	write_psg(ENV_COARSE, sustain);
	write_psg(ENV_SHAPE, shape);
	
	return;
}

/********************************************************************************************
Function Name: 	stop_sound

Details: 	This function stops all sound.

*********************************************************************************************/

void stop_sound()
{
	set_volume(CH_A,0);
	set_volume(CH_B,0);
	set_volume(CH_C,0);
	enable_channel(CH_A, 0, 0);
	enable_channel(CH_B, 0, 0);
	enable_channel(CH_C, 0, 0);
	
	return;
}