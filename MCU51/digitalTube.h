
#ifndef __DIGITAL_TUBE_HANDER_H__
#define __DIGITAL_TUBE_HANDER_H__

void DTubeInit();

void DTubeClose();

void DTubeDisplayOne(unsigned char dat, unsigned char order);

void DTubeDisplaySingleHex(unsigned char dat, unsigned char order);

int DTubeDisplayNum(unsigned long num, unsigned char left, unsigned char dec);
int DTubeDisplayNumFix(unsigned long num, unsigned char len, unsigned char left, unsigned char dec);

void DTubeDisplayDecFix(unsigned long num, unsigned char len, unsigned char left);
void DTubeDisplayDec(unsigned long num, unsigned char left);

void DTubeDisplaySignedDec(long num);

void DTubeDisplayHexFix(unsigned long num, unsigned char len, unsigned char left);
void DTubeDisplayHex(unsigned long num, unsigned char left);

void DTubeDisplayBinFix(unsigned long num, unsigned char len, unsigned char left);
void DTubeDisplayBin(unsigned long num, unsigned char left);

void DTubeDisplayChar(unsigned char dat, unsigned char order);
void DTubeDisplayString(const char* str, unsigned char left);

#endif  // __DIGITAL_TUBE_HANDER_H__