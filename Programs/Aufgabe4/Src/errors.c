#include "errors.h"
#include "lcd.h"

void printError(int error){
    switch(error){
        case ERROR_NOT_CONNECTED: lcdPrintS("Not connected!"); break;
        case ERROR_CRC_CHECK: lcdPrintS("CRC error!"); break;
    }
}