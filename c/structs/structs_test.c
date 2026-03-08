/**********************
 * structs
 * Author: Tal Frank
 * Reviewer: Name
**********************/


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "structs.c"


int main()
{

	operation_t int_ops = {&PrintInt, &AddInt, &ClearInt};
	operation_t float_ops = {&PrintFloat, &AddFloat, &ClearFloat};
	operation_t string_ops = {&PrintString, &AddString, &ClearString};


	element_t arr[3];
	char* str = (char*)malloc(12);
	int max, max3;
	int a = 5, b = 10, c = 13;
	
	strcpy (str,  "hello world");

	max = MAX(a, b);
	max3 = MAX3(a, b, c);
	printf("the max is %d\n", max);
	printf("the max3 is %d\n", max3);
	printf("variable size is %ld\n", SIZEOF(arr[0]));
	printf("type size is %ld\n", TYPE_SIZEOF(double));
	
	*(int*)&arr[0].data = 6;
	*(float*)&arr[1].data = 6.7;
	*(char**)&arr[2].data = str;
	
	arr[0].op = &int_ops;
	arr[1].op = &float_ops;
	arr[2].op = &string_ops;
	
	PrintAll(arr, 3);
	AddAll(arr, 3, 107);
	PrintAll(arr, 3);
	Clear(arr, 3);
	PrintAll(arr, 3);
	
	
	return 0;
}












