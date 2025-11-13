#include "calculator.h"
#include "lcd.h"
#include <stdio.h>

double omega;
void get_angular_velocity(double angle1,double angle2, int lasttime,int currenttime){

    omega = (angle1-angle2)/(lasttime-currenttime);

    
}

void print(double angle, double angular_velocity){
    static int pos = 0;

    char angle_array[MAX_ANGLE_LENGTH];
    char angle_arrayCopy[MAX_ANGLE_LENGTH];
    char angular_velocity_array[MAX_ANGULAR_VElOCITY];
    
    if(pos == 0)
    {
        snprintf(angle_array, MAX_ANGLE_LENGTH, "%6.1f", angle);
    }

    if(angle_array[pos] != angle_arrayCopy[pos])
    {
        lcdGotoXY(15 + pos, 2);
        lcdPrintC(angle_array[pos]);
        angle_arrayCopy[pos] = angle_array[pos];
    }

    pos++;
    if(pos == MAX_ANGLE_LENGTH)
    {
        pos = 0;
    }
}