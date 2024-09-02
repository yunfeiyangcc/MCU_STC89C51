
#ifndef __INTERRUPT_HANDER_H__
#define __INTERRUPT_HANDER_H__


typedef void (*InterruptFunc)();

void InterruptInit(unsigned char id, InterruptFunc f);

void InterruptStart(unsigned char id);

void InterruptStop(unsigned char id);

bit InterruptIsStart(unsigned char id);


#endif  // __INTERRUPT_HANDER_H__