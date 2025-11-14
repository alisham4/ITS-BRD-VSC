#ifndef ANGLECALCULATOR_H
#define ANGLECALCULATOR_H
#include <stdint.h>

#define MAX_ANGLE_LENGTH 7
#define MAX_ANGULAR_VElOCITY 11
#define ANGLE (stepCounter*0.3)

/**
* @brief calculates the angular velocity
* @param double angle, int timestamp, int stepCounter
* @return double
*/
double get_angular_velocity(double angle1, double angle2,uint32_t lasttime, uint32_t currenttime);

/**
* @brief prints the angule and velocity onto the diplay
* @param char array, char arrayCopy, int lenght of array, int position of x and y , int pos counter
 */
void refreshDisplay(char *array, char *arrayCopy, int maxLength, int row, int startCol, int *pos);

/**
* @brief writes the angle and velocity into an char array and calls refreshDisplay()
* @param double angle, double angularVelocity
*/
void updateDisplayValues(double angle, double angularVelocity);


#endif