#include "calculator.h"
#include "stack.h"
#include "Errors.h"

//addition
int add(void){
    int number1 = pop(&number1);
    int number2 = pop(&number2);
    int answer = number1+number2;
    push(&answer);
    return SUCCESS;
}

//subtraction
int sub(void){
    int number1 = pop(&number1);
    int number2 = pop(&number2);
    int answer = number1-number2;
    push(&answer);
    return SUCCESS;
}

//multiplication
int mul(void){
    int number1 = pop(&number1);
    int number2 = pop(&number2);
    int answer = number1*number2;
    push(&answer);
    return SUCCESS;
}

//division
int div(void){
    int number1 = pop(&number1);
    int number2 = pop(&number2);
    if(number2!=0){
        int answer = number1/number2;
        push(&answer);
        return SUCCESS;
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
    
}
