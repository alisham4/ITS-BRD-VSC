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

//PEEK
int peek(int *value){
    if(isEmpty()){
      return STACK_UNDERFLOW;
    }else{
      *value = stack[topIndex];
      return SUCCESS;
    }
}

//RETURNFIRST 
int returnFirst(){
   int value = 0;
   int res = 0;
   res = peek(&value);
   if(res) { 
      return res; 
   }

   intTostring(value);
   return SUCCESS;
}


//PRINTSTACK
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


//SWAP
int swap(){
     int num1,num2;
     int res1 = 0;
     int res2 = 0;

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

//DUPLICATE
int duplicate(void)
{
   int res = 0;
   int num = 0;

   res = pop(&num);
   if(res != SUCCESS){
      return res;
   }
   push(num);

   //push second number onto the stack
   res = push(num);
   if(res != SUCCESS){
      return res;
   }

   return SUCCESS;
}

//INTTOSTRING
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
         digit = -digit;         //handling negative numbers
      }

      int c = digit + '0';
      array[len] = c;
      len--;
      value /= 10;
   }while(value != 0);

   if(zahl < 0){
      array[len] = '-';
      len--;
   }

   // (___________1234\0) 
   printStdout(array + len + 1);
   return SUCCESS;
}


//STACKCLEAR
void stackClear(){
   clearStdout();
   topIndex = -1; 
}


//ISEMPTY
int isEmpty(void){
    if(topIndex <= -1){
      return STACK_UNDERFLOW;
    }else{
        return SUCCESS;
    }
}


//ISFULL
int isFull(){
   if(topIndex == MAX_SIZE - 1){
      return STACK_OVERFLOW;
   }else{
      return SUCCESS;
   }
}

