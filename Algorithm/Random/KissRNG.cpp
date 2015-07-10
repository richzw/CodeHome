#include "stdafx.h"
#include "KissRNG.h"
#include <windows.h>


void RNG::kiss_init()
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	w = 916191069L;
	x = (x ^ (counter.QuadPart & 0xFFFF)) | 1;
	y = y ^ (counter.QuadPart & 0xFFFF);
	z = 521288629L;
}

unsigned long RNG::kiss_rand()
{
	unsigned long ret;

	// kiss w
	w = 30903 * (w & 0xFFFF) + w >> 16;

	// kiss x
	x = 69069 * x + 1327217885;

	// kiss y
	y = y ^ (y << 13);
	y = y ^ (y >> 17);
	y = y ^ (y << 5);

	// kiss z
	z = 18000 * (z & 0xFFFF) + (z >> 16);

	return (w << 16) + x + y + (z & 0xFFFF);
}

RNG::RNG() :w(0), x(0), y(0), z(0)
{
	kiss_init();
}

unsigned long RNG::GetRNG(unsigned long rand_min, unsigned long rand_max)
{
	unsigned long span = (rand_min > rand_max) ? (rand_min - rand_max)+1 : (rand_max - rand_min)+1;

	if (span)
		rand_min += kiss_rand() % span;

	return rand_min;
}


