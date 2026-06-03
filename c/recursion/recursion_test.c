#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "recursion.c"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

void StrStrTest(char* str, char* substr)
{
	char* found_str = StrStr(str, substr);
	char* found_str_lib = strstr(str, substr);
	
	printf(CYAN "STRSTR TEST " RESET_COLOR "string %s\n" , str);
	if (NULL == found_str && NULL == found_str_lib)
	{
		printf(GREEN "---PASSED---\n" RESET_COLOR);
		printf("both strings are NULL\n");
		printf("\n");
		return;	
	}
	if (0 != StrCmp(found_str, found_str_lib))
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("Expected = %s\nActual = %s\n", found_str_lib, found_str);
		printf("\n");
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("string = %s\n", found_str);
	printf("\n");
	return;	
}

void StrLenTest(char* str)
{
	size_t size = StrLen(str);
	size_t actual_size = strlen(str);
	
	printf(CYAN "STRLEN TEST " RESET_COLOR "string %s\n" , str);
	if (size != actual_size)
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("Expected = %ld\nActual = %ld\n", actual_size, size);
		printf("\n");
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("length = %ld\n", size);
	printf("\n");
	return;	
}

void StrCmpTest(char* str1, char* str2, int expected)
{
	int compare = StrCmp(str1, str2);
	
	printf(CYAN "STRCMP TEST\n" RESET_COLOR );
	printf("string1 : %s\nstring2 : %s\n" , str1, str2);
	if (!!compare != expected)
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("Expected = %d\nActual = %d\n", expected, !!compare);
		printf("\n");
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("compare = %d\n", compare);
	printf("\n");
	return;	
}

void StrCpyTest(char* src)
{
	int compare = 0;
	char* dest = (char*)malloc(strlen(src) + 1);
	if (NULL == dest)
	{
		free(dest);
		return;
	}
	dest = StrCpy(dest, src);	
	printf(CYAN "STRCPY TEST\n" RESET_COLOR );
	printf("source : %s\n", src);

	compare = StrCmp(dest, src);
	if (0 != compare)
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("dest = %s\n", dest);
		printf("\n");
		free(dest);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("dest = %s\n", dest);
	printf("\n");
	free(dest);
	return;	
}

void StrCatTest(char* first, char* src)
{
	char* dest = (char*)malloc(strlen(src) + strlen(first) + 1);
	if (NULL == dest)
	{
		free(dest);
		return;
	}
	dest = StrCpy(dest, first);
	dest = StrCat(dest, src);
	printf(CYAN "STRCAT TEST\n" RESET_COLOR );
	printf("first part : %s\n", first);
	printf("source : %s\n", src);
	printf("first part + source = %s%s\n", first, src);
	printf("result              = %s\n", dest);
	
	printf("\n");
	free(dest);
	return;	
}

void FibonacciTest(unsigned long num)
{
	unsigned long fibo_recursive = Fibonacci(num);
	unsigned long fibo_iterative = Fibonacci_iter(num);
	
	printf(CYAN "FIBONACCI TEST " RESET_COLOR "index %ld\n" , num);
	if (fibo_recursive != fibo_iterative)
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("Expected = %ld\nActual = %ld\n", fibo_iterative, fibo_recursive);
		printf("\n");
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("result = %ld\n", fibo_recursive);
	printf("\n");
	return;	
}

