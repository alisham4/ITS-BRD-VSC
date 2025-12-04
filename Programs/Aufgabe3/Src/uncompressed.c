#include "uncompressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "input.h"
#include <stdint.h>
#include "printLine.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern uint16_t displayArray[480];

void print_uncmp_picture(){
    
    int x;
    int y;
    int width;
    for(y=infoHeader.biHeight-1; y>=0; y--) {
        Coordinate crd = { 0, y };
        for (x = 0; x < infoHeader.biWidth; x++) {
            uint8_t farbIndex = nextChar();
            putPixel(x, farbIndex);
        }

        printLine(displayArray, crd);
        padding_Line();
    }
}

