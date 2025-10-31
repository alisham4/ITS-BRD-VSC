#include "calculator.h"
#include "stack.h"
#include "Errors.h"
#include <limits.h>

//ADDITION
int add(void){
    int res = 0;
    int a = 0;
    int b = 0;

    res = pop(&a);
    if(res!= SUCCESS) {
         return res; 
    }
    
    res = pop(&b);
    if(res != SUCCESS) { 
        return res;
    }
     
    //check limits
    if ((b > 0 && a > INT_MAX - b) ||
        (b < 0 && a < INT_MIN - b)) {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a + b;
    push(answer);
    return SUCCESS;
}


//SUBTRACTION
int sub(void){
    int res = 0;
    int a = 0;
    int b = 0;

    res = pop(&b);
    if(res != SUCCESS) {
        return res;
     }
    
    res = pop(&a);
    if(res != SUCCESS) {
       return res;
    }
    
    //check limits
    if ((b > 0 && a < INT_MIN + b) ||
        (b < 0 && a > INT_MAX + b)) {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a - b;
    push(answer);
    return SUCCESS;
}


//MULTIPLICATION
int mul(void){
    int res = 0;
    int a = 0;
    int b = 0;

    res = pop(&a);
    if(res != SUCCESS) {
        return res;
    }
    
    res = pop(&b);
    if(res != SUCCESS) {
        return res;
    }
    
    //check limits
    //case1:
    if(a > 0 && b > 0 && a > INT_MAX / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }
    //case2:
    if(a > 0 && b < 0 && a > INT_MIN / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }
    //case3:
    if(a < 0 && b > 0 && a > INT_MIN / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }
    //case4:
    if(a < 0 && b < 0 && a > INT_MAX / b)
    {
        return ARITHEMETHIC_OVERFLOW;
    }

    int answer = a * b;
    push(answer);
    return SUCCESS;
}


//DIVISION
int div(void){
    int res = 0;
    int number1 = 0;
    int number2 = 0;

    res = pop(&number1);
    if(res != SUCCESS) {
        return res; 
    }
    
    res = pop(&number2);
    if(res != SUCCESS) {
        return res; 
    }
    
    //check limits
    if(number2 == INT_MIN && number1 == -1)
    {
        return ARITHEMETHIC_OVERFLOW;
    }
    //check division by zero
    if(number2 != 0){
        int answer = number2 / number1;
        push(answer);
        return SUCCESS;
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
}
