#include <REGX51.H>
#include "IIC.h"

sbit IIC_SDA = P2^0;
sbit IIC_SCL = P2^1;


void IICInit()
{
	IIC_SDA = 1;
	IIC_SCL = 1;
}

void IICStart()
{
	IIC_SDA = 1;
	IIC_SCL = 1;
	IIC_SDA = 0;
	IIC_SCL = 0;
}

void IICStop()
{
	IIC_SDA = 0;
	IIC_SCL = 1;
	IIC_SDA = 1;
}

void IICSend(unsigned char dat)
{
	unsigned char i = 0;

	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		IIC_SDA = dat & (0x80 >> i);
		IIC_SCL = 1;
		IIC_SCL = 0;
	}
}


unsigned char IICReceive()
{
	unsigned char dat = 0;
	unsigned char i = 0;

	IIC_SDA = 1;

	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 1;
		if (IIC_SDA)
			dat |= (0x80 >> i);
		IIC_SCL = 0;
	}
	
	return dat;
}

void IICSendAck(bit ack)
{
	IIC_SDA = ack;
	IIC_SCL = 1;
	IIC_SCL = 0;
}

bit IICReceiveAck()
{
	bit ack = 0;

	IIC_SDA = 1;
	IIC_SCL = 1;
	ack = IIC_SDA;
	IIC_SCL = 0;

	return ack;
}

void IICWaitAck()
{
	unsigned char i = 0;

	IIC_SCL = 1;

	while((IIC_SDA == 1) && (i < 250))
		i++;

	IIC_SCL = 0;
}



