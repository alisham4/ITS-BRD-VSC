#include "stack.h"
#include <stdio.h>
#include "stackErrors.h"

#define MAX_SIZE 10

int stack[MAX_SIZE];
int topIndex = -1;


int pop(){
    if(isEmpty() == 1){
       return STACK_UNDERFLOW;
    }else{
       int value;
       value = stack[topIndex];
       topIndex--;
       return value;
    }
}

int push(int value){
     if(topIndex >= MAX_SIZE){
        return STACK_OVERFLOW;
     }else{
        stack[topIndex] = value;
        topIndex++;
        return 0;
     }

}

int isEmpty(void){
    if(topIndex <= -1){
      return 1;
    }else{
        return 0;
    }
}


