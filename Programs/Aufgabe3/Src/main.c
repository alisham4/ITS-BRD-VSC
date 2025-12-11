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
#include "compressed.h"
#include "headers.h"
#include "input.h"
#include "printLine.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "readBitMap.h"
#include "uncompressed.h"
#include "minimizePicture.h"

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;
RGBQUAD palette[256];
extern int yCor; 
extern MinimizeState minState;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	int paletteLength;
	
	initInput();

	// Test in Endlosschleife
	while(1) {
		
		readInput(); //Bild einlesen
		paletteLength = get_number_Of_Colors(); //Länge der Palette bestimmen
		COMread((char *)palette, sizeof(RGBQUAD), paletteLength);
		padding_Bytes(paletteLength); //Anzahl der padding Bytes bestimmen, die zwischen den Header und dem "eigentlichen" Bild liegen
		
		initMinimize(); 
		
		if(minState.box_size <= 5) {
			if (infoHeader.biCompression == 0){
				// uncompressed
				print_uncmp_picture();
			}
			else {
				// compressed
				print_cmp_picture();
			}
		
		} else {
			GUI_clear(WHITE);
			
			lcdPrintS("the picture is too big!");
			lcdPrintlnS("please choose another one");
		}

		while(!(GPIOF->IDR & 1)); // wait while pressed
		while(GPIOF->IDR & 1); // wait until released
		if(1 != (GPIOF->IDR & 1)) {
			yCor=320;
			GUI_clear(WHITE);
		}
	}	
}

// EOF
