
#include <stdio.h>
#include <string.h> /* memcpy */
#include "../include/stack.h"


int main()
{
	size_t cap = 0;
	size_t size = 0;
	int capacity = 5;
	size_t size_of_element = 4;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
/*	int num6 = 6;
	int num7 = 7;
	int num8 = 8;
	int num9 = 9;
	int num10 = 10;
*/
	stack_t* stack = StackCreateOneMalloc(capacity, size_of_element);

	if (StackIsEmpty(stack))
	{
		printf("stack is empty\n");
	}
	else
	{
		printf("stack is not empty\n");
	}

	cap = StackCapacity(stack);	
	printf("cap = %ld\n" , cap);

	StackPush(stack, &num1);	
	printf("size = %ld\n" , size);
	StackPush(stack, &num2);
	StackPush(stack, &num3);
	StackPush(stack, &num4);
	StackPush(stack, &num5);
	size = StackSize(stack);	
	
	if (StackIsEmpty(stack))
	{
		printf("stack is empty\n");
	}
	else
	{
		printf("stack is not empty\n");
	}
	

	
	num1 = *(int*)StackPeek(stack);
	printf("num1 = %d\n" , num1);
	StackPop(stack);
	
	num2 = *(int*)StackPeek(stack);
	printf("num2 = %d\n" , num2);
	StackPop(stack);
	
	num3 = *(int*)StackPeek(stack);
	printf("num3 = %d\n" , num3);
	StackPop(stack);
	
	num4 = *(int*)StackPeek(stack);
	StackPop(stack);
	printf("num4 = %d\n" , num4);
	
	num5 = *(int*)StackPeek(stack);
	printf("num5 = %d\n" , num5);
	StackPop(stack);

	size = StackSize(stack);
	printf("size = %ld\n" , size);
	
	if (StackIsEmpty(stack))
	{
		printf("stack is empty\n");
	}
	else
	{
		printf("stack is not empty\n");
	}
	
	StackDestroyOneMalloc(stack);
	
	
	
	return 0;
}
