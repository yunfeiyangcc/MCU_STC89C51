
#ifndef __LED_HANDER_H__
#define __LED_HANDER_H__

#include <REGX51.H>


#define LED1_8 P1
#define LED_1 P1_0
#define LED_2 P1_1
#define LED_3 P1_2
#define LED_4 P1_3
#define LED_5 P1_4
#define LED_6 P1_5
#define LED_7 P1_6
#define LED_8 P1_7

sbit LED_LE = P2^5;

void LedSet(unsigned char led);

void LedLock();

void LedUnlock();

// pos: 1 - 8
// b: 0 on, 1 off
void LedSetBit(unsigned char pos, bit b);
bit LedGetBit(unsigned char pos);

void LedWaterfallLight(int ms);
void LedWaterfallLight2(int ms);


#endif  // __LED_HANDER_H__