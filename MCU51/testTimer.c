#include "lcd1602.h"
#include "digitalTube.h"
#include "timer.h"

unsigned long timer0Count = 0;
unsigned long timer1Count = 0;

void Timer0Handler(unsigned int ms, unsigned int us)
{
	timer0Count += ms;
	LcdShowDec(1, 3, timer0Count, 8);
}

void Timer1Handler(unsigned int ms, unsigned int us)
{
	timer1Count += ms;
//	if (timer1Count % 50 == 0)
//	{
		LcdShowDec(2, 3, timer1Count, 8);
//	}
}


unsigned char hours = 0;
unsigned char mins = 0;
unsigned char secs = 0;
unsigned long timer01Count = 0;
void Timer01Handler(unsigned int ms)
{
	timer01Count += ms;
	if (timer01Count == 1000)
	{
		timer01Count = 0;
		secs++;
		if (secs >= 60)
		{
			secs = 0;
			mins++;
			if (mins >= 60)
			{
				mins = 0;
				hours++;
				if (hours >= 24)
				{
					hours = 0;
				}
				LcdShowDec(2, 3, hours, 2);
			}
			LcdShowDec(2, 6, mins, 2);
		}
		LcdShowDec(2, 9, secs, 2);
	}
}


//void main()
void TestTimer()
{
///////////  TIMER  //////////////
	DTubeClose();
	LcdInit();
	TimerInit(0, TIMER_50MS, Timer0Handler);
	TimerInit(1, TIMER_50MS, Timer1Handler);
	TimerStart(0);
	TimerStart(1);

	while(1)
	{
		
	}


//	DTubeClose();
//	LcdInit();
//	TimerInit(0, TIMER_50MS, Timer01Handler);
//	TimerStart(0);

//	LcdShowString(1, 3, "Clock:");
//	LcdShowString(2, 3, "00:00:00");
//	LcdShowDec(2, 3, hours, 2);
//	LcdShowDec(2, 6, mins, 2);			
//	LcdShowDec(2, 9, secs, 2);

	while(1)
	{
		
	}

}