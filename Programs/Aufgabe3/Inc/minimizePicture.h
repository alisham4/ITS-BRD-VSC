#ifndef _MINIMIZEPICTURE_H
#define _MINIMIZEPICTURE_H
#include <stdint.h>
#include "BMP_types.h"

/*
* minimizes the picture by 1/5
*/
void min_Picture();

void minimizeLine();

uint16_t averageColor(int x, int y, int x_end, int y_end);

RGBQUAD getPixel(int x, int y);

int indexLine(int i);

int min(int a, int b);


#endif