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
#include "errors.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "one_wire_bus_functions.h"
#include "temperature_functions.h"
#include "timer.h"
#include <stdio.h>

void lcdPrintByteHex(uint8_t byte)
{
	char hex[] = "0123456789ABCDEF";
	lcdPrintC(hex[byte >> 4]);
	lcdPrintC(hex[byte & 0xF]);
}

uint8_t sensor_roms[][8] =
{
	{0x28,0x0B,0x6F,0x54,0x0F,0x00,0x00,0x11 },
	{0x28,0x40,0x97,0x54,0x0F,0x00,0x00,0x04 },
	{0x28,0x67,0xC6,0x54,0x0F,0x00,0x00,0x6F },
	{0x28,0x18,0x87,0x54,0x0F,0x00,0x00,0xF7 },
};

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initTimer();
	initOnewire();
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	
	// Test Mit mehreren Sensoren
	while(1) {
		

		for(int i = 0; i < 4; i++) {
			uint8_t *rom = sensor_roms[i];
			lcdGotoXY(0, 2 + i);
			for(int i = 0; i < 8; i++) {
				lcdPrintByteHex(rom[i]);
				lcdPrintC(' ');
			}

			float t = 0.0;
			int status = convert_T(rom, &t);
			if(status != STATUS_SUCCESS)
			{
				printError(status);
			}
			else {	
				char buf[32];
				snprintf(buf, sizeof(buf), "%6.2f C", t);
				lcdPrintS(buf);
			}
		}
	}

	uint8_t rom[8] = {0};
	// Test in Endlosschleife
	while(1) {
		//reset
		int status = reset();
		if(status != STATUS_SUCCESS){
           printError(status);
		}
		
		//read ROM command 
		readROMCommand();
		//read ROM number 
		readROMNumber(rom);
		//check CRC
		if(!checkCRC(8, rom)){
			//if CRC is not ok, then print error message on display 
			lcdPrintS("the CRC check failed!");
		} else {
			//if CRC is ok, then print the whole ROM on display 
			lcdGotoXY(10, 10);
			for(int i = 0; i < 8; i++) {
				lcdPrintByteHex(rom[i]);
				lcdPrintC(' ');
			}
		}

		float t = 0.0;
		status = convert_T(rom, &t);
		if(status != STATUS_SUCCESS)
		{
           printError(status);
		}

		char buf[32];
		snprintf(buf, sizeof(buf), "Temp: %8.2f", t);
		lcdPrintS(buf);
	}
}

// EOF
