#include "keys.h"
#include "led.h"
#include "timer.h"
#include "lcd1602.h"
#include "digitalTube.h"
#include "beep.h"

void SkeyHandler(unsigned char value, unsigned char opt)
{
// 1. 独立按键控制LED亮灭
	if (value == 1)
	{
		if (opt == 1)        // 按键1 按下
		{
			LedSetBit(1, 0);
		}
		else if (opt == 0)   // 按键1 松开
		{
			LedSetBit(1, 1);
		}
	}
// 2. 独立按键控制LED状态
	else if (value == 2)
	{
		if (opt == 0)   // 按键2 松开
		{
			LedSetBit(2, ~LedGetBit(2));
		}
	}
// 3. 独立按键控制LED显示二进制
	else if (value == 3)
	{
		if (opt == 0)   // 按键3 松开
		{
			static unsigned char ledNum = 0;
			ledNum++;
			LedSet(~ledNum);
		}
	}
// 4. 独立按键控制LED移位
	else if (value == 4)
	{
		if (opt == 0)   // 按键4 松开
		{
			static unsigned char ledNum = 0;
			if (ledNum >= 8)
				ledNum = 0;

			LedSet(~(0x01 << ledNum));
			ledNum++;
		}
	}
}

int count = 0;
void MkeyHandler(unsigned char value, unsigned char opt)
{
	if (opt == 0)
	{
		LcdShowDec(2, 3, value, 2);
		LcdShowDec(2, 9, count++, 0);
	}
}

int password = 0;
int pwCount = 0;
void MkeyPwHandler(unsigned char value, unsigned char opt)
{
	// 由于P3端口Mkey和LCD1602有冲突
	// 不用S6 S10 S14 S18按键
	unsigned char keyValue = 0;
	if (opt == 0)
	{
		if (value == 2 || value == 3 || value == 4)
		{
			keyValue = value - 1;
			pwCount++;
			if (pwCount <= 4)
			{
				password *= 10;
				password += keyValue;
			}
			LcdShowDec(2, 3, password, 4);
		}
		else if (value == 6 || value == 7 || value == 8)
		{
			keyValue = value - 2;
			pwCount++;
			if (pwCount <= 4)
			{
				password *= 10;
				password += keyValue;
			}
			LcdShowDec(2, 3, password, 4);
		}
		else if (value == 10 || value == 11 || value == 12)
		{
			keyValue = value - 3;
			pwCount++;
			if (pwCount <= 4)
			{
				password *= 10;
				password += keyValue;
			}
			LcdShowDec(2, 3, password, 4);
		}
		else if (value == 14)
		{
			keyValue = 0;
			pwCount++;
			if (pwCount <= 4)
			{
				password *= 10;
				password += keyValue;
			}
			LcdShowDec(2, 3, password, 4);
		}
		else if (value == 15)  // 确认按键
		{
			if (password == 2468)  // 秘密正确
			{
				pwCount = 0;
				password = 0;
				LcdShowDec(2, 3, password, 4);
				LcdShowString(2, 14, "OK ");
			}
			else
			{
				pwCount = 0;
				password = 0;
				LcdShowDec(2, 3, password, 4);
				LcdShowString(2, 14, "ERR");
			}
		}
		else if (value == 16)  // 取消按键
		{
				pwCount = 0;
				password = 0;
				LcdShowDec(2, 3, password, 4);
				LcdShowString(2, 14, "   ");
		}
		
		BeepClose();
	}
	else
	{
		BeepOpen();
	}
}


//void main()
void TestKeys()
{
///////////  SKEY  //////////////

//	SkeyInit(SkeyHandler);
//	
//	while(1)
//	{
//		SkeyScan();
//	}

///////////  MKEY  //////////////
// 1. 显示16个按键的键值
//	DTubeClose();
//	MkeyInit(MkeyHandler);
//	LcdInit();

//	LcdShowString(1, 3, "Hello Keys");
//	LcdShowDec(2, 3, 0, 2);
//	while(1)
//	{
//		MkeyScan();
//	}

// 2. 密码锁
	DTubeClose();
	MkeyInit(MkeyPwHandler);
	LcdInit();

	LcdShowString(1, 3, "Password:");
	LcdShowDec(2, 3, 0, 4);
	while(1)
	{
		MkeyScan();
	}
}