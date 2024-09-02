#include "AT24C02.h"
#include "IIC.h"
#include "timer.h"

#define AT24C02_ADDR_W 0xA0
#define AT24C02_ADDR_R 0xA1
#define AT24C02_PAGE_SIZE 0x08

void AT24C02Write(unsigned char addr, unsigned char value)
{
	IICStart();
	IICSend(AT24C02_ADDR_W);
	IICWaitAck();
	IICSend(addr);
	IICWaitAck();
	IICSend(value);
	IICWaitAck();
	IICStop();
	Delay(5);
}

/*
  --------------------------------
  |           页分布             |
  --------------------------------
	|  | 高5位   地3位             |
	|  | page    offset            |
  --------------------------------
  |0 | 00000   0 1 2 3 4 5 6 7 8 |
  |1 | 00001   0 1 2 3 4 5 6 7 8 |
  |2 | 00010   0 1 2 3 4 5 6 7 8 |
  |3 | 00011   0 1 2 3 4 5 6 7 8 |
  |4 | 00100   0 1 2 3 4 5 6 7 8 |
  |  | .....                     |
  |31| 11111   0 1 2 3 4 5 6 7 8 |
  --------------------------------
*/

void AT24C02WriteMultiInner(unsigned char addr, unsigned char* value, int len)
{
	int vi = 0;

	IICStart();
	IICSend(AT24C02_ADDR_W);
	IICWaitAck();

	IICSend(addr);
	IICWaitAck();
	for (vi = 0; vi < len; vi++)
	{
		IICSend(value[vi]);
		IICWaitAck();
	}
	
	IICStop();
}

void AT24C02WriteMulti(unsigned char addr, unsigned char* value, int len)
{
	int i = 0;
	int vi = 0;
	unsigned char page = 0;
	unsigned char offset = 0;
	unsigned char pageInfo[3] = {0};
	unsigned char wrAddr = 0;

	wrAddr = addr;
	page = addr >> 3;
	offset = addr & 0x07;
	
	if (offset + len > AT24C02_PAGE_SIZE)
	{
		pageInfo[0] = AT24C02_PAGE_SIZE - offset;
		pageInfo[1] = (len - pageInfo[0]) / AT24C02_PAGE_SIZE;
		pageInfo[2] = len - pageInfo[1] * AT24C02_PAGE_SIZE - pageInfo[0];
	}
	else
	{
		pageInfo[0] = len;
	}

	AT24C02WriteMultiInner(wrAddr, value, pageInfo[0]);
	vi += pageInfo[0];
	wrAddr += pageInfo[0];

	if (pageInfo[1] > 0)
	{
		for (i = 0; i < pageInfo[1]; i++)
		{
			AT24C02WriteMultiInner(wrAddr, value + vi , AT24C02_PAGE_SIZE);
			vi += AT24C02_PAGE_SIZE;
			wrAddr += AT24C02_PAGE_SIZE;
		}
	}

	if (pageInfo[2] > 0)
	{
		AT24C02WriteMultiInner(wrAddr, value + vi , pageInfo[2]);
		vi += pageInfo[2];
		wrAddr += pageInfo[2];
	}
	
	IICStop();

	Delay(5);
	
	if ((wrAddr & 0x07) == 0x00)
	{
		AT24C02Read(wrAddr - 1);
	}
}

unsigned char AT24C02ReadCur()
{
	unsigned char value = 0;
	
	IICStart();
	IICSend(AT24C02_ADDR_R);
	IICWaitAck();
	value = IICReceive();
	IICSendAck(1);
	IICStop();
	
	return value;
}

unsigned char AT24C02Read(unsigned char addr)
{
	unsigned char value = 0;
	
	IICStart();
	IICSend(AT24C02_ADDR_W);
	IICWaitAck();
	IICSend(addr);
	IICWaitAck();

	IICStart();
	IICSend(AT24C02_ADDR_R);
	IICWaitAck();
	value = IICReceive();
	IICSendAck(1);
	IICStop();
	
	return value;
}

void AT24C02ReadMulti(unsigned char addr, unsigned char* value, int len)
{
	int i = 0;

	if (value == 0)
		return;
	
	IICStart();
	IICSend(AT24C02_ADDR_W);
	IICWaitAck();
	IICSend(addr);
	IICWaitAck();

	IICStart();
	IICSend(AT24C02_ADDR_R);
	IICWaitAck();

	for (i = 0; i < len; i++)
	{
		value[i] = IICReceive();
		IICSendAck(i == len - 1 ? 1 : 0);
	}
	IICStop();
}
