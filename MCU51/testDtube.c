#include "digitalTube.h"
#include "timer.h"

unsigned long num = 0;

void TimerHandler(unsigned int ms, unsigned int us)
{
	static unsigned int timer0ms = 0;
	timer0ms += ms;
	
	if (timer0ms == 100)
	{
		timer0ms = 0;
		num++;
	}
}


//void main()
void TestDtube()
{
///////////  Digital tube  //////////////

	DTubeInit();
	TimerInit(0, TIMER_50MS, TimerHandler);
	TimerStart(0);

	while(1)
	{
//		DTubeDisplayDecFix(num++, 4, 1);
		DTubeDisplayDec(num, 0);
//		DTubeDisplayHexFix(num++, 4, 1);
//		DTubeDisplayHex(num++, 1);
//		DTubeDisplayBin(num++, 1);
//		DTubeDisplayChar('H', 1);
//		DTubeDisplayChar('E', 2);
//		DTubeDisplayChar('L', 3);
//		DTubeDisplayChar('L', 4);
//		DTubeDisplayChar('O', 5);
//		DTubeDisplayString("ABCDEFFEDCBA", 0);

//		DTubeDisplaySignedDec(-3214);
//		Delay(500);
	}
}