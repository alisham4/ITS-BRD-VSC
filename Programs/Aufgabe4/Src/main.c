/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "Errors.h"
#include "crc.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "one_wire_bus_functions.h"


int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	
	// Test in Endlosschleife
	while(1) {
		//reset
		int sensor_connected = reset();

		if(sensor_connected != SENSOR_CONNECTED){
           printError(sensor_connected);
		}
		
		//read ROM command 
		readROMCommand();
		//read ROM number 
		readROMNumber();
		//check CRC
		if(!checkCRC(EIN_BYTE, reg_ROM_number)){
			//if CRC is not ok, then print error message on display 
			lcdPrintS("the CRC check failed!");
		} else {
			//if CRC is ok, then print the whole ROM on display 
			lcdGotoXY(10, 10);
			for(int i=0; i<ACHT_BYTE; i++){
				lcdPrintInt(reg_ROM_number[i]);
			}
		}
	}
}

// EOF
