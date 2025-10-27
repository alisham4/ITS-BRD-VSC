#include "calculator.h"
#include "stack.h"
#include "Errors.h"


int operations (String inputOperation){
    switch (inputOperation) {
        case "+" : add(void);
        break;
        case "-" : sub(void);
        break;
        case "*" : mul(void);
        break;
        case "/" : div(void);
        break;
        default: printf("The operation is undefined");
        break;
    }
}

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
    if(number2!=0){
        int answer = number1/number2;
        push(answer);
    } else {
        return DIVIDE_BY_ZERO_ERROR;
    }
    
}
