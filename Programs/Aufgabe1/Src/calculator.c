#include "calculator.h"
#include "stack.h"
#include "Errors.h"

//addition
int add(void){
    int ret = 0;
    int number1 = 0;
    int number2 = 0;

    ret = pop(&number1);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&number2);
    if(ret != SUCCESS) { return ret; }

    int answer = number1+number2;
    push(answer);
    return SUCCESS;
}

//subtraction
int sub(void){
    int ret = 0;
    int number1 = 0;
    int number2 = 0;

    ret = pop(&number1);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&number2);
    if(ret != SUCCESS) { return ret; }

    int answer = number1-number2;
    push(answer);
    return SUCCESS;
}

//multiplication
int mul(void){
    int ret = 0;
    int number1 = 0;
    int number2 = 0;

    ret = pop(&number1);
    if(ret != SUCCESS) { return ret; }
    
    ret = pop(&number2);
    if(ret != SUCCESS) { return ret; }

    int answer = number1*number2;
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

    if(number2 != 0){
        int answer = number1/number2;
        push(answer);
        return SUCCESS;
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
}
