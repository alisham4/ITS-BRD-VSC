#include "input.h"
#include "stm32f429xx.h"

//READ PIN A
int readPinA(){
    return (IDR_MASK_PIN_A == (GPIOF->IDR & IDR_MASK_PIN_A));
}

//READ PIN B
int readPinB(){
    return (IDR_MASK_PIN_B == (GPIOF->IDR & IDR_MASK_PIN_B));
}

//CHECK BUTTON S6 (if not equal => pressed , else not pressed)
bool checkButtonS6(){
    return (mask_S6 != (GPIOF -> IDR & mask_S6));
}
