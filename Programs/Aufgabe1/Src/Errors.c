#include "Error.h"
#include "main.c"

void errorMessage(int error){
    switch(error){
        case -1 : lcdPrintlnS("Stack Underflow!");
        break;
        case -2 : lcdPrintlnS("Stack Overflow!");
        break;
        case -3 : lcdPrintlnS("Division by zero is not allowed!");
        break;
    }
}