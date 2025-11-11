#ifndef ERRORS_H
#define ERRORS_H

#define STACK_OVERFLOW -1
#define STACK_UNDERFLOW -2
#define DIVIDE_BY_ZERO_ERROR -3 
#define SUCCESS 0
#define ARITHEMETHIC_OVERFLOW -4

/**
* @brief prints error message on the display
* @param int 
 */
void errorMessage(int error);

#endif