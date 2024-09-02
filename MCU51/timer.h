
#ifndef __TIMER_HANDER_H__
#define __TIMER_HANDER_H__

void Delay5us();
void Delay10us();
void Delay20us();
void Delay50us();
void Delay70us();
void Delay100us();
void Delay200us();
void Delay500us();

void Delay(int ms);


#define TIMER_1MS 1024
#define TIMER_50MS 45876

typedef void (*TimerFunc)(unsigned int ms, unsigned int us);
typedef struct TimerData
{
	unsigned int timeout;
	unsigned int ms;
	unsigned int us;
	TimerFunc f;
} sTimerData;


void TimerInit(unsigned char id, unsigned int timeout, TimerFunc f);

void TimerStart(unsigned char id);

void TimerStop(unsigned char id);

bit TimerIsStart(unsigned char id);


#endif  // __TIMER_HANDER_H__