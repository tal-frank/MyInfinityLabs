
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "union.c"


int main()
{

	operation_t int_ops = {&PrintInt, &AddInt, &ClearInt};
	operation_t float_ops = {&PrintFloat, &AddFloat, &ClearFloat};
	operation_t string_ops = {&PrintString, &AddString, &ClearString};


	element_t arr[3];
	char* str = (char*)malloc(12);
	
	strcpy (str,  "hello world");
	
	arr[0].data.i = 6;
	arr[1].data.f = 6.7;
	arr[2].data.s = str;
	
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


