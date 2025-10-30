#include "Error.h"
#include "display.h"
#include "lcd.h"


void errorMessage(int error){
    switch(error){
        case -1 : printStdout("Stack Underflow!");
        break;
        case -2 : lcdPrintlnS("Stack Overflow!");
        break;
        case -3 : lcdPrintlnS("Division by zero is not allowed!");
        break;
    }
}