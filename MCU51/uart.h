
#ifndef __UART_HANDER_H__
#define __UART_HANDER_H__

#include <stdio.h>

typedef void (*UartRecvFunc)(unsigned char dat);

void UartInit(UartRecvFunc recvFunc);

void UartInitBps(int bps, UartRecvFunc recvFunc);

void UartSetBps(int bps);

void UartSend(unsigned char dat);

void UartSends(unsigned char* dat, int size);

int UartPrintf(const char* format, ...);


#endif  // __UART_HANDER_H__