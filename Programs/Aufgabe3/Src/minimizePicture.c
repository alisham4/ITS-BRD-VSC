#include "minimizePicture.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "printLine.h"
#include "math.h"
#include "readBitMap.h"
#include <stdbool.h>

extern RGBQUAD palette[256];
extern uint8_t linesArray[5][5*480];
extern BITMAPFILEHEADER fileHeader;
extern BITMAPINFOHEADER infoHeader;
extern uint16_t displayArray[480];

#define MAX_BUFF_SIZE 5

uint8_t flag;

MinimizeState minState;
int yCor=320;

//Hilfsmethoden
int min(int a, int b){
    return a < b ? a : b;
}

int indexLine(int i) {
    return (i + minState.loopY) % MAX_BUFF_SIZE;
}

RGBQUAD getPixel(int x, int y) {
	int index = linesArray[indexLine(y)][x];
    return palette[index];
}


// Durchschnittsfarbe einer Box berechnen
uint16_t averageColor(int x_start, int y_start, int x_end, int y_end) {
    int r = 0, g = 0, b = 0;

    for(int y = y_start; y >= y_end; y--) {
        for(int x = x_start; x <= x_end; x++) {
            //RGBQUAD color = getPixel(x, y - minState.startY);// <-
			//int index = linesArray[y - y_end][x];
			//RGBQUAD color = palette[index];
            int lineIndex = y - minState.startY;
            RGBQUAD color = getPixel(x, lineIndex);
            r += color.rgbRed;
            g += color.rgbGreen;
            b += color.rgbBlue;
        }
    }

    int count = minState.box_size * minState.box_size;
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

    minState.startY = infoHeader.biHeight;
    minState.loopY = 0;
		flag = minState.box_size;
}

void minimizeLine() { 
    int y_orig = minState.startY;
    int y_end = y_orig - minState.box_size + 1;
    minState.startY = y_end - 1;
	
    for(int x = 0; x < minState.scaled_width; x++) {
        int x_orig = (minState.box_size * x);
		int x_end = x_orig + minState.box_size - 1;

        displayArray[x] = averageColor(x_orig, y_orig, x_end, y_end);
    }

    Coordinate crd = {0, yCor };
    GUI_WriteLine(crd, minState.scaled_width, displayArray);
    yCor--;
    //minState.startY++;
    minState.loopY = (minState.loopY + 1) % MAX_BUFF_SIZE;
		
}

/*

count in average color ist negative
y_orig, y_end, x_orig, x_end mithilfe von infoHeader.biWidth/biHeight +/- minState.box_size
L�sung
x_orig = (minState.box_size * x)
x_end = x_orig + minState.box_size - 1


*/
