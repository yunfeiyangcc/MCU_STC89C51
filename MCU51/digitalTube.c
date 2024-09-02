#include <REGX51.H>
#include <string.h>
#include "digitalTube.h"
#include "timer.h"
#include "comm.h"


// 数码管
sbit DULA = P2^6;  // 段选:选择某一个数码管亮哪几段
sbit WELA = P2^7;  // 位选:选择哪个数码管亮,一共有6个数码管

unsigned char code gHexTable[] = {
	0x3F, 0x06, 0x5B, 0x4F,  // 0, 1, 2, 3
	0x66, 0x6D, 0x7D, 0x07,  // 4, 5, 6, 7
	0x7F, 0x6F, 0x77, 0x7C,  // 8, 9, A, B
	0x39, 0x5E, 0x79, 0x71,  // C, D, E, F
	0x00,                    // end
};

unsigned char code gCharTable[] = {
	0x77, 0x7C,	0x39, 0x5E, 0x79, 0x71, 0x6F,  // A, B, C, D, E, F, G
	0x76, 0x06,	0x0F, 0x40, 0x38, 0x40, 0x40,  // H, I, J, K, L, M, N
	0x3F, 0x73,	0x40, 0x40, 0x6D, 0x40,		     // O, P, Q, R, S, T
	0x37, 0x40,	0x40, 0x40, 0x40, 0x40,		     // U, V, W, X, Y, Z
	0x40, 0x00,                                // '-', end
};

unsigned char code gWeTable[] = {
	0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF
};


void DTubeInit()
{
	WELA = 0;
	DULA = 0;
}

void DTubeClose()
{
	WELA = 0;
	DULA = 0;
}

void DTubeDisplayOne(unsigned char dat, unsigned char order)
{
	DULA = 1;
	P0 = dat;
	DULA = 0;
	P0 = 0xFF;

	WELA = 1;
	P0 = order;
	WELA = 0;

	Delay(1);
}

void DTubeDisplaySingleHex(unsigned char dat, unsigned char order)
{
	DTubeDisplayOne(gHexTable[dat], gWeTable[order-1]);
}

/**
 **  num: 显示的数字
 **  left: 1 左对齐，0 右对齐
 **/
int DTubeDisplayNum(unsigned long num, unsigned char left, unsigned char dec)
{
	static unsigned long n = 0;
	static int count = 0;
	int i = 0;

	if (n != num)
	{
		count = 0;
		n = num;
		count = GetNumLen(n, dec);

		n = num;
		if (count > 6)
		{
			count = 6;
			n %= (dec == 10 ? 1000000 : dec == 16 ? 0x1000000 : 0x40);
		}
	}
	else if (num == 0)
	{
		count = 1;
	}

	DTubeDisplayNumFix(n, count, left, dec);
	
	return count;
}

/**
 **  num: 显示的数字
 **  len: 显示的数字的位数
 **  left: 1 左对齐，0 右对齐
 **/
int DTubeDisplayNumFix(unsigned long num, unsigned char len, unsigned char left, unsigned char dec)
{
	unsigned char i = 0;

	for (i = len; i > 0; --i)
	{
		if (left)
			DTubeDisplaySingleHex(num / PowL(dec, i - 1) % dec, len - i + 1);
		else
			DTubeDisplaySingleHex(num / PowL(dec, i - 1) % dec, 6 - i + 1);
	}
	
	return len;
}

/**
 **  num: 显示的数字
 **  len: 显示的数字的位数
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayDecFix(unsigned long num, unsigned char len, unsigned char left)
{
	DTubeDisplayNumFix(num, len, left, 10);
}

/**
 **  num: 显示的数字
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayDec(unsigned long num, unsigned char left)
{
	DTubeDisplayNum(num, left, 10);
}

void DTubeDisplaySignedDec(long num)
{
	int count = 0;

	if (num >= 0)
	{
		DTubeDisplayNum(num, 0, 10);
	}
	else
	{
		count = DTubeDisplayNum(-num, 0, 10);
		DTubeDisplayChar('Z', 6 - count);
	}
}

/**
 **  num: 显示的数字
 **  len: 显示的数字的位数
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayHexFix(unsigned long num, unsigned char len, unsigned char left)
{
	DTubeDisplayNumFix(num, len, left, 16);
}


/**
 **  num: 显示的数字
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayHex(unsigned long num, unsigned char left)
{
	DTubeDisplayNum(num, left, 16);
}

/**
 **  num: 显示的数字
 **  len: 显示的数字的位数
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayBinFix(unsigned long num, unsigned char len, unsigned char left)
{
	DTubeDisplayNumFix(num, len, left, 2);
}

/**
 **  num: 显示的数字
 **  left: 1 左对齐，0 右对齐
 **/
void DTubeDisplayBin(unsigned long num, unsigned char left)
{
	DTubeDisplayNum(num, left, 2);
}


void DTubeDisplayChar(unsigned char dat, unsigned char order)
{
	DTubeDisplayOne(gCharTable[dat - 'A'], gWeTable[order-1]);
}

void DTubeDisplayString(const char* str, unsigned char left)
{
	int len = 0;
	int i = 0;
	int start = 0;

	if (str == 0)
		return;

	len = strlen(str);
	if (len > 6)
	{
		start = len - 6;
	}
	for (i = start; i < len; i++)
	{
		if (left)
			DTubeDisplayChar(str[i], i + 1 - start);
		else
			DTubeDisplayChar(str[i], 6 - len + i + 1);
	}
}



