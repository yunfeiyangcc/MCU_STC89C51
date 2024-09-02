#include <REGX51.H>
#include <intrins.h>
#include "timer.h"


void Delay5us()		//@11.0592MHz
{
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay20us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 6;
	while (--i);
}

void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}

void Delay70us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 29;
	while (--i);
}

void Delay100us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 43;
	while (--i);
}

void Delay200us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 89;
	while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}


static void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay(int ms)
{
	int i = 0;
	for(i = 0; i < ms; i++)
		Delay1ms();
}


sTimerData gTimerData[2] = {
	{ TIMER_50MS, 50, 0, 0},
	{ TIMER_50MS, 50, 0, 0}
};


void TimerInit(unsigned char id, unsigned int timeout, TimerFunc f)
{
	if (timeout == TIMER_50MS)
	{
		gTimerData[id].timeout = timeout;
		gTimerData[id].ms = 50;
		gTimerData[id].us = 0;
		gTimerData[id].f = f;
	}
	else if (timeout == TIMER_1MS)
	{
		gTimerData[id].timeout = timeout;
		gTimerData[id].ms = 1;
		gTimerData[id].us = 0;
		gTimerData[id].f = f;
	}

	if (id == 0)  // 50ms
	{
		TMOD &= 0xF0;
		TMOD |= 0x01;
		TH0 = (65536 - gTimerData[id].timeout) / 256;
		TL0 = (65536 - gTimerData[id].timeout) % 256;
		EA = 1;
		ET0 = 1;
	}
	else if (id == 1)  // 50ms
	{
		TMOD &= 0x0F;
		TMOD |= 0x10;
		TH1 = (65536 - gTimerData[id].timeout) / 256;
		TL1 = (65536 - gTimerData[id].timeout) % 256;
		EA = 1;
		ET1 = 1;
	}

}

void TimerStart(unsigned char id)
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

void TimerStop(unsigned char id)
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

bit TimerIsStart(unsigned char id)
{
	return (id == 0 ? TR0 : id == 1 ? TR1 : 0);
}

void Timer0Interrupt() interrupt 1
{
	TH0 = (65536 - gTimerData[0].timeout) / 256;
	TL0 = (65536 - gTimerData[0].timeout) % 256;
	if (gTimerData[0].f != 0)
		gTimerData[0].f(gTimerData[0].ms, gTimerData[0].us);
}

void Timer1Interrupt() interrupt 3
{
	TH1 = (65536 - gTimerData[1].timeout) / 256;
	TL1 = (65536 - gTimerData[1].timeout) % 256;
	if (gTimerData[1].f != 0)
		gTimerData[1].f(gTimerData[1].ms, gTimerData[1].us);
}


