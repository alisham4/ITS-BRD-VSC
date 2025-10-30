#include "Errors.h"
#include "display.h"


void errorMessage(int error){
    switch(error){
        case STACK_UNDERFLOW: printStdout("Stack Underflow!");
        break;
        case STACK_OVERFLOW : printStdout("Stack Overflow!");
        break;
        case DIVIDE_BY_ZERO_ERROR : printStdout("Division by zero is not allowed!");
        break;
        case ARITHEMETHIC_OVERFLOW: printStdout("Arithmetic overflow!");
    }
}