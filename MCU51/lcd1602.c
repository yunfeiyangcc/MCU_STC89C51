#include <REGX51.H>
#include <string.h>
#include "lcd1602.h"
#include "timer.h"
#include "comm.h"

sbit LCD_EN = P3^4;
sbit LCD_RS = P3^5;
#define LCD_DATA P0

void LcdWriteComm(unsigned char com)
{
	LCD_RS = 0;
	LCD_DATA = com;
//	Delay(1);
	LCD_EN = 1;
	Delay(1);
	LCD_EN = 0;
	Delay(1);
}

void LcdWriteData(unsigned char dat)
{
	LCD_RS = 1;
	LCD_DATA = dat;
//	Delay(5);
	LCD_EN = 1;
	Delay(1);
	LCD_EN = 0;
	Delay(1);
}

void LcdInit()
{
	LCD_EN = 0;
	LcdWriteComm(0x38);  // 显示模式设置
	LcdWriteComm(0x0C);  // 显示开关设置
	LcdWriteComm(0x06);  // 显示光标设置
	LcdWriteComm(0x01);  // 清屏
}

void LcdSetCursor(unsigned char row, unsigned char col)
{
	if (row == 1)
	{
		LcdWriteComm(0x80 | (col - 1));
	}
	else if (row == 2)
	{
		LcdWriteComm(0x80 | 0x40 | (col - 1));
	}
}

void LcdShowChar(unsigned char row, unsigned char col, char dat)
{
	LcdSetCursor(row, col);
	LcdWriteData(dat);
}

void LcdShowCharQue(char dat)
{
	LcdWriteData(dat);
}

void LcdShowString(unsigned char row, unsigned char col, const char* dat)
{
	const char* p = 0;

	LcdSetCursor(row, col);
	if (dat == 0)
		dat = "NULL";

	for (p = dat; *p != '\0'; p++)
	{
		LcdWriteData(*p);
	}
}

void LcdShowDec(unsigned char row, unsigned char col, unsigned long dat, unsigned char len)
{
	int count = 0;
	int i = 0;

	LcdSetCursor(row, col);

	count = GetNumLen(dat, 10);
	
	if (len == 0)
	{
		len = count;
	}

	for (i = len; i > 0; --i)
	{
		LcdWriteData('0' + (dat / PowL(10, i - 1) % 10));
	}
}

void LcdShowSignedDec(unsigned char row, unsigned char col, long dat, unsigned char len)
{
	int count = 0;
	int i = 0;

	LcdSetCursor(row, col);

	if (dat >= 0)
	{
		LcdWriteData('+');
		LcdShowDec(row, col + 1, dat, len);
		return;
	}

	LcdWriteData('-');
	LcdShowDec(row, col + 1, -dat, len);
}

void LcdShowHex(unsigned char row, unsigned char col, unsigned long dat, unsigned char len)
{
	int count = 0;
	int i = 0;

	LcdSetCursor(row, col);

	count = GetNumLen(dat, 16);
	
	if (len == 0)
	{
		len = count;
	}

	for (i = len; i > 0; --i)
	{
		unsigned char n = (dat / PowL(16, i - 1) % 16);
		if (n < 10)
			LcdWriteData('0' + n);
		else
			LcdWriteData('A' + n - 10);
	}
}

void LcdShowBin(unsigned char row, unsigned char col, unsigned long dat, unsigned char len)
{
	int count = 0;
	int i = 0;

	LcdSetCursor(row, col);

	count = GetNumLen(dat, 2);
	
	if (len == 0)
	{
		len = count;
	}

	for (i = len; i > 0; --i)
	{
		LcdWriteData('0' + (dat / PowL(2, i - 1) % 2));
	}
}

void LcdShowFloat(unsigned char row, unsigned char col, float dat, bit showPositive)
{
	int count = 0;
	int i = 0;
	unsigned long datH = 0;
	unsigned long datL = 0;

	LcdSetCursor(row, col);

	if (dat < 0)
	{
		dat = -dat;
		LcdWriteData('-');
	}
	else
	{
		if (showPositive)
			LcdWriteData('+');
	}
	
	datH = (unsigned long)dat;
	datL = (unsigned long)(dat * 10000) % 10000;
	
	count = GetNumLen(datH, 10);
	for (i = count; i > 0; --i)
	{
		LcdWriteData('0' + (datH / PowL(10, i - 1) % 10));
	}

	if (datL > 0) 
	{	
		LcdWriteData('.');

		count = GetNumLen(datL, 10);
		for (i = count; i > 0; --i)
		{
			LcdWriteData('0' + (datL / PowL(10, i - 1) % 10));
		}
	}
}


void LcdLeftMove(int offset)
{
	int i = 0;
	for (i = 0; i < offset; i++)
	{
		LcdWriteComm(0x18);  // 移动
		Delay(200);
	}
}

void LcdRightMove(int offset)
{
	int i = 0;
	for (i = 0; i < offset; i++)
	{
		LcdWriteComm(0x1C);  // 移动
		Delay(200);
	}
}

