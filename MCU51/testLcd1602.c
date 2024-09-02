#include "lcd1602.h"
#include "digitalTube.h"
#include "timer.h"

//void main()
void TestLcd1602()
{
///////////  LCD 1602  //////////////
	DTubeClose();
	LcdInit();

//	LcdShowChar(1, 1, 'a');
//	LcdShowString(1, 1, "abcdefg hijklmn ");
//	LcdShowString(2, 1, "opq rsq uvw xyz");
//	LcdShowDec(1, 3, 678765, 8);
//	LcdShowSignedDec(1, 3, -132456, 8);
//	LcdShowSignedDec(2, 3, 132456, 8);
	
	LcdShowHex(1, 3, 0xFEDCBA, 8);
	LcdShowBin(2, 3, 0xAA, 0);

	while(1)
	{
		
	}
}