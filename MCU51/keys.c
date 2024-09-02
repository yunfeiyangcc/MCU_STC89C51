#include "keys.h"
#include "timer.h"


KeyHandler gSkeyHandler = 0;
KeyHandler gMkeyHandler = 0;

void SkeyInit(KeyHandler handler)
{
	gSkeyHandler = handler;
}

unsigned char SkeyScan()
{
	static unsigned char key = 0;
//	MKEY_PORT = 0xFF;
	
	if (skey2 == 0)
	{
		Delay(5);
		if (skey2 == 0)
		{
			key = 1;
			if (gSkeyHandler)
				gSkeyHandler(key, 1);  // 压下
		}
		while(!skey2) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}
		Delay(5);
		while(!skey2) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}

		if (gSkeyHandler)
			gSkeyHandler(key, 0);      // 松开

	}
	else if (skey3 == 0)
	{
		Delay(5);
		if (skey3 == 0)
		{
			key = 2;
			if (gSkeyHandler)
				gSkeyHandler(key, 1);  // 压下
		}
		while(!skey3) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}
		Delay(5);
		while(!skey3) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}

		if (gSkeyHandler)
			gSkeyHandler(key, 0);      // 松开
	}
	else if (skey4 == 0)
	{
		Delay(5);
		if (skey4 == 0)
		{
			key = 3;
			if (gSkeyHandler)
				gSkeyHandler(key, 1);  // 压下
		}
		while(!skey4) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}
		Delay(5);
		while(!skey4) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}

		if (gSkeyHandler)
			gSkeyHandler(key, 0);      // 松开
	}
	else if (skey5 == 0)
	{
		Delay(5);
		if (skey5 == 0)
		{
			key = 4;
			if (gSkeyHandler)
				gSkeyHandler(key, 1);  // 压下
		}
		while(!skey5) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}
		Delay(5);
		while(!skey5) {
			if (gSkeyHandler)
				gSkeyHandler(key, 2);  // 长按
		}

		if (gSkeyHandler)
			gSkeyHandler(key, 0);      // 松开
	}

	return key;
}


// 矩阵键盘
void MkeyInit(KeyHandler handler)
{
	gMkeyHandler = handler;
}

unsigned char MkeyScan()
{
	static unsigned char key = 0;
	unsigned char tmp = 0;

	MKEY_PORT = 0xFE;
	tmp = MKEY_PORT;
	if (tmp != 0xFE)
	{
		Delay(10);
		tmp = MKEY_PORT;
		if (tmp != 0xFE)
		{
			tmp = MKEY_PORT;
			switch(tmp)
			{
			case 0xEE: key = 1; break;
			case 0xDE: key = 2; break;
			case 0xBE: key = 3; break;
			case 0x7E: key = 4; break;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 1);      // 压下

			while(tmp != 0xFE)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}
			
			Delay(10);
			tmp = MKEY_PORT;
			while(tmp != 0xFE)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 0);      // 松开
		}
	}

	MKEY_PORT = 0xFD;
	tmp = MKEY_PORT;
	if (tmp != 0xFD)
	{
		Delay(10);
		tmp = MKEY_PORT;
		if (tmp != 0xFD)
		{
			tmp = MKEY_PORT;
			switch(tmp)
			{
			case 0xED: key = 5; break;
			case 0xDD: key = 6; break;
			case 0xBD: key = 7; break;
			case 0x7D: key = 8; break;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 1);      // 压下

			while(tmp != 0xFD)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			Delay(10);
			tmp = MKEY_PORT;
			while(tmp != 0xFD)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 0);      // 松开
		}
	}

	MKEY_PORT = 0xFB;
	tmp = MKEY_PORT;
	if (tmp != 0xFB)
	{
		Delay(10);
		tmp = MKEY_PORT;
		if (tmp != 0xFB)
		{
			tmp = MKEY_PORT;
			switch(tmp)
			{
			case 0xEB: key = 9; break;
			case 0xDB: key = 10; break;
			case 0xBB: key = 11; break;
			case 0x7B: key = 12; break;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 1);      // 压下

			while(tmp != 0xFB)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			Delay(10);
			tmp = MKEY_PORT;
			while(tmp != 0xFB)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 0);      // 松开
		}
	}

	MKEY_PORT = 0xF7;
	tmp = MKEY_PORT;
	if (tmp != 0xF7)
	{
		Delay(10);
		tmp = MKEY_PORT;
		if (tmp != 0xF7)
		{
			tmp = MKEY_PORT;
			switch(tmp)
			{
			case 0xE7: key = 13; break;
			case 0xD7: key = 14; break;
			case 0xB7: key = 15; break;
			case 0x77: key = 16; break;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 1);      // 压下

			while(tmp != 0xF7)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			Delay(10);
			tmp = MKEY_PORT;
			while(tmp != 0xF7)
			{
				if (gMkeyHandler)
					gMkeyHandler(key, 2);    // 长按

				tmp = MKEY_PORT;
			}

			if (gMkeyHandler)
				gMkeyHandler(key, 0);      // 松开
		}
	}

	return key;	
}
