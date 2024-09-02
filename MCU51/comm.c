#include "comm.h"

unsigned long PowL(unsigned long x, unsigned long y)
{
	unsigned long result = 1;
	int i = 0;

	if (y == 0)
		return 1;

	for (i = 0; i < y; i++)
	{
		result *= x;
	}

	return result;
}


unsigned char GetNumLen(unsigned long num, unsigned char dec)
{
	unsigned char count = 0;
	do
	{
		num /= dec;
		count++;
	} while(num > 0);

	return count;
}