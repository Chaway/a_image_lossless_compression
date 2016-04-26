#ifndef VIDEO_CODE_H
#define VIDEO_CODE_H
#include <stdio.h>
#include <stdlib.h>
#include "predictions.h"


#define rows 512
#define cols 512
#define num_pixels rows*cols

extern unsigned char image[rows][cols];
extern unsigned char dif[rows][cols];
extern unsigned char T[rows][cols];
extern FILE *fpi;
extern unsigned char max;
extern unsigned char min;
extern unsigned char best_pre;
extern int min_code_length;
extern char * outputname;

#endif