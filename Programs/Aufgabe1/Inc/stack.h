#ifndef STACK_H
#define STACK_H

/**
 * @brief returns the top most element of the stack and removes it
 * @return int
 */
int  pop();

/**
 * @brief returns the top most element of the stack without changing the stack
 * @return int
 */
int returnFirst();

/**
 * @brief pushes an elemnt on top the stack
 * @param int
 * @return void
 */
void push(int value);  

/**
 * @brief the whole stack
 * @return int
 */
int  printStack();

/**
 * @brief fills the stack with zeros (deletes all entries)
 * @return void
 */
void stackClear();  

/**
 * @brief swaps two values
 * @param address of first and second value on the stack
 * @return void
 */
void swap(int *num1, int*num2);

#endif