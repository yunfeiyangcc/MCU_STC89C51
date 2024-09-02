#include <REGX51.H>
#include <intrins.h>
#include "timer.h"

void CounterInit(unsigned char id)
{
	if (id == 0)
	{
		TMOD &= 0xF0;
		TMOD |= 0x01;
		TH0 = 0;
		TL0 = 0;
		TF0 = 0;
		TR0 = 0;
	}
	else if (id == 1)
	{
		TMOD &= 0x0F;
		TMOD |= 0x10;
		TH1 = 0;
		TL1 = 0;
		TF1 = 0;
		TR1 = 0;
	}
}

void CounterStart(unsigned char id)
{
	if (id == 0)
	{
		TR0 = 1;
	}
	else if (id == 1)
	{
		TR1 = 1;
	}
}

void CounterStop(unsigned char id)
{
	if (id == 0)
	{
		TR0 = 0;
	}
	else if (id == 1)
	{
		TR1 = 0;
	}
}

bit CounterIsStart(unsigned char id)
{
	return (id == 0 ? TR0 : id == 1 ? TR1 : 0);
}

void CounterClear(unsigned char id)
{
	if (id == 0)
	{
		TH0 = 0;
		TL0 = 0;
	}
	else if (id == 1)
	{
		TH1 = 0;
		TL1 = 0;
	}
}

unsigned int CounterGet(unsigned char id)
{
	if (id == 0)
	{
		return ((TH0 << 8) | TL0);
	}
	else if (id == 1)
	{
		return ((TH1 << 8) | TL1);
	}
	
	return 0;
//	return (id == 0 ? ((TH0 << 8) | TL0) : ((TH1 << 8) | TL1));
}

