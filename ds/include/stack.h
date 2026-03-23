

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
 *	  Arguments: capacity - capacity of the elements in the stack.
 *		     size_of_element - size of one element in bytes.
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
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* cleans memory and kills the stack */
void StackDestroy(stack_t* stack);
void StackDestroyOneMalloc(stack_t* stack);

/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* inserts an int value into the stack, returns 1 for success */
void StackPush(stack_t* stack, const void* data);

/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* removes the top element from the stack and returns it */
void StackPop(stack_t* stack);

/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* returns the top element of the stack */
void* StackPeek(const stack_t* stack);


/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return:  
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* returns the current number of elements in the stack */
size_t StackSize(const stack_t* stack);

/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* returns the capacity of the stack */
size_t StackCapacity(const stack_t* stack);
 
/*******************************************************************************
 *	Description: StackCreate allocates memory to a stack struct with room 
 *		     for "capasity" number of elements with "size_of_elemnt" 
 *		     size.
 *
 *	  Arguments: 
 *
 *	     return: 
 *
 *	 Complexity: 
 *
 ******************************************************************************/
 /* returns 1 if the stack is empty and 0 if it's not */
size_t StackIsEmpty(const stack_t* stack);
 
 
#endif /** end of __STACK_H__ */
