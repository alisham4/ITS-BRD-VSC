/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "BMP_types.h"
#include "LCD_general.h"
#include "headers.h"
#include "input.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;
static RGBQUAD palette[256];

uint16_t farbeUmwandeln(RGBQUAD farbe)
{
	return (farbe.rgbRed >> 3) << 11 | (farbe.rgbGreen >> 2) << 5 | (farbe.rgbBlue >> 3);
}

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	char currentChar = NULL;
	int paletteLength;
	 
	// Test in Endlosschleife
	while(1) {
		initInput();
		openNextFile();
		readHeaders();
		getFileHeader(&fileHeader);
		getInfoHeader(&infoHeader); 
		if(infoHeader.biClrUsed == 0) {
			paletteLength = 256;
		} else {
			paletteLength = infoHeader.biClrUsed;
		}

		COMread((char *)palette, sizeof(RGBQUAD), paletteLength);
		int paddingBytes = fileHeader.bfOffBits - sizeof(infoHeader) - sizeof(fileHeader) - sizeof(RGBQUAD) * paletteLength;

		for(int i = 0; i < paddingBytes; i++){
			nextChar();
		}

		int paddingLine = ((infoHeader.biWidth * 8 + 31) / 32) * 4 - infoHeader.biWidth;

		if(infoHeader.biCompression == 0){
			// uncompressed
		   	for(int y=infoHeader.biHeight-1; y>=0; y--) {
				for (int x = 0; x < infoHeader.biWidth; x++) {
					uint8_t farbIndex = nextChar();
					RGBQUAD farbe = palette[farbIndex];
					uint16_t displayFarbe = farbeUmwandeln(farbe);
					Coordinate crd = { x, y };
					GUI_drawPoint(crd, displayFarbe, DOT_PIXEL_1X1, DOT_FILL_AROUND);
				}

				for (int i = 0; i < paddingLine; i++) {
					nextChar();
				}
			}
		}
		else {
			// compressed
			int x = 0;
			int y = infoHeader.biHeight-1;
			while(true) {
				uint8_t a = nextChar();
				uint8_t b = nextChar();

				if(a == 0) {
					if(b == 0) {
						// end of line
						x = 0;
						y--;
					}
					else if(b == 1) {
						// end of file
						break;
					}
					else if(b == 2) {
						// delta
						x += nextChar();
						y -= nextChar();
					}
					else {
						// absolute mode
						for (int i = 0; i < b; i++) {
							uint8_t farbIndex = nextChar();
							RGBQUAD farbe = palette[farbIndex];
							uint16_t displayFarbe = farbeUmwandeln(farbe);
							Coordinate crd = { x, y };
							GUI_drawPoint(crd, displayFarbe, DOT_PIXEL_1X1, DOT_FILL_AROUND);
							x++;
						}

						if(b % 2 != 0)
						{
							// padding byte
							nextChar();
						}
					}
				}
				else {
					// encoded mode
					RGBQUAD farbe = palette[b];
					uint16_t displayFarbe = farbeUmwandeln(farbe);
                    for (int i = 0; i < a; i++) {
						Coordinate crd = { x, y };
						GUI_drawPoint(crd, displayFarbe, DOT_PIXEL_1X1, DOT_FILL_AROUND);
						x++;
					}
				}
			}
		}


		/*Coordinate crd1;
		crd1.x = 0;
		crd1.y = 0; 

		GUI_drawPoint( crd1, BLACK, 1, 1);*/
	}
}

// EOF
