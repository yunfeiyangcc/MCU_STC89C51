#include "uart.h"
#include "led.h"
#include "log.h"


void UartRecvHandler(unsigned char dat)
{
	float PI = 3.14159;
	
	LedSet(dat);
	UartSend(dat);
	
	UartPrintf("\tPI = %f\n", PI);
	UartPrintf("\tAA = %f\n", 1.987456321);
	UartPrintf("\tBB = %d\n", 12345);
	UartPrintf("\tCC = %s\n", "string");
	UartPrintf("\tDD = %c\n", 'Z');
	UartPrintf("\tXX = %x\n", 12345);
	
	LOG("\tLOG = %s\n", "LOG");
}

//void main()
void TestUart()
{
///////////  UART  //////////////
	UartInit(UartRecvHandler);

	while(1)
	{
		
	}
}