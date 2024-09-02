
#ifndef __LCD_1602_HANDER_H__
#define __LCD_1602_HANDER_H__

void LcdInit();

void LcdShowChar(unsigned char row, unsigned char col, char dat);
void LcdShowCharQue(char dat);

void LcdShowString(unsigned char row, unsigned char col, const char* dat);

void LcdShowDec(unsigned char row, unsigned char col, unsigned long dat, unsigned char len);

void LcdShowSignedDec(unsigned char row, unsigned char col, long dat, unsigned char len);

void LcdShowHex(unsigned char row, unsigned char col, unsigned long dat, unsigned char len);

void LcdShowBin(unsigned char row, unsigned char col, unsigned long dat, unsigned char len);

void LcdShowFloat(unsigned char row, unsigned char col, float dat, bit showPositive);

void LcdLeftMove(int offset);

void LcdRightMove(int offset);

#endif  // __LCD_1602_HANDER_H__