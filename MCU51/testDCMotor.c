#include "DCMotor.h"
#include "lcd1602.h"
#include "digitalTube.h"
#include "led.h"
#include "log.h"
#include "timer.h"
#include "keys.h"

unsigned char counter = 0;
unsigned char compare = 0;
unsigned char speed = 0;

void Timer100Handler(unsigned int ms, unsigned int us)
{
	counter = ++counter % 100;
	if (counter < compare)
	{
		DCMotorClose();
	}
	else
	{
		DCMotorOpen();
	}
}

void TestDCMotorSkeyHandler(unsigned char value, unsigned char opt)
{
	if (value == 1)
	{
		if (opt == 0)
		{
			speed = ++speed % 6;
			if (speed == 0) { compare = 0; }
			else if (speed == 1) { compare = 20; }
			else if (speed == 2) { compare = 40; }
			else if (speed == 3) { compare = 60; }
			else if (speed == 4) { compare = 80; }
			else if (speed == 5) { compare = 100; }
		}
	}
}

//void main()
void TestDCMotor()
{
///////////  DC MOTOR  //////////////
//  按S2按键控制直流电机的速度

	TimerInit(0, TIMER_1MS, Timer100Handler);
	TimerStart(0);
	SkeyInit(TestDCMotorSkeyHandler);
	DTubeInit();
	LedLock();

	while(1)
	{
		SkeyScan();
		DTubeDisplayDec(speed, 0);
	}
}