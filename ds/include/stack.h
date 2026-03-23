

#ifndef __STACK_H__
#define __STACK_H__

/********************************************************** Standard librarys */
#include <stddef.h>	/* size_t */

/******************************************************************* Struct's */


typedef struct Stack stack_t;



/*******************************************************************************
 *	Description: StackCreate() creates a stack element and allocates enugh 
 *		     memory to a stack struct with room for "capasity" number of
 *		     elements with "size_of_elemnt" size.
 *
 *	  Arguments: capacity - Capacity of the elements in the stack.
 *		     size_of_element - Size of one element in bytes.
 *
 *	     return: Pointer to new allocated stack_t pointer or NULL on Fail 
 *
 *	 Complexity: Time: O(1) space: O(n);
 *
 ******************************************************************************/
/* creates an empty stack with capacity using only one malloc */
stack_t* StackCreate(size_t capacity, size_t size_of_element);
stack_t* StackCreateOneMalloc(size_t capacity, size_t size_of_element);

/*******************************************************************************
 *	Description: StackDestroy() free's the memory segment of the 
 *		     stack element. 
 *
 *	  Arguments: stack - A defined stack pointer to free.
 *
 *	     return: void
 *
 *	 Complexity: Time: O(1)
 *
 ******************************************************************************/
 /* cleans memory and kills the stack */
void StackDestroy(stack_t* stack);
void StackDestroyOneMalloc(stack_t* stack);

/*******************************************************************************
 *	Description: StackPush() insert data to the top of the stack from void pointer type and size 
 *		     of element as chosen when the stack was created. when the stack is full it stops 
 *		     inserting data. 
 *
 *	  Arguments: data - Data to insert to the top of the stack
 *		     stack - A stack pointer to insert the data to.
 *
 *	     return: void
 *
 *	 Complexity: Time: O(1), Space: O(1)
 *
 ******************************************************************************/
 /* inserts an int value into the stack, returns 1 for success */
void StackPush(stack_t* stack, const void* data);

/*******************************************************************************
 *	Description: StackPop() removes the top data of the stack. Stops reducing when size equals 0.
 *
 *	  Arguments: stack - A stack pointer to remove the data from.
 *
 *	     return: void
 *
 *	 Complexity: time: O(1), space: O(1)
 *
 ******************************************************************************/
 /* removes the top element from the stack and returns it */
void StackPop(stack_t* stack);

/*******************************************************************************
 *	Description: StackPeek() reads the data from the top of the stack.
 *
 *	  Arguments: stack - A stack pointer to read data from.
 *
 *	     return: void
 *
 *	 Complexity: time: O(1), space: O(1)
 *
 ******************************************************************************/
 /* returns the top element of the stack */
void* StackPeek(const stack_t* stack);


/*******************************************************************************
 *	Description: StackSize() gives the value of the poiter to the top of the stack.
 *
 *	  Arguments: stack - A stack to get the top of.
 *
 *	     return:  Value of the poiter to the top of the stack.
 *
 *	 Complexity: time: O(1), space: O(1)
 *
 ******************************************************************************/
 /* returns the current number of elements in the stack */
size_t StackSize(const stack_t* stack);

/*******************************************************************************
 *	Description: StackCapacity() reveals the capacity of the stack.
 *
 *	  Arguments: stack - A stack to get the capacity of.
 *
 *	     return: Returns the capacity of the stack.
 *
 *	 Complexity: time: O(1), space: O(1)
 *
 ******************************************************************************/
 /* returns the capacity of the stack */
size_t StackCapacity(const stack_t* stack);
 
/*******************************************************************************
 *	Description: StackIsEmpty() reveals if the stack is empty.
 *
 *	  Arguments: stack - A stack to check if empty.
 *
 *	     return: 0 if the stack is not empty and one if it is.
 *
 *	 Complexity: time: O(1), space: O(1)
 *
 ******************************************************************************/
 /* returns 1 if the stack is empty and 0 if it's not */
size_t StackIsEmpty(const stack_t* stack);
 
 
#endif /** end of __STACK_H__ */
