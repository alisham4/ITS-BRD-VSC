#ifndef ANGLECALCULATOR_H
#define ANGLECALCULATOR_H
#include <stdint.h>

#define MAX_ANGLE_LENGTH 7
#define MAX_ANGULAR_VElOCITY 7
#define ANGLE (stepCounter*0.3)

/**
* @brief calculates the angular velocity
* @param double angle, int time
* @return double
*/
double get_angular_velocity(double angle, double time);

/**
* @brief prints the angle and velocity onto the diplay
* @param char array, char arrayCopy, int lenght of array, int position of x and y , int *index 
 */
void refreshDisplay(char *array, char *arrayCopy, int maxLength, int row, int startCol, int *index);

/**
* @brief writes the angle and velocity into an char array and calls refreshDisplay()
* @param double angle, double angularVelocity
*/
void updateDisplayValues(double angle, double angularVelocity);


#endif