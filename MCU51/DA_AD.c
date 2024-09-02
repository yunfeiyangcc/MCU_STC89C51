#include <REGX51.H>
#include <intrins.h>
#include "DA_AD.h"
#include "timer.h"

sbit DULA = P2^6;
sbit WELA = P2^7;

sbit DA_CS = P3^2;
sbit DA_WR = P3^6;
#define DA_PORT P0

sbit AD_CS = P0^7;
sbit AD_WR = P3^6;
sbit AD_RD = P3^7;
#define AD_PORT P1


void DAInit()
{
	DA_CS = 0;
	DA_WR = 0;
}
void DAIn(unsigned char dat)
{
	DA_PORT = dat;
}


void ADInit()
{
	WELA = 1;
	AD_CS = 0;
	WELA = 0;
}

void ADStart()
{
	WELA = 1;
	AD_CS = 0;

	AD_WR = 0;
	_nop_();
	AD_WR = 1;

	AD_CS = 1;
	Delay(10);
	WELA = 0;
}

unsigned char ADRead()
{
	unsigned char value = 0;

	WELA = 1;

	AD_PORT = 0xFF;
	AD_CS = 0;

	AD_RD = 0;
//	_nop_();

	value = P1;
	AD_RD = 1;

	AD_CS = 1;

//	wr = 0;
	WELA = 0;

	return value;
}
