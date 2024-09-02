#include <REGX51.H>
#include "interrupt.h"

InterruptFunc gInterruptFunc[2] = {0};

void InterruptInit(unsigned char id, InterruptFunc f)
{
	if (id == 0)
	{
		EA = 1;   // 使能总中断
//		PX0 = 1;  // 中断优先级：最高优先级
		IT0 = 1;  // 中断触发方式：跳变沿出发
//		IE0 = 0;  // 外部中断0清0
	}
	else if (id == 1)
	{
		EA = 1;
//		PX1 = 1;
		IT1 = 1;
//		IE1 = 0;
	}
	
	gInterruptFunc[id] = f;
}

void InterruptStart(unsigned char id)
{
	if (id == 0)
	{
		EX0 = 1;  // 使能外部中断0
	}
	else if (id == 1)
	{
		EX1 = 1;
	}
}

void InterruptStop(unsigned char id)
{
	if (id == 0)
	{
		EX0 = 0;  // 使能外部中断2
	}
	else if (id == 1)
	{
		EX1 = 0;
	}
}

bit InterruptIsStart(unsigned char id)
{
	return (id == 0 ? EX0 : id == 1 ? EX1 : 0);
}


void Extern0Interrupt() interrupt 0
{
	if (gInterruptFunc[0])
		gInterruptFunc[0]();
}

void Extern2Interrupt() interrupt 2
{
	if (gInterruptFunc[1])
		gInterruptFunc[1]();
}


