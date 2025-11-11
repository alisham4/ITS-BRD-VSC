#include "leds.h"
#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"


//LED ON
void LED_ON(int mask){
    // ?????? machen clear erstmal von dem previous state und nur dann die LED anschalten/ kann man das zusammenfügen?
    LED_OFF(BSRR_LED21_MASK);
    LED_OFF(BSRR_LED22_MASK);
    LED_OFF(BSRR_LED23_MASK);

    GPIOE->BSRR = mask;
}

//LED OFF
void LED_OFF(int mask){
    GPIOE->BSRR = mask << 16;
}