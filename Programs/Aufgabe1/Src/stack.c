#include "stack.h"
#include <stdio.h>
#include "Errors.h"

#define MAX_SIZE 10

int stack[MAX_SIZE];
static int topIndex = -1;
static int num;


//PUSH
int push(int *value){
    if(isFull()){
       return STACK_OVERFLOW;
    }else{
       topIndex++;
       stack[topIndex] = *value;
       return SUCCESS;
    }
}

//POP 
int pop(int *value){
    if(isEmpty()){
      return STACK_UNDERFLOW;
    }else{
      *value = stack[topIndex];
      topIndex--;
      return SUCCESS;
    }
}

//returnFirst 
int returnFirst(){
   return stack[topIndex];
}


//printStack
void printStack(void){
     if(!isEmpty()){
        for (int i = 0; i <= topIndex; i++){
            printf("%d\t", stack[i]);
        }
     } else{
        printf("Stack is empty!");
     }
}

//swap
int swap(){
     int num1,num2;
     int res1,res2;
     res1 = pop(&num1);
     res2 = pop(&num2);
     
     if(res1 == SUCCESS && res2 == SUCCESS){
      push(&num1);
      push(&num2);
      return SUCCESS;
     }else{
      return STACK_UNDERFLOW;
     }
     
}

//duplicate
int duplicate(void){
      int num;
      // check if Stack is not empty, then pop a number to duplicate
      if(isEmpty()==SUCCESS){
           int res;
           res = pop(&num);
      } else {
         return STACK_UNDERFLOW;
      }
      
      push(&num);

      //check if Stack is not full, then push the duplicate
      if(isFull()==SUCCESS){
         push(&num);
         return SUCCESS;
      } else {
         return STACK_OVERFLOW;
      }
      
}

/*--------------------------------------------------------------------------------------------
Helper Methods
*/

void stackClear(){
    for(int i = 0; i< MAX_SIZE; i++){
       stack[i] = 0;
    }
    topIndex = -1;
    
}

int isEmpty(void){
    if(topIndex <= -1){
      return STACK_UNDERFLOW;
    }else{
        return SUCCESS;
    }
}

int isFull(){
   if(topIndex == MAX_SIZE - 1){
      return STACK_OVERFLOW;
   }else{
      return SUCCESS;
   }
}

