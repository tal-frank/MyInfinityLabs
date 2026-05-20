#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "bit_array.h"


int GetMissingNumberWrong(int arr[], size_t size)
{
	size_t i = 0;
	bitarray_t ba1 = 0;
	bitarray_t ba2 = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (64 <= arr[i])
		{
			ba2 = BitarraySetBitOn(ba2, arr[i] - 64);
		}
		
		else
		{
			ba1 = BitarraySetBitOn(ba2, arr[i]);
		}

	}
	
	for (i = 0; i < 64; ++i)
	{
		if (!BitarrayGetBit(ba1, i))
		{
			return i;
		}
	}
	
	for (i = 64; i < size; ++i)
	{
		if (!BitarrayGetBit(ba1, i % 64))
		{
			return i;
		}
	}
	return -1;
}

int GetMissingNumber (int arr[], size_t size)
{
	size_t i = 0;
	size_t tot_sum = 0;
	size_t arr_sum = 0;
	for (i = 0; i <= size; ++i)
	{
		tot_sum += i;
	}
	for (i = 0; i < size; ++i)
	{
		arr_sum += arr[i];
	}
	return tot_sum - arr_sum;
}

void SetRandomArr(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	int rand_num = rand() % size;
	int offset = rand() % size;
	printf ("rand_num = %d\nrand_offset = %d\n", rand_num, offset);
	for (i = 0; i < size; ++i ,++j)
	{
		if (rand_num == ((int)j + offset) % ((int)size + 1))
		{
			--i;
			continue;
		}
		arr[i] = ((int)j + offset) % ((int)size + 1);
	}
}

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d ", arr[i]);
	}
}

int main()
{
	int arr[1024];
	int missing_num = 0;
	int arr2[128];
	int missing_num2 = 0;
	srand(time(NULL));
	
	printf("\n");	
		
	SetRandomArr(arr, 1024);
	PrintArr(arr, 1024);
	printf("\n\n");
	SetRandomArr(arr2, 128);
	PrintArr(arr2, 128);
	
	missing_num = GetMissingNumber(arr, 1024);
	missing_num2 = GetMissingNumber(arr2, 128);
	
	printf("\n\n");
	
	printf("missing num is: %d\n", missing_num);
	printf("missing num 2 is: %d", missing_num2);
	
	printf("\n\n");
			
	
	
	return 0;
}

