#include "minimizePicture.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "printLine.h"
#include "math.h"
#include "readBitMap.h"

extern RGBQUAD palette[256];
extern uint8_t linesArray[5][5*480];
extern BITMAPFILEHEADER fileHeader;
extern BITMAPINFOHEADER infoHeader;

extern uint16_t displayArray[480];

bool tooBig = false;
int startY = 0;
int loopY = 0;
int box_size = 1;
float scale = 1.0;
int scaled_height;
int scaled_width;

void min_Picture(){
    if(infoHeader.biHeight > displayHeight || infoHeader.biWidth > displayWidth){
        float scale_x = (float)displayWidth / infoHeader.biWidth;
        float scale_y = (float)displayHeight / infoHeader.biHeight;

        scale = fmin(scale_x, scale_y);
        box_size = ceil(1 / scale);
        scaled_height = infoHeader.biHeight / box_size;
        scaled_width = infoHeader.biWidth / box_size;
        tooBig = true;
    }
    else {
        tooBig = false;
        box_size = 1;
        scale = 1.0;
    }

    startY = 0;
    loopY = 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int indexLine(int i) {
    return (i + loopY + 1) % 5;
}

RGBQUAD getPixel(int x, int y) {
    return palette[linesArray[indexLine(y - startY)][x]];
}

uint16_t averageColor(int x, int y, int x_end, int y_end) {
    int r = 0;
    int g = 0;
    int b = 0;
    for(int x0 = x; x0 < x_end; x++) {
        for(int y0 = y; y0 < y_end; y++) {
            RGBQUAD color = getPixel(x, y);
            r += color.rgbRed;
            g += color.rgbGreen;
            b += color.rgbBlue;
        }
    }

    int count = (x_end - x) * (y_end - y);

    r /= count;
    g /= count;
    b /= count;

    RGBQUAD farbe = { r, g, b, 0 };
    return farbeUmwandeln(farbe);
}

void minimizeLine() {
    int y = startY;
    int y_ = floor(y / scale);
    int y_end = min(y_ + box_size, scaled_height - 1);
    for(int x = 0; x < scaled_width; x++) {
        int x_ = floor(x / scale);
        int x_end = min(x_ + box_size, scaled_width - 1);
        
        uint16_t color = averageColor(x_, y_, x_end, y_end);
        displayArray[x] = color;
    }

    Coordinate crd = { 0, y };
    GUI_WriteLine(crd, scaled_width, displayArray);

    startY++;
    loopY = (loopY + 1) % 5;
}
