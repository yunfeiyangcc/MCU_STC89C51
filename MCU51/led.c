#include <intrins.h>
#include "led.h"
#include "timer.h"

void LedSet(unsigned char led)
{
	LED1_8 = led;
}

void LedLock()
{
	LED_LE = 0;
}

void LedUnlock()
{
	LED_LE = 1;
}

void LedSetBit(unsigned char pos, bit b)
{
	unsigned char value = 0;

	if (pos < 1 || pos > 8)
		return;

	value = LED1_8;
	if (b)
	{
		value |= (0x01 << (pos - 1));
	}
	else
	{
		value &= _crol_(0xFE, (pos - 1));
	}
	
	LED1_8 = value;
}

bit LedGetBit(unsigned char pos)
{
	if (pos < 1 || pos > 8)
		return 0;

	return (LED1_8 & (0x01 << (pos - 1)));
}


void LedWaterfallLight(int ms)
{
	unsigned char i = 0;
	unsigned char led = 0xFE;
	
	for (i = 0; i < 8; i++)
	{
		LedSet(led);
		Delay(ms);
		led = _crol_(led, 1);
	}
}

void LedWaterfallLight2(int ms)
{
	int i = 0;
	for (i = 1; i <= 8; i++)
	{
		LedSetBit(i, 0);
		Delay(ms);
		LedSetBit(i, 1);
		Delay(ms);
	}
}
