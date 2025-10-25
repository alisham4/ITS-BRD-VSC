#include "calculator.h"
#include "stack.h"

int add(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1+number2;
    push(answer);
}

int sub(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1-number2;
    push(answer);
}

int mul(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1*number2;
    push(answer);
}

int div(void){
    int number1 = pop();
    int number2 = pop();
    int answer = number1/number2;
    push(answer);
}
