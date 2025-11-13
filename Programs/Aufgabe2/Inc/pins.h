#ifndef PINS_H
#define PINS_H
#include <stdbool.h>


#define IDR_MASK_PIN_A (0x01u)
#define IDR_MASK_PIN_B (0x01u << (1))

/**
 * @brief reads the pin A (GPIO PF0) and returs true if pin == 1 ,false otherwise
 * @return int
 */
int readPinA();

/**
 * @brief reads the pin B (GPIO PF1) and returs true if pin == 1 ,false otherwise
 * @return int 
 */
int readPinB();
#endif
