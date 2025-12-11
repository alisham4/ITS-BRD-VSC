#include "one_wire_bus_functions.h"
#include "stm32f429xx.h"
#include <stdbool.h>

bool reset(){
    GPIOD->BSRR = MASK_PD1 << OFFSET_16; 

}