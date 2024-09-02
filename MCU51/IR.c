#include <REGX51.H>
#include "IR.h"
#include "counter.h"
#include "interrupt.h"
#include "log.h"

sbit IR_PORT = P3^3;

unsigned char gNecState = 0;
unsigned char gNecRepeatFlag = 0;

unsigned char gNecData[4] = {0};
unsigned char gNecDataCnt = 0;
unsigned char gNecDataFlag = 0;
unsigned char gNecAddress = 0;
unsigned char gNecCommand = 0;

unsigned int gNecCounter = 0;


// 有问题，无法正确解析红外数据
void IRInterrupt0Func()
{
	if (gNecState == 0)
	{
		CounterClear(0);
		CounterStart(0);
		gNecState = 1;
		LOG("gNecCounter 0 = %u\n", gNecCounter);
	}
	else if (gNecState == 1)
	{
		gNecCounter = CounterGet(0);
		CounterClear(0);
		LOG("gNecCounter 1 = %u\n", gNecCounter);
		if (gNecCounter > 8000 && gNecCounter < 14000)     // Start 13.5ms
		{
			CounterClear(0);
			P1 = 0xFE;
			gNecState = 2;
		}
		else if(gNecCounter > 12368 - 500 && gNecCounter < 12368 + 500)        // Repeat 11.25ms
		{
			P1 = 0xFD;
			gNecRepeatFlag = 1;
			gNecState = 0;
			CounterClear(0);
			CounterStop(0);
		}
		else
		{
			P1 = 0xFB;
			gNecState = 0;
			CounterClear(0);
		}
	}
	else if (gNecState == 2)
	{
		gNecCounter = CounterGet(0);
//		CounterClear(0);
		LOG("gNecCounter         = %u\n", gNecCounter);
		if(gNecCounter > 700 && gNecCounter < 1450)    // 1120us  数据 0
		{
			P1 = 0x7F;
			gNecData[gNecDataCnt/8] &= ~(0x01 << (gNecDataCnt % 8));
			gNecDataCnt++;
		}
		else if(gNecCounter > 1450 && gNecCounter < 3000)    // 2250us  数据 1
		{
			P1 = 0xDF;
			gNecData[gNecDataCnt/8] |= (0x01 << (gNecDataCnt % 8));
			gNecDataCnt++;
		}
		else
		{
			gNecDataCnt = 0;
			gNecState = 1;
		}
		CounterClear(0);
		
		if (gNecDataCnt >= 32)   // 数据接收完毕
		{
			gNecDataCnt = 0;
			if ((gNecData[0] == ~gNecData[1]) &&
				  (gNecData[2] == ~gNecData[3]))
			{
				gNecAddress = gNecData[0];
				gNecCommand = gNecData[2];
				gNecDataFlag = 1;
				P1 = 0x00;
			}
			CounterStop(0);
			CounterClear(0);
			gNecState = 0;
		}
	}
}


void IRInit()
{
	InterruptInit(1, IRInterrupt0Func);
	InterruptStart(1);
	CounterInit(0);
	CounterStart(0);
	UartInit(NULL);
}

unsigned char IRGetDataFlag()
{
	if (gNecDataFlag)
	{
		gNecDataFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IRGetRepeatFlag()
{
	if (gNecRepeatFlag)
	{
		gNecRepeatFlag = 0;
		return 1;
	}
	return 0;
}

unsigned char IRGetAddress()
{
	return gNecAddress;
}

unsigned char IRGetCommand()
{
	return gNecCommand;
}


