#include "calculator.h"
#include "stack.h"
#include "Errors.h"
#include <limits.h>

//addition
int add(void){
    int ret = 0;
    int a = 0;
    int b = 0;

    ret = pop(&a);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&b);
    if(ret != SUCCESS) { return ret; }
     
    if ((b > 0 && a > INT_MAX - b) ||
        (b < 0 && a < INT_MIN - b)) {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a + b;
    push(answer);
    return SUCCESS;
}

//subtraction
int sub(void){
    int ret = 0;
    int a = 0;
    int b = 0;

    ret = pop(&b);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&a);
    if(ret != SUCCESS) { return ret; }

    if ((b > 0 && a < INT_MIN + b) ||
        (b < 0 && a > INT_MAX + b)) {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a - b;
    push(answer);
    return SUCCESS;
}

//multiplication
int mul(void){
    int ret = 0;
    int a = 0;
    int b = 0;

    ret = pop(&a);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&b);
    if(ret != SUCCESS) { return ret; }

    if(a > 0 && b > 0 && a > INT_MAX / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    if(a > 0 && b < 0 && a > INT_MIN / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    if(a < 0 && b > 0 && a > INT_MIN / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    if(a < 0 && b < 0 && a > INT_MAX / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a * b;
    push(answer);
    return SUCCESS;
}

//division
int div(void){
    int ret = 0;
    int number1 = 0;
    int number2 = 0;

    ret = pop(&number1);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&number2);
    if(ret != SUCCESS) { return ret; }

    if(number2 == INT_MIN && number1 == -1)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    if(number2 != 0){
        int answer = number2 / number1;
        push(answer);
        return SUCCESS;
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
}
