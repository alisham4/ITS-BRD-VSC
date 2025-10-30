#include "stack.h"
#include <stdio.h>
#include "Errors.h"
#include "display.h"

#define MAX_SIZE 10

int stack[MAX_SIZE];
static int topIndex = -1;
static int num;


//PUSH
int push(int value){
    if(isFull()){
       return STACK_OVERFLOW;
    }else{
       topIndex++;
       stack[topIndex] = value;
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

int peek(int *value){
    if(isEmpty()){
      return STACK_UNDERFLOW;
    }else{
      *value = stack[topIndex];
      return SUCCESS;
    }
}

//returnFirst 
int returnFirst(){
   int value = 0;
   int err = peek(&value);
   if(err) { 
      return err; 
   }

   intTostring(value);
   return SUCCESS;
}


//printStack
void printStack(void){
   if(!isEmpty()) {
      for (int i = 0; i <= topIndex; i++) {
         intTostring(stack[i]);
      }
   }
   else {
      printStdout("Stack is empty!");
   }
}

//swap
int swap(){
     int num1,num2;
     int res1,res2;
     res1 = pop(&num1);
     res2 = pop(&num2);
     
     if(res1 == SUCCESS && res2 == SUCCESS){
      push(num1);
      push(num2);
      return SUCCESS;
     }else{
      return STACK_UNDERFLOW;
     }
     
}

//duplicate
int duplicate(void)
{
   int res = 0;
   int num = 0;

   res = pop(&num);
   if(res != SUCCESS)
   {
      return res;
   }

   push(num);
   res = push(num);
   if(res != SUCCESS)
   {
      return res;
   }

   return SUCCESS;
}

int intTostring(int value){
   char array[16];
   int len = 15;
   array[len] = '\0';
   len--;
   array[len] = '\n';
   len--;
   int zahl = value;
   do{
      int digit = value % 10;
      if(digit < 0) 
      {
         digit = -digit;
      }

      int c = digit + '0';
      array[len] = c;
      len--;
      value /= 10;
   }while(value != 0);

   if(zahl < 0)
   {
      array[len] = '-';
      len--;
   }

   // (___________1234\0)
   printStdout(array + len + 1);
   return SUCCESS;
}


/*--------------------------------------------------------------------------------------------
Helper Methods
*/

void stackClear(){
   clearStdout();
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

