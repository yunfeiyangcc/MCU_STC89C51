#include "led.h"
#include "timer.h"

//void main()
void TestLed()
{
///////////  LED  //////////////
// 测试锁存器
// 当P2^5锁存器的LE至0时，无法操作LED
//	LedLock();
//	LedSet(0xFE);
//	Delay(3000);
//	while(1);

//	LedSet(0xF0);
//	Delay(3000);
//	LedSetBit(8, 0);
//	while(1);

	
// 测试流水灯
//	while(1)
//	{
//		LedWaterfallLight(100);
//	}
	

	while(1)
		LedWaterfallLight2(200);
}