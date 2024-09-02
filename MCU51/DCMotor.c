#include <REGX51.H>

sbit DC_MOTOR = P1^7;

void DCMotorOpen()
{
	DC_MOTOR = 0;
}

void DCMotorClose()
{
	DC_MOTOR = 1;
}

