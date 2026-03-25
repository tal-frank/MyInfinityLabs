/**********************
* Stack
* Author: Tal Frank
* Reviewer: Roman Polugrudov
* Last update: 25/03/2026
**********************/

#include <string.h> /* memcpy */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/stack.h"


/***************************** STACK STRUCT *****************************/

struct Stack
{
    size_t size_of_element;
    size_t size;
    size_t capacity;
    char* buffer;
};


/***************************** CREATE STACK 1 MALLOC *****************************/

stack_t* StackCreateOneMalloc(size_t capacity, size_t size_of_element)
{
	stack_t* stack = (stack_t*)malloc(sizeof(stack_t) + (size_of_element * (capacity - 1)));
	if (NULL == stack)
	{
		printf("can't creat struct\n");
		return NULL;
	}
	stack->buffer = (char*)(stack + 1);
	stack->capacity = capacity;
	stack->size_of_element = size_of_element;
	stack->size = 0;
	return stack;
}


/***************************** CREATE STACK *****************************/

stack_t* StackCreate(size_t capacity, size_t size_of_element)
{
	stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
	if (NULL == stack)
	{
		printf("can't creat struct\n");
		return NULL;
	}
	stack->buffer = (char*)malloc(size_of_element * capacity);
	if (NULL == stack->buffer)
	{
		printf("can't creat buffer\n");
		free(stack);
		return NULL;
	}
	stack->capacity = capacity;
	stack->size_of_element = size_of_element;
	stack->size = 0;
	return stack;
}


/***************************** DESTROY STACK *****************************/

void StackDestroyOneMalloc(stack_t* stack)
{
	free(stack);
}


void StackDestroy(stack_t* stack)
{
	free(stack->buffer);
	free(stack);
}


/***************************** PUSH POP PEEK *****************************/

void StackPush(stack_t* stack, const void* data)
{
	assert(NULL != stack);
	assert(NULL != data);
	
	if (stack->capacity != stack->size)
	{
		memcpy(&stack->buffer[stack->size * stack->size_of_element], 
			data, stack->size_of_element);
		stack->size += 1;
	}
}


void StackPop(stack_t* stack)
{
	assert(NULL != stack);
	if (0 != stack->size)
	{
		stack->size -= 1;
	}
}


void* StackPeek(const stack_t* stack)
{
	assert(NULL != stack);	
	
	return &stack->buffer[(stack->size - 1) * stack->size_of_element];
}


/***************************** STACK INFO *****************************/

size_t StackSize(const stack_t* stack)
{
	assert(NULL != stack);
	return stack->size;
}


size_t StackCapacity(const stack_t* stack)
{
	assert(NULL != stack);
	return stack->capacity;
}


size_t StackIsEmpty(const stack_t* stack)
{
	assert(NULL != stack);
	return 0 == stack->size;
}









