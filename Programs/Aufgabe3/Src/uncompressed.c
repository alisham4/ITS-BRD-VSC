#include "uncompressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "input.h"
#include <stdint.h>
#include "printLine.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
extern uint16_t displayArray[480];

void print_uncmp_picture(RGBQUAD palette[]){
    
    int x;
    int y;
    int width;
    for(y=infoHeader.biHeight-1; y>=0; y--) {
                Coordinate crd = { 0, y };
				for (x = 0; x < infoHeader.biWidth; x++) {
					uint8_t farbIndex = nextChar();
					RGBQUAD farbe = palette[farbIndex];
					uint16_t displayFarbe = farbeUmwandeln(farbe);
                    if(x < 480){
                       displayArray[x] = displayFarbe;
                }  
			}
                printLine(displayArray,crd);
                padding_Line();
            }
        }

