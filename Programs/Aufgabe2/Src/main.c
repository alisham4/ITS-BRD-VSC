/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "calculator.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"
#include "input.h"
#include "leds.h"
#include "phaseDetector.h"
#include "timer.h"
#include <stddef.h>
#include <stdint.h>

#define TIMER_CONT (1000 * TICKS_PER_US)
extern int stepCounter;

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

  //initialize timer 
  initTimer();  
 
  uint32_t lastTime = 0;
  uint32_t startTime;
  double angle;
  bool buttonPressed = false;
  double angle1;
  double angle2;

	
	// Test in Endlosschleife
	while(1) {
		HAL_Delay(10000);

		//Direct Digital Control Concept 

		//read input (pins and time)
        startTime = getTimeStamp();
    
		readPinA();
		readPinB();

		if(checkButtonS6()){
		   buttonPressed = true;
		};
	
    
        char currentState = get_result_Phase();
        char nextState;

        //update phase 
        switch (currentState) {
            // case BACKWARD -> LED22 on 
            case BACKWARD : LED_ON(BSRR_LED22_MASK);
            break;
            //case FORWARD -> LED23 on
            case FORWARD : LED_ON(BSRR_LED23_MASK);
			break;
            //case ERROR -> LED21 on 
            case ERROR_ : LED_ON(BSRR_LED21_MASK);
            break; 
            //case NO_CHANGE ??
            case NO_CHANGE : 
            break;
        }
        
		//check if 250ms have passed
		if((startTime - lastTime) > 250 * TIMER_CONT)
		{
			// 250 ms passed
			lastTime = startTime;
			//update angular velocity
			get_angular_velocity(angle1,angle2,startTime,lastTime);
		}

		//output (turn leds on according to stepCounter) 
        GPIOD->ODR = stepCounter & 0xFF;
	}
}
