#include "calculator.h"
#include "lcd.h"
#include <stdio.h>

//initialize arrays
static char angle_arrayCurrent[MAX_ANGLE_LENGTH];
static char angle_arrayOld[MAX_ANGLE_LENGTH];
static char angular_velocity_arrayCurrent[MAX_ANGULAR_VElOCITY];
static char angular_velocity_arrayOld[MAX_ANGULAR_VElOCITY]; 


//caculation of angular velocity
double get_angular_velocity(double angle, double time)
{
    return (angle) / (time);
}


//print a single character onto the display
void refreshDisplay(char *angle_arrayCurrent, char *angle_arrayOld, int maxLength, int row, int startCol, int *index){

    if (angle_arrayCurrent[*index] != angle_arrayOld[*index]) {
        lcdGotoXY(startCol + *index + 1, row);
        lcdPrintC(angle_arrayCurrent[*index]);
        angle_arrayOld[*index] = angle_arrayCurrent[*index];
    }

    (*index)++;
    if (*index == maxLength) {
      *index = 0;
    }
}

//write the value of angle and angular velocity into a char array 
void updateDisplayValues(double angle, double angular_velocity){
    static int indexAngle = 0;
    static int indexVelocity = 0;

    snprintf(angle_arrayCurrent, MAX_ANGLE_LENGTH, "%6.1f", angle);
    snprintf(angular_velocity_arrayCurrent, MAX_ANGULAR_VElOCITY, "%6.1f", angular_velocity);

    refreshDisplay(angle_arrayCurrent, angle_arrayOld, MAX_ANGLE_LENGTH, 3, 9, &indexAngle);
    refreshDisplay(angular_velocity_arrayCurrent, angular_velocity_arrayOld, MAX_ANGULAR_VElOCITY, 1, 21, &indexVelocity);
}
