#ifndef STACK_H
#define STACK_H

/**
 * @brief returns the top most element of the stack and removes it
 * @param int*
 * @return int
 */
int  pop(int *);

/**
 * @brief returns the top most element of the stack without changing the stack
 * @return int
 */
int returnFirst(void);

/**
 * @brief pushes an elemnt on top the stack
 * @param int*
 * @return int
 */
int push(int *value);  

/**
 * @brief the whole stack
 * @return void
 */
void  printStack(void);

/**
 * @brief fills the stack with zeros (deletes all entries)
 * @return void
 */
void stackClear(void);  

/**
 * @brief swaps two values
 * @return int
 */
int swap();

/**
 * @brief checks wheter the stack is empty or not
 * @return int
 */
int isEmpty(void);

/**
 * @brief checks wether the stack is full or not
 * @return int
 */
int isFull(void);

/**
 * @brief dublicates the top value 
 * @return int
 */
int duplicate(void);


#endif