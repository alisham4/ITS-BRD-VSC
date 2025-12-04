#include "uncompressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "LCD_GUI.h"
#include "headers.h"
#include "input.h"
#include <stdint.h>

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
uint16_t  displayArray[480];

uint16_t farbeUmwandeln(RGBQUAD farbe)
{
	return (farbe.rgbRed >> 3) << 11 | (farbe.rgbGreen >> 2) << 5 | (farbe.rgbBlue >> 3);
}

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
            
            if(infoHeader.biWidth < displayWidth){
               width = infoHeader.biWidth;
            }else{
               width = displayWidth;
            }
            GUI_WriteLine(crd, width, displayArray);
                padding_Line();
            }
        }

