
#ifndef __IIC_HANDER_H__
#define __IIC_HANDER_H__

void IICInit();

void IICStart();

void IICStop();

void IICSend(unsigned char dat);

unsigned char IICReceive();


void IICSendAck(bit ack);

bit IICReceiveAck();

void IICWaitAck();


#endif  // __IIC_HANDER_H__