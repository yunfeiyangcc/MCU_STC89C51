#include <REGX51.H>
#include "relay.h"

sbit RELAY = P2^0;

void RelayOpen()
{
	RELAY = 0;
}

void RelayClose()
{
	RELAY =1;
}

void RelaySet(bit value)
{
	RELAY = value;
}

bit RelayGet()
{
	return RELAY;
}
