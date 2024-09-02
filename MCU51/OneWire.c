#include <REGX51.H>
#include "OneWire.h"
#include "timer.h"

sbit ONE_WIRE_DQ = P2^2;

unsigned char OneWireInit()
{
	unsigned char ack = 0;

	ONE_WIRE_DQ = 1;
	ONE_WIRE_DQ = 0;
	Delay500us();
	ONE_WIRE_DQ = 1;
	Delay70us();
	ack = ONE_WIRE_DQ;
	Delay500us();
	
	while(!ONE_WIRE_DQ);
	
	return ack;
}

void OneWireSendBit(bit value)
{
	ONE_WIRE_DQ = 0;
	Delay10us();
	ONE_WIRE_DQ = value;
	Delay50us();
	ONE_WIRE_DQ = 1;
}

bit OneWireReceiveBit()
{
	bit value = 0;

	ONE_WIRE_DQ = 0;
	Delay5us();
	ONE_WIRE_DQ = 1;
	Delay5us();
	value = ONE_WIRE_DQ;
	Delay50us();
	
	return value;
}

void OneWireSendByte(unsigned char value)
{
	unsigned char i = 0; 
	for (i = 0; i < 8; i++)
	{
		OneWireSendBit(value & (0x01 << i));
	}
}

unsigned char OneWireReceiveByte()
{
	unsigned char value = 0;

	unsigned char i = 0; 
	for (i = 0; i < 8; i++)
	{
		if (OneWireReceiveBit())
			value |= (0x01 << i);
	}

	return value;
}

