#ifndef PINS_H
#define PINS_H
#include <stdbool.h>

#define IDR_MASK_PIN_A 0x01u
#define IDR_MASK_PIN_B 0x01u

/**
 * @brief reads the pin A (GPIO PF0) and returs true if pin == 1 ,false otherwise
 * @return bool
 */
bool readPinA();

/**
 * @brief reads the pin B (GPIO PF1) and returs true if pin == 1 ,false otherwise
 * @return bool
 */
bool readPinB();
#endif