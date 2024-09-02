#include <REGX51.H>
#include "beep.h"

sbit BEEP = P2^3;

void BeepOpen()
{
	BEEP = 0;
}

void BeepClose()
{
	BEEP =1;
}
