#include "leds.h"
#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"

//LED ON
void LED_ON(int mask){
    GPIOE->BSSR = mask;
}