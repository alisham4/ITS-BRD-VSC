#ifndef _MINIMIZEPICTURE_H
#define _MINIMIZEPICTURE_H
#include <stdint.h>
#include "BMP_types.h"
#include "stdbool.h"

typedef struct{

    int box_size;
    float scale;
    int scaled_width;
    int scaled_height;
    int startY;
    int loopY;
    bool tooBig;
}MinimizeState;



void initMinimize();

void minimizeLine();

uint16_t averageColor(int x, int y, int x_end, int y_end);

RGBQUAD getPixel(int x, int y);

int indexLine(int i);

int min(int a, int b);


#endif