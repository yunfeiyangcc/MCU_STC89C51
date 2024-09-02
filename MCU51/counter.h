
#ifndef __COUNTER_HANDER_H__
#define __COUNTER_HANDER_H__

void CounterInit(unsigned char id);

void CounterStart(unsigned char id);

void CounterStop(unsigned char id);

bit CounterIsStart(unsigned char id);

void CounterClear(unsigned char id);

unsigned int CounterGet(unsigned char id);

#endif  // __COUNTER_HANDER_H__