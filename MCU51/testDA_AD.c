#include "DA_AD.h"
#include "digitalTube.h"
#include "log.h"
#include "timer.h"
#include "keys.h"


unsigned long gTimerDAms = 0;
unsigned char gDAValue = 0;


void TimerDAHandler(unsigned int ms, unsigned int us)
{
	gTimerDAms += ms;

	if (gTimerDAms < 2000)
	{
		gDAValue += (256/40);
	}
	else if (gTimerDAms == 2000)
	{
		gDAValue = 0xFF;
	}
	else if (gTimerDAms > 2000 && gTimerDAms < 4000)
	{
		gDAValue -= (256/40);
	}
	else
	{
		gTimerDAms = 0;
		gDAValue = 0;
	}
}



//void main()
void TestDA_AD()
{
///////////  DA   //////////////
	DTubeClose();
	TimerInit(0, TIMER_50MS, TimerDAHandler);
	TimerStart(0);
	DAInit();


	while(1)
	{
		DAIn(gDAValue);
	}





///////////  AD  //////////////
//	int i = 0;
//	unsigned char adValue = 0;
//	DTubeInit();

//	ADInit();
//	
//	while(1)
//	{
//		ADStart();

//		for (i = 0; i < 20; i++)
//			DTubeDisplayDec(adValue, 0);
//		
//		adValue = ADRead();

//		DTubeDisplayDec(adValue, 0);
//	}
}