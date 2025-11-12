/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "pins.h"
#include "leds.h"
#include "phaseDetector.h"
#include "timer.h"

extern int stepCounter;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  //initialize timer 
  initTimer();  
 
	
	// Test in Endlosschleife
	while(1) {
		HAL_Delay(10000);

		//Direct Digital Control Concept 
    //enable timer 
    int currentTimeUpdate ; 
		//read input 
		readPinA();

		readPinB();

		//update phase 

		//output
		  
        char currentState = get_result_Phase();
        // 
        switch (currentState) {
            // case BACKWARD -> LED22 on 
            case BACKWARD : LED_ON(BSRR_LED22_MASK);
                            step_Counter_Output(stepCounter);
            break;
            //case FORWARD -> LED23 on
            case FORWARD : LED_ON(BSRR_LED23_MASK);
                            step_Counter_Output(stepCounter);
            break;
            //case ERROR -> LED21 on 
            case ERROR_ : LED_ON(BSRR_LED21_MASK);
            break; 
            //case NO_CHANGE ??
            case NO_CHANGE : 
            break;
        }
     

	}
}

// EOF
