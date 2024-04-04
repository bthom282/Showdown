#include "random.h"

/*******************************************************************************************
Function Name: 	rand_in_range

Details: 	Given a range and a seed value, this function will return a pseudo-random 
		number in the given range. This will be used for the random snake spawning
  		during enemy waves.

Sample Call:	spawn_loc = rand_in_range((UINT32 *)seed, 0, 15);
*********************************************************************************************/

unsigned int rand_in_range(UINT32 *seed, UINT16 min, UINT16 max) {
    const unsigned long a = 1664525;
    const unsigned long c = 1013904223;
    const unsigned long m = 4294967295; /* 2^32-1 */
	unsigned int scaled; 

    *seed = (a * (*seed) + c) % m; /* Update the seed value */

    /* Scale the generated value to fit within the range [min, max] */

	scaled = (unsigned int)(((double)(*seed) / ((double)m + 1)) * (max - min + 1) + min);
    return scaled;
}