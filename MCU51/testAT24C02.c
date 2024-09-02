#include "AT24C02.h"
#include "led.h"
#include "log.h"
#include "timer.h"

void TestAT24C02UartRecvHandler(unsigned char dat)
{
	unsigned char value = 0;

	AT24C02Write(0x02, dat);
	Delay(5);

	value = AT24C02Read(0x02);
	LedSet(value);

	
	LedSet(~value);
	UartSend(value);
	
	LOG("value = %bX\n", value);
}

//void main()
void TestAT24C02()
{
///////////  AT24C02  //////////////
	int i = 0;
	unsigned char value = 0;
	unsigned char dat[] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
//		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
//		0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
	};
	unsigned char readData[40] = {0x00};

	UartInit(TestAT24C02UartRecvHandler);

	LOG("testAT24C02 start value = %bX\n", value);

	
//	AT24C02Write(0x00, 0x00);
//	AT24C02Write(0x01, 0x01);
//	AT24C02Write(0x02, 0x02);
//	AT24C02Write(0x03, 0x03);
//	AT24C02Write(0x07, 0x07);
//	AT24C02Write(0x08, 0x08);
//	AT24C02Write(0x07, 0xFF);

	AT24C02WriteMulti(0x00, dat, sizeof(dat));

//	value = AT24C02Read(0x20-1);
//	LedSet(value);
//	LOG("value = %bX\n", value);

	value = AT24C02ReadCur();
	LedSet(value);
	LOG("value = %bX\n", value);
	
	

	AT24C02ReadMulti(0x00, readData, sizeof(readData));
	for (i = 0; i < sizeof(readData); i++)
	{
		LOG("readData[%d] = %bX\n", i, readData[i]);
	}

//	value = AT24C02Read(0x07);
//	LedSet(value);
//	LOG("value = %bX\n", value);


	
	while(1)
	{
		
	}
}