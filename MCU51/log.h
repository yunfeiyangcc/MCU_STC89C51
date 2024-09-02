
#ifndef __LOG_HANDER_H__
#define __LOG_HANDER_H__

#include "uart.h"

#define LOG_OPEN 1

#if LOG_OPEN == 1
#define LOG UartPrintf
#else
#define LOG 
#endif


#endif  // __LOG_HANDER_H__