#ifndef TRANSFER_H
#define TRANSFER_H
#include "Video_Code.h"
unsigned char getT(unsigned char pixels_value);
unsigned char transfer(unsigned char T_pre, int dif);
int intransfer(unsigned char T,unsigned char dif,unsigned char pixels_value);

#endif