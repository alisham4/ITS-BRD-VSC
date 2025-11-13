#ifndef ANGLECALCULATOR_H
#define ANGLECALCULATOR_H

#define MAX_ANGLE_LENGTH 7
#define MAX_ANGULAR_VElOCITY 11
#define ANGLE (stepCounter*0.3)

/**
* @brief calculates the angular velocity
* @param double angle, int timestamp, int stepCounter
*/
void get_angular_velocity(double angle1, double angle2,int lasttime, int currenttime);

/**
* @brief prints the angular velocity and time onto the display
* @param double angle , double angular_velocity
 */
void print(double angle, double angular_velocity);


#endif