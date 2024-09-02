
#ifndef __KEYS_HANDER_H__
#define __KEYS_HANDER_H__

#include <REGX51.H>


// 独立按键
sbit skey2 = P3^4;
sbit skey3 = P3^5;
sbit skey4 = P3^6;
sbit skey5 = P3^7;

#define MKEY_PORT P3

/**
 **  value: 键值: 1, 2, 3, 4
 **  opt:   操作: 1 压下, 2 长按, 0 松开
 **/
typedef void(*KeyHandler)(unsigned char value, unsigned char opt);


// 独立按键
void SkeyInit(KeyHandler handler);
unsigned char SkeyScan();

// 矩阵键盘
void MkeyInit(KeyHandler handler);
unsigned char MkeyScan();


#endif  // __KEYS_HANDER_H__