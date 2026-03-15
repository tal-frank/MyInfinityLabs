#include <stdio.h>

typedef struct max_sub
{
	int max;
	size_t start;
	size_t end;
}max_sub_t;

max_sub_t MaxSubArr(int arr[], size_t size)
{
	size_t i;
	size_t start = 0;
	int max = 0; 
	max_sub_t sub_arr = {0};

	for (i = 0; i < size; ++i)
	{
		max = 0 >= (max + arr[i]) ? 0 : max + arr[i];
		
		if (0 == max && i < (size - 1))
		{
			start = i + 1;
		}
		
		if (max > sub_arr.max)
		{
			sub_arr.max = max;
			sub_arr.start = start;
			sub_arr.end = i;
		}
	}
	return sub_arr;
}


int main()
{
	size_t arr_size = 10;
	int arr[] = {14, -5, -20, -9, 15, -3, -10, 9, -3, 8};
	max_sub_t sub_arr = {0};
	
	sub_arr = MaxSubArr(arr, arr_size);
	
	printf("max is : %d\n", sub_arr.max);
	printf("start index is : %ld\n", sub_arr.start);
	printf("end index is : %ld\n", sub_arr.end);

	return 0;
}


