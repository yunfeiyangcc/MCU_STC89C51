#include "DS18B20.h"
#include "lcd1602.h"
#include "digitalTube.h"
#include "led.h"
#include "log.h"
#include "timer.h"

void TestDS18B20UartRecvHandler(unsigned char dat)
{
	unsigned char value = dat;

	LedSet(~value);
	UartSend(value);
	
	LOG("value = %bX\n", value);
}

float gT = 0;

//void main()
void TestDS18B20()
{
///////////  DS18B20  //////////////
	float t = 0;

	LOG("TestDS18B20 start\n");
	DTubeClose();
	DS18B20ConvertT();
	Delay(1000);

	
	UartInit(TestDS18B20UartRecvHandler);

	LcdInit();
	
	while(1)
	{
		DS18B20ConvertT();
		t = DS18B20ReadT();
		if (gT != t)
		{
			gT = t;
			LcdShowString(1, 2, "Tempture:");
			LcdShowFloat(2, 2, t, 1);
			LcdShowCharQue(0xDF);
			LcdShowCharQue('C');

			LOG("TestDS18B20 t = %f\n", t);
		}
		
		Delay(500);
	}
}