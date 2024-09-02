#include <reg51.h>
#include <stdarg.h>
#include "uart.h"

int gUartBps = 0;
UartRecvFunc gUartRecvFunc = 0;

// 默认波特率9600
void UartInit(UartRecvFunc recvFunc)
{
	UartInitBps(9600, recvFunc);
}

void UartInitBps(int bps, UartRecvFunc recvFunc)
{
	TMOD = 0x20;
//	TH1 = 256 - (11059200 / (32 * bps * 12));
//	TL1 = 256 - (11059200 / (32 * bps * 12));
	TH1 = 256 - (28800 / bps);
	TL1 = 256 - (28800 / bps);
	TR1 = 1;

	SM0 = 0;
	SM1 = 1;

	gUartRecvFunc = recvFunc;
	if (gUartRecvFunc)
		REN = 1;

	EA = 1;
	ES = 1;
}

void UartSetBps(int bps)
{
	if (gUartBps != bps)
	{
		gUartBps = bps;
		TH1 = 256 - (28800 / bps);
		TL1 = 256 - (28800 / bps);
	}
}

void UartSend(unsigned char dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
}

void UartSends(unsigned char* dat, int size)
{
	int i = 0;

	if (dat == 0 || size == 0)
		return;

	for (i = 0; i < size; i++)
	{
		UartSend(dat[i]);
	}
}

int UartPrintf(const char* format, ...)
{
	int ret = 0;
	va_list ap;

	ES = 0;
	TI = 1;
	
	va_start(ap, format);

	ret = vprintf(format, ap);

	va_end(ap);

	TI = 0;
	ES = 1;

	return ret;
}



void UartInterrupt() interrupt 4
{
	if (RI == 1)
	{
		RI = 0;

		if (gUartRecvFunc)
			gUartRecvFunc(SBUF);
	}
}

