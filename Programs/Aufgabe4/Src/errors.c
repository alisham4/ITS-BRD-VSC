#include "errors.h"
#include "lcd.h"

void printError(int error){
    switch(error){
        case SENSOR_NOT_CONNECTED : lcdPrintS("Sensor is not connected!");
    }
}