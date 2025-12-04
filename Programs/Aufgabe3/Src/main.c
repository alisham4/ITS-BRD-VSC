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

BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;
static RGBQUAD palette[256];


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	char currentChar = NULL;
	int paletteLength;
	 
	// Test in Endlosschleife
	while(1) {
		
		readInput();
		paletteLength = get_number_Of_Colors();
		COMread((char *)palette, sizeof(RGBQUAD), paletteLength);
		padding_Bytes(paletteLength);

		if(infoHeader.biCompression == 0){
			// uncompressed
			print_uncmp_picture(palette);
			}
		else {
			// compressed
			print_cmp_picture(palette);
			}
		}


		/*Coordinate crd1;
		crd1.x = 0;
		crd1.y = 0; 

		GUI_drawPoint( crd1, BLACK, 1, 1);*/
	
}

// EOF
