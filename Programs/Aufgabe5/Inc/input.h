#ifndef PINS_H
#define PINS_H
#include <stdbool.h>


#define IDR_MASK_PIN_A (0x01u)
#define IDR_MASK_PIN_B (0x01u << (1))
#define mask_S6 (0x01u << 6)

/**
 * @brief reads the pin A (GPIO PF0) and returs true if pin == 1 ,false  otherwise
 * @return int pin
 */
int readPinA();

/**
 * @brief reads the pin B (GPIO PF1) and returs true if pin == 1 ,false otherwise
 * @return int 
 */
int readPinB();

/**
* @brief checks if S6 is pressed or not
* @return bool (1 => pressed , 0 => not pressed)
 */
bool checkButtonS6();


#endif
