#include "relay.h"
#include "led.h"
#include "log.h"
#include "timer.h"
#include "keys.h"



void TestRelaySkeyHandler(unsigned char value, unsigned char opt)
{
	if (value == 1)
	{
		if (opt == 0)
		{
			RelaySet(!RelayGet());
		}
	}
}

//void main()
void TestRelay()
{
///////////  RELAY  //////////////
//  按S2按键控制relay
	SkeyInit(TestRelaySkeyHandler);
	LedLock();

	while(1)
	{
		SkeyScan();
	}
}