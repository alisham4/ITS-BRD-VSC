#include "stack.h"
#include <stdio.h>
#include "Errors.h"

#define MAX_SIZE 10

int stack[MAX_SIZE];
static int topIndex = -1;


//PUSH
int push(int value){
    if(isFull()){
       return STACK_OVERFLOW;
    }else{
       topIndex++;
       stack[topIndex] = value;
       return 0;
    }
}

//POP 
int pop(){
    if(isEmpty()){
      return STACK_UNDERFLOW;
    }else{
      int value = stack[topIndex];
      topIndex--;
      return value;
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
void swap(int *num1, int *num2){
     int temp;
     temp = *num1;
     *num1 = *num2;
     *num2 = temp;

}

//dublicate
int dublicate(void){
      // check if Stack is not empty, then pop a number to dublicate
      if(isEmpty==0){
         int num=pop();
      } else {
         return STACK_UNDERFLOW;
      }
      
      push(num);

      //check if Stack is not full, then push the dublicate
      if(isFull==0){
         push(num);
         return 0;
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
      return 1;
    }else{
        return 0;
    }
}

int isFull(){
   if(topIndex == MAX_SIZE){
      return 1;
   }else{
      return 0;
   }
}

