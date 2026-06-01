
#include "stack.h"

typedef struct Node node_t;

struct Node
{
	node_t* next;
	int data;
};

/*----------------------------------------------------------------*/
/*************************** STACK SORT ***************************/
/*----------------------------------------------------------------*/

void StackBubbleSort(stack_t* stack, int* is_fliped)
{
	int big_num = *(int*)StackPeek(stack);
	int small_num = 0;
	
	StackPop(stack);	
	if (StackIsEmpty(stack))
	{
		StackPush(stack, &big_num);
		return;
	}
	
	small_num = *(int*)StackPeek(stack);
	StackPop(stack);
	if (big_num > small_num)
	{
		StackPush(stack, &small_num);
	}
	else
	{
		StackPush(stack, &big_num);
		*is_fliped = 1;
		big_num = small_num;
	}
	StackBubbleSort(stack, is_fliped);
	StackPush(stack, &big_num);
}

void SortStack(stack_t* stack)
{
	static int is_fliped = 1;
	if (0 == is_fliped)
	{
		return;
	}
	
	is_fliped = 0;
	StackBubbleSort(stack, &is_fliped);
	SortStack(stack);
}

/*---------------------------------------------------------------*/
/*************************** FLIP SORT ***************************/
/*---------------------------------------------------------------*/

node_t* FlipList(node_t* node)
{
	node_t* head = NULL;
	if (NULL == node->next)
	{
		return node;
	}
	
	head = FlipList(node->next);
	node->next->next = node;
	node->next = NULL;
	return head;
}

/*---------------------------------------------------------------*/
/*************************** FIBONACCI ***************************/
/*---------------------------------------------------------------*/

unsigned long Fibonacci_iter(unsigned int n)
{
	unsigned long i = 0;
	unsigned long prev = 1;
	unsigned long cur = 1;
	unsigned long fib = 0;
	
	if (1 >= n)
	{
		return 1;
	}
	
	for (i = 1; n > i; ++i)
	{
		fib = cur + prev;
		prev = cur;
		cur = fib;
	}
	return fib;
}


unsigned long Fibonacci(int element_index)
{
	if (1 == element_index || 0 == element_index)
	{
		return 1;
	}
	
	return Fibonacci(element_index - 1) + Fibonacci(element_index - 2);
}

/*---------------------------------------------------------------------*/
/*************************** STRING FUCTIONS ***************************/
/*---------------------------------------------------------------------*/

size_t StrLen(const char* str)
{
	if ('\0' == *str)
	{
		return 0;
	}
	
	return StrLen(++str) + 1;
}

int StrCmp(const char* str1, const char* str2)
{
	if (*str1 != *str2)
	{
		return *str1 - *str2;
	}	

	else if ('\0' == *str1)
	{
		return 0;
	}

	
	return StrCmp(++str1, ++str2);
}

char* StrCpy(char* dest, const char* src)
{
	if ('\0' == *src)
	{
		*dest = '\0';
		return dest;
	}
	
	*dest = *src;
	StrCpy(dest + 1, src + 1);
	
	return dest;
}

char* StrCat(char* dest, const char* src)
{
	if ('\0' == *dest)
	{
		StrCpy(dest, src);
	}
	else
	{
		StrCat(dest + 1, src);
	}
	
	return dest;
}

char* StrStr(const char* str, const char* substr)
{
	char* found_str = (char*)str;
	if ('\0' == *found_str || StrLen(substr) > StrLen(found_str))
	{
		return NULL;
	}
	if (0 == strncmp(found_str, substr, strlen(substr)))
	{
		return found_str;
	}
	return StrStr(str + 1, substr);
}





