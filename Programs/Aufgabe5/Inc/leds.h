#ifndef LEDS_H
#define LEDS_H


#define BSRR_LED23_MASK (0x01 << (7))
#define BSRR_LED22_MASK (0x01 << (6))
#define BSRR_LED21_MASK (0x01 << (5))

/**
 * @brief turns LEDs with the given mask on
 * @param int
 */
void LED_ON(int mask);


/**
 * @brief turns LEDs with the given mask off 
 * @param int
 */
void LED_OFF(int mask);

/**
 * @brief turns LED with the given mask off for time measurement 
 * @param int
 */
void LED_ON_OS(int mask);

#endif
