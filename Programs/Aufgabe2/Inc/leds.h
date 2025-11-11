#ifndef LEDS_H
#define LEDS_H


#define LED_FORWARD D23
#define LED_BACKWARD D22
#define LED_ERROR D21

#define BSSR_LED23_MASK (0x01 << (15))
#define BSSR_LED22_MASK (0x01 << (14))
#define BSSR_LED21_MASK (0x01 << (13))

/**
 * @brief turns LEDs with the given mask on
 * @param int
 */
void LED_ON(int mask);

/**
 * @brief turns LEDs off
 * @param int
 */
void LED_OFF(int mask);
#endif