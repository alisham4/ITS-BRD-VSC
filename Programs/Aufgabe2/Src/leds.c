#include "leds.h"
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

