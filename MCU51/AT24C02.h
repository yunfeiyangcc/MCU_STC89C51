
#ifndef __AT24C02_HANDER_H__
#define __AT24C02_HANDER_H__

/*
  --------------------------------
  |           页分布             |
  --------------------------------
	|  | 高5位   地3位             |
  --------------------------------
  |0 | 00000   0 1 2 3 4 5 6 7 8 |
  |1 | 00001   0 1 2 3 4 5 6 7 8 |
  |2 | 00010   0 1 2 3 4 5 6 7 8 |
  |3 | 00011   0 1 2 3 4 5 6 7 8 |
  |4 | 00100   0 1 2 3 4 5 6 7 8 |
  |  | .....                     |
  |31| 11111   0 1 2 3 4 5 6 7 8 |
  --------------------------------
*/


void AT24C02Write(unsigned char addr, unsigned char value);

void AT24C02WriteMulti(unsigned char addr, unsigned char* value, int len);

unsigned char AT24C02Read(unsigned char addr);

unsigned char AT24C02ReadCur();

void AT24C02ReadMulti(unsigned char addr, unsigned char* value, int len);

#endif  // __AT24C02_HANDER_H__