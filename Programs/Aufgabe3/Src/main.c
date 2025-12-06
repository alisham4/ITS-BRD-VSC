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

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	int paletteLength;
	
	initInput();

	// Test in Endlosschleife
	while(1) {
		
		readInput();
		paletteLength = get_number_Of_Colors();
		COMread((char *)palette, sizeof(RGBQUAD), paletteLength);
		padding_Bytes(paletteLength);
		
		initMinimize();
		
		if (infoHeader.biCompression == 0){
			// uncompressed
			print_uncmp_picture();
		}
		else {
		// compressed
			print_cmp_picture();
		}

		while(!(GPIOF->IDR & 1)); // wait while pressed
		while(GPIOF->IDR & 1); // wait until released
	}


		/*Coordinate crd1;
		crd1.x = 0;
		crd1.y = 0; 

		GUI_drawPoint( crd1, BLACK, 1, 1);*/
	
}

// EOF
