#include "minimizePicture.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "printLine.h"
#include "math.h"
#include "readBitMap.h"
#include <stdint.h>

extern RGBQUAD palette[256];
extern BITMAPFILEHEADER fileHeader;
extern BITMAPINFOHEADER infoHeader;
extern uint16_t displayArray[480];

#define MAX_BUFF_SIZE 5

extern uint8_t linesArray[MAX_BUFF_SIZE][5*480];


MinimizeState minState;
uint8_t flag;

//Hilfsmethoden
int min(int a, int b){
    return a < b ? a : b;
}

int indexLine(int i) {
    return (i + minState.loopY) % MAX_BUFF_SIZE;
}

RGBQUAD getPixel(int x, int y) {
    return palette[linesArray[indexLine(y )][x]];
}


// Durchschnittsfarbe einer Box berechnen
uint16_t averageColor(int x_start, int y_start, int x_end, int y_end) {
    int r = 0, g = 0, b = 0;

    for(int y = y_start; y < y_end; y++) {
        for(int x = x_start; x < x_end; x++) {
            RGBQUAD color = getPixel(x, y- minState.startY);
            r += color.rgbRed;
            g += color.rgbGreen;
            b += color.rgbBlue;
        }
    }

    int count = (x_end - x_start) * (y_end - y_start);
    if(count == 0) count = 1;

    RGBQUAD avg = { r/count, g/count, b/count, 0 };
    return farbeUmwandeln(avg);
}

void initMinimize() {
    if(infoHeader.biHeight > displayHeight || infoHeader.biWidth > displayWidth) {
        float scaleX = (float)displayWidth/ infoHeader.biWidth;
        float scaleY = (float)displayHeight / infoHeader.biHeight;

        minState.scale = fmin(scaleX, scaleY);
        minState.box_size = ceil(1 / minState.scale);
        minState.scaled_width = infoHeader.biWidth * minState.scale;
        minState.scaled_height = infoHeader.biHeight * minState.scale;
        minState.tooBig = true;
    } else {
        minState.scale = 1.0;
        minState.box_size = 1;
        minState.scaled_width = infoHeader.biWidth;
        minState.scaled_height = infoHeader.biHeight;
        minState.tooBig = false;
    }

    minState.startY = displayHeight;
    minState.loopY = 0;
    flag = minState.box_size;
}

void minimizeLine() {
    int y = minState.startY;
    int y_orig = floor(y / minState.scale);
    int y_end  = min(y_orig + minState.box_size, infoHeader.biHeight);

    for(int x = 0; x < minState.scaled_width; x++) {
        int x_orig = floor(x / minState.scale);
        int x_end  = min(x_orig + minState.box_size, infoHeader.biWidth);

        displayArray[x] = averageColor(x_orig, y_orig, x_end, y_end);
    }

    Coordinate crd = {0, y};
    GUI_WriteLine(crd, minState.scaled_width, displayArray);

    minState.startY--;
    minState.loopY = (minState.loopY + 1) % MAX_BUFF_SIZE;
}