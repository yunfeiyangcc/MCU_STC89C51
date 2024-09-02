
#ifndef __ONE_WIRE_HANDER_H__
#define __ONE_WIRE_HANDER_H__



unsigned char OneWireInit();

void OneWireSendBit(bit value);

bit OneWireReceiveBit();

void OneWireSendByte(unsigned char value);

unsigned char OneWireReceiveByte();


#endif  // __ONE_WIRE_HANDER_H__