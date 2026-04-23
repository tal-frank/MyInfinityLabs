#include <stdio.h>
#include <stddef.h>

static int lut[0xFFFFFFFF] = {0};

int IsNumInArrLut(int arr[], size_t arr_size, int num)
{
	int exist = 0;
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		lut[arr[i]] = 1;
	}
	
	if (1 == lut[num])
	{
		exist = 1;
	}
	
	for (i = 0; i < 0x8FFFFFFF; ++i)
	{
		lut[i] = 0;
	}
	
	return exist;
}


int IsNumInArr(int arr[], size_t arr_size, int num)
{
	int exist = 1;
	size_t i = 0;
	
	for (i = 0; i < arr_size; ++i)
	{
		exist *= (num - arr[i]);
	}
	
	return !exist;
}


int main ()
{
	int arr[] = {2, 5, -7, 23, 78, 100, 42, 7, -73};
	int num = 73;
	
	if (1 == IsNumInArrLut(arr, 9, num) )
	{
		printf("LUT : the num %d is in arr\n", num);
	}
	
	else
	{
		printf("LUT : the num %d is not in arr\n", num);
	}
	
	if (1 == IsNumInArr(arr, 9, num) )
	{
		printf("the num %d is in arr\n", num);
	}
	
	else
	{
		printf("the num %d is not in arr\n", num);
	}
	
	return 0;
}

