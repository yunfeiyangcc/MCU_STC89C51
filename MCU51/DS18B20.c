#include <REGX51.H>
#include "DS18B20.h"
#include "OneWire.h"

#define SEARCH_ROM          0xF0
#define READ_ROM            0x33
#define MATCH_ROM           0x55
#define SKIP_ROM            0xCC
#define ALARM_SEARCH        0xEC
#define CONVERT_T           0x44
#define WRITE_SCRATCHPAD    0x4E
#define READ_SCRATCHPAD     0xBE
#define COPY_SCRATCHPAD     0x48
#define RECALL_E2           0xB8
#define READ_POWER_SUPPLY   0xB4


void DS18B20ConvertT()
{
  OneWireInit();
	OneWireSendByte(SKIP_ROM);
	OneWireSendByte(CONVERT_T);
}

float DS18B20ReadT()
{
	int value = 0;
	float t = 0.0;
	
  OneWireInit();
	OneWireSendByte(SKIP_ROM);
	OneWireSendByte(READ_SCRATCHPAD);
	
	value = OneWireReceiveByte();				// LOW 8
	value |= OneWireReceiveByte() << 8; // HIGH 8
	
	t = value / 16.0;
	return t;
}