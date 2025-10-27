#include "calculator.h"
#include "stack.h"
#include "Errors.h"

//addition
int add(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1+number2;
    push(answer);
}

//subtraction
int sub(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1-number2;
    push(answer);
}

//multiplication
int mul(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1*number2;
    push(answer);
}

//division
int div(void){
    int number1 = pop();
    int number2 = pop();
    if(number2!=0){
        int answer = number1/number2;
        push(answer);
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
    
}
