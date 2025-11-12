#include "leds.h"
#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"


//LED ON
void LED_ON(int mask){
    // clear all LED, before turn
    LED_OFF(BSRR_LED21_MASK);
    LED_OFF(BSRR_LED22_MASK);
    LED_OFF(BSRR_LED23_MASK);

    GPIOE->BSRR = mask;
}

//LED OFF
void LED_OFF(int mask){
    GPIOE->BSRR = mask << 16;
}


//CALCULATION OF 8 BIT BINARY NUMBERS
void step_Counter_Output(int stepCounter){
    // array to store binary number
    int length=8;
    int binaryNum[length];
    

    // counter for binary array
    int i = 0;
    while (stepCounter > 0) {
        // storing remainder in binary array
        binaryNum[i] = stepCounter % 2;
        stepCounter = stepCounter / 2;
        i++;
    }

    for(int binaryNumIndex = length; binaryNumIndex>=0; binaryNumIndex--){
        
    }
}