#ifndef VIDEO_DECODE_H
#define VIDEO_DECODE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "de-predictors.h"
#include "arith_code.h"

#define rows 512
#define cols 512
#define num_pixels rows*cols

extern unsigned char image[rows][cols];
extern unsigned char dif[rows][cols];
extern unsigned char T[rows][cols];
extern FILE *fpi,*fpo_decode;
extern unsigned char max;
extern unsigned char min;
extern unsigned char best_pre;
extern int min_code_length;

#endif