void FibonacciMemoisationTest(unsigned long num, long arr[])
{
	unsigned long fibo_recursive = FibonacciMemoisation(num, arr);
	unsigned long fibo_iterative = Fibonacci_iter(num);
	
	printf(CYAN "FIBONACCI MEMOISATION TEST " RESET_COLOR "index %ld\n" , num);
	if (fibo_recursive != fibo_iterative)
	{
		printf(RED "---ERROR---\n" RESET_COLOR);
		printf("Expected = %ld\nActual = %ld\n", fibo_iterative, fibo_recursive);
		printf("\n");
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("result = %ld\n", fibo_recursive);
	printf("\n");
	return;	
}

void PrintList(node_t* node)
{
	while (NULL != node)
	{
		printf(" %d ", node->data);
		node = node->next;
	}
}

void FlipListTest(node_t* node)
{
	printf(CYAN "FLIP LIST TEST\n" RESET_COLOR);
	PrintList(node);
	printf("\n");
	node = FlipList(node);
	PrintList(node);
	printf("\n");
	printf("\n");
}

void StackSortTest(stack_t* stack)
{
	int big_num = 0;
	SortStack(stack);
	while (!StackIsEmpty(stack))
	{
		big_num = *(int*)StackPeek(stack);
		printf (" %d ", *(int*)StackPeek(stack));
		StackPop(stack);
		if (!StackIsEmpty(stack) && big_num < *(int*)StackPeek(stack))
		{
			printf(RED "---ERROR---\n" RESET_COLOR);
			printf("big_num = %d\nnext_num = %d\n", big_num, *(int*)StackPeek(stack));
			printf("\n");
			return;
		}
	}
	printf("\n");
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("stack is sorted\n");
	printf("\n");
}

int main()
{	
	int i = 0;
	char* str1 = "hello";
	char* str2 = "";
	char* str3 = "1";
	char* str4 = "12";
	char* str5 = "123";
	char* str6 = "1234";
	char* str7 = "12345";
	char* str8 = "123456";
	char* str9 = "1234567";
	char* str10 = "2345";
	char* str11 = "4567";
	char* str12 = "346";
	
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int num7 = 7;
	int num8 = 8;
	int num9 = 9;
	int num10 = 10;
	int num11 = 11;
	int num12 = 12;
	int num13 = 13;
	
	long arr[100] = {0};
		
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* node2 = (node_t*)malloc(sizeof(node_t));
	node_t* node3 = (node_t*)malloc(sizeof(node_t));
	node_t* node4 = (node_t*)malloc(sizeof(node_t));
	node_t* node5 = (node_t*)malloc(sizeof(node_t));

	stack_t* stack = StackCreate(20, sizeof(int));
	
	StackPush(stack, &num5);
	StackPush(stack, &num2);
	StackPush(stack, &num8);
	StackPush(stack, &num9);
	StackPush(stack, &num4);
	StackPush(stack, &num1);
	StackPush(stack, &num11);
	StackPush(stack, &num7);
	StackPush(stack, &num13);
	StackPush(stack, &num3);
	StackPush(stack, &num6);
	StackPush(stack, &num10);
	StackPush(stack, &num12);
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = NULL;
	
	node1->data = 1;
	node2->data = 2;
	node3->data = 3;
	node4->data = 4;
	node5->data = 5;
	
	FibonacciTest(1);
	FibonacciTest(2);
	FibonacciTest(3);
	FibonacciTest(4);
	FibonacciTest(5);
	FibonacciTest(6);
	FibonacciTest(7);
	FibonacciTest(8);
	FibonacciTest(9);
	FibonacciTest(10);
	FibonacciTest(11);
	FibonacciTest(12);
	FibonacciTest(13);
	FibonacciTest(14);
	FibonacciTest(15);
/*	FibonacciTest(40);
*/	
	StrLenTest(str1);
	StrLenTest(str2);
	StrLenTest(str3);
	StrLenTest(str4);
	StrLenTest(str5);
	StrLenTest(str6);
	StrLenTest(str7);
	StrLenTest(str8);
	StrLenTest(str9);
	
	StrCmpTest(str1, str3, 1);
	StrCmpTest(str2, str7, 1);
	StrCmpTest(str3, str3, 0);
	StrCmpTest(str7, str4, 1);
	StrCmpTest(str5, str5, 0);
	StrCmpTest(str1, str1, 0);
	StrCmpTest(str7, str1, 1);
	StrCmpTest(str2, str2, 0);
	StrCmpTest(str8, str9, 1);
	
	StrCpyTest(str1);
	StrCpyTest(str2);
	StrCpyTest(str3);
	StrCpyTest(str4);
	StrCpyTest(str5);
	StrCpyTest(str6);
	StrCpyTest(str7);
	StrCpyTest(str8);
	StrCpyTest(str9);
	
	StrCatTest(str1, str9);
	StrCatTest(str3, str8);
	StrCatTest(str4, str7);
	StrCatTest(str5, str3);
	StrCatTest(str5, str2);
	StrCatTest(str2, str6);
	StrCatTest(str2, str2);
	
	FlipListTest(node1);
	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	
	StackSortTest(stack);
	StackDestroy(stack);
	
	StrStrTest(str6, str5);
	StrStrTest(str8, str10);
	StrStrTest(str8, str12);
	StrStrTest(str9, str11);
	
	for (i = 0; i < 100; ++i)
	{
		arr[i] = -1;
	}
	

	FibonacciMemoisationTest(80, arr);
	return 0;
}
