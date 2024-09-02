#include "interrupt.h"
#include "digitalTube.h"
#include "lcd1602.h"
#include "log.h"
#include "timer.h"
#include "keys.h"
#include "IR.h"
#include "counter.h"


//void main()
void TestCounter()
{
	unsigned int testCount = 0;
	unsigned char i, j;
	
	DTubeClose();
	LcdInit();

	CounterInit(0);
	CounterStart(0);

	Delay(10);

	testCount = CounterGet(0);
	LcdShowDec(2, 2, testCount, 0);
	
	CounterClear(0);


	i = 2;
	j = 255;
	do
	{
		while (--j);
	} while (--i);

	testCount = CounterGet(0);
	LcdShowDec(2, 10, testCount, 0);
	
	while(1)
	{
		
	}
}

void main()
//void TestIR()
{
///////////  IR   //////////////
	unsigned char num = 0;
	DTubeClose();
	LcdInit();
	IRInit();

	LcdShowString(1, 2, "ADDR  CMD  NUM");
	LcdShowString(2, 2, "00    00   00");

	while(1)
	{
		if (IRGetDataFlag())
		{
			if (IRGetCommand() == IR_VOL_MINUS)
			{
				num--;
			}
			else if (IRGetCommand() == IR_VOL_ADD)
			{
				num++;
			}
			LcdShowHex(2, 2, IRGetAddress(), 0);
			LcdShowHex(2, 8, IRGetCommand(), 0);
			LcdShowHex(2, 13, num, 0);
		}
	}


}