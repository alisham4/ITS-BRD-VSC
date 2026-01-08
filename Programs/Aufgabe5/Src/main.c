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


#include "leds.h"
#include "phaseDetector.h"
#include "timer.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "input.h"

#define TIMER_CONT (1000 * TICKS_PER_US)
//declaration of variables stepCounter and phaseOld
extern int stepCounter, phaseOld;
extern uint32_t startTime;
extern char currentState;

int main(void) {
  initITSboard();    // Initialisierung des ITS Boards
	
  GUI_init(DEFAULT_BRIGHTNESS);   
  TP_Init(false);                 


  //initialize timer 
  initTimer();  

  
  //activate interrupt
  initISR();
 
  //initialize variables 
  uint32_t lastTime = 0;
  double angle = 0.0;
  double lastAngle = 0.0;
  double omega = 0.0;
  int phaseCurrent = 0;

  //print text on display
  lcdGotoXY(1,1);
  lcdPrintS("Angular Velocity: ");
  lcdGotoXY(1, 3);
  lcdPrintS("Angle: ");
	
	// Test in Endlosschleife
    
	while(1) {
        int buttonPressed = checkButtonS6();

		int stepCounterCopy = stepCounter;
		uint32_t startTimeCopy = startTime;
		char currentStateCopy = currentState;


        //turn leds on according to phaseChange
        switch (currentStateCopy) {
            // case BACKWARD -> LED22 on 
            case BACKWARD : LED_ON(BSRR_LED22_MASK);
            break;
            //case FORWARD -> LED23 on
            case FORWARD : LED_ON(BSRR_LED23_MASK);
			break;
            //case ERROR -> LED21 on 
            case ERROR_ : LED_ON(BSRR_LED21_MASK);
            break; 
            //case NO_CHANGE 
            case NO_CHANGE : 
            break;
        }

		
		if(currentStateCopy == ERROR_)
        {
            if(buttonPressed){
                currentState = NO_CHANGE;
                LED_OFF(BSRR_LED21_MASK);
                stepCounter = 0;
                phaseOld = -1;
            }
        }
 
		uint32_t curTime = getTimeStamp();
        
		//check timer
        angle = stepCounterCopy * 0.3;
        uint32_t time_diff = startTimeCopy - lastTime;
		uint32_t time_diff_loop = curTime - lastTime;
		
		if(time_diff_loop > 500 * TIMER_CONT)
		{
			time_diff = time_diff_loop;
			startTimeCopy = curTime;
		}

		if(time_diff > 250 * TIMER_CONT)
		{
			//update angular velocity
			omega = get_angular_velocity(angle - lastAngle, time_diff / (1000.0 * TIMER_CONT));
            lastTime = startTimeCopy;
            lastAngle = angle;
		}
        
        LED_ON_OS(0x01<<2);
        updateDisplayValues(angle, omega);
        LED_OFF(0x01<<2); 
        
		//output (turn leds on according to stepCounter)
        GPIOD->BSRR = 0xFF << 16;
        GPIOD->BSRR = stepCounterCopy & 0xFF;
	}

}
