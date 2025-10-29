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
#include "stack.h"
#include "calculator.h"
#include "token.h"
#include "Errors.h"
#include "display.h"
#include "scanner.h"



int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);  
    initDisplay();          // Initialisierung des LCD Boards mit Touch

  // Begruessungstext	
	//lcdPrintlnS("Hallo liebes TI-Labor (c-project)");
	
	// Test in Endlosschleife

	// while schleife
	while(1) {
        
        //get the next token and push it onto the stack
        T_token t = nextToken();
        push(&t);

        int error;
        
	switch (t.tok) {
        case PLUS : error = add();
        break;
        case MINUS : error = sub();
        break;
        case MULT : error = mul();
        break;
        case DIV : error = div();
        break;
		case PRT : error = returnFirst();
        break;
		case PRT_ALL : printStack();
        break;
		case CLEAR : stackClear();
        break;
		case DOUBLE : error =  duplicate();
		break;
		case SWAP : error = swap();
        break;
        default: printf("The operation is undefined");
        break;
    }

    if(error!=SUCCESS){
       errorMessage(error);
    }


	}

	
    

}

// EOF
