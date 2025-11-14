#include "calculator.h"
#include "lcd.h"
#include <stdio.h>


 

//ANGULAR VELOCITY
double get_angular_velocity(double angle1, double angle2, uint32_t lastTime, uint32_t currentTime)
{
    return (angle2 - angle1) / (currentTime - lastTime);
}


//PRINT ANGLE & ANGULAR VELOCITY ON DISPLAY
void refreshDisplay(char *array, char *arrayCopy, int maxLength, int row, int startCol, int *pos){

    if (array[*pos] != arrayCopy[*pos]) {
        lcdGotoXY(startCol + *pos, row);
        lcdPrintC(array[*pos]);
        arrayCopy[*pos] = array[*pos];
    }

    (*pos)++;
    if (*pos == maxLength) {
        *pos = 0;
    }
}

//WRITE ANGLE AND VELOCITY INTO AN ARRAY 
void updateDisplayValues(double angle, double angular_velocity){

    int posAngle = 0;
    int posVelocity = 0;

    char angle_array[MAX_ANGLE_LENGTH];
    char angle_arrayCopy[MAX_ANGLE_LENGTH];

    char angular_velocity_array[MAX_ANGULAR_VElOCITY];
    char angular_velocity_arrayCopy[MAX_ANGULAR_VElOCITY]; 

    snprintf(angle_array, MAX_ANGLE_LENGTH, "%6.1f", angle);
    snprintf(angular_velocity_array, MAX_ANGULAR_VElOCITY, "%6.1f", angular_velocity);

    refreshDisplay(angle_array, angle_arrayCopy, MAX_ANGLE_LENGTH, 2, 15, &posAngle);
    refreshDisplay(angular_velocity_array, angular_velocity_arrayCopy, MAX_ANGULAR_VElOCITY, 1, 15, &posVelocity);
}


