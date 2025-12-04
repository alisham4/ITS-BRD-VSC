#include "compressed.h"
#include "BMP_types.h"
#include "readBitMap.h"
#include "LCD_GUI.h"
#include "headers.h"
#include "input.h"
#include "printLine.h"

extern BITMAPINFOHEADER infoHeader;
extern BITMAPFILEHEADER fileHeader;
uint16_t  displayArray[480];

uint16_t farbeUmwandeln(RGBQUAD farbe)
{
	return (farbe.rgbRed >> 3) << 11 | (farbe.rgbGreen >> 2) << 5 | (farbe.rgbBlue >> 3);
}

void print_cmp_picture(RGBQUAD palette[]){

            int x = 0;
			int y = infoHeader.biHeight-1;
			while(true) {
				uint8_t a = nextChar();
				uint8_t b = nextChar();

				if(a == 0) {
					if(b == 0) {
						// end of line (a==0 && b==0)
						Coordinate crd = {0,y};
						printLine(displayArray,crd);
						x = 0;
						y--;
					}
					else if(b == 1) {
						// end of file (a==0 && b==1)
						Coordinate crd = {0,y};
						printLine(displayArray,crd);
						break;
					}
					else if(b == 2) {
						// delta
						x += nextChar();
						y -= nextChar();
					}
					else {
						// absolute mode
						Coordinate crd = {0,b};
						for (int i = 0; i < b; i++) {
							uint8_t farbIndex = nextChar();
							RGBQUAD farbe = palette[farbIndex];
							uint16_t displayFarbe = farbeUmwandeln(farbe);
							   if(x < 480){
                               displayArray[x] = displayFarbe;
                             } 
							x++;
						}
						printLine(displayArray, crd);

						if(b % 2 != 0)
						{
							// padding byte
							nextChar();
                        }
                    }
                } else {
					      // encoded mode
						 Coordinate crd = { x, a };
					        RGBQUAD farbe = palette[b];
					        uint16_t displayFarbe = farbeUmwandeln(farbe); 
                            for (int i = 0; i < a; i++) {
							if(x < 480){
                             displayArray[x] = displayFarbe;
                            }
						    printLine(displayArray,crd);
						    x++;      
                   }
				}
            }
                                    			
                                
                                
}
                