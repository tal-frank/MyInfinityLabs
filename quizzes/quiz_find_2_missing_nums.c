
#include <stdio.h>
#include <stddef.h>

void FindTwoMissingNums(size_t arr[], size_t size)
{
	size_t i = 0;
	size_t total_sum = 0;
	size_t arr_sum = 0;
	size_t two_nums_sum = 0;
	size_t num_avarage = 0;
	size_t first_num = 0;
	
	for (i = 1; i <= size + 2; ++i)
	{
		total_sum += i;
	}
	for (i = 0; i < size; ++i)
	{
		arr_sum += arr[i];
	}
	
	two_nums_sum = total_sum - arr_sum;
	num_avarage = two_nums_sum / 2;
	total_sum = 0;
	arr_sum = 0;
	
	for (i = 1; i <= num_avarage; ++i)
	{
		total_sum += i;
	}
	for (i = 0; i < size; ++i)
	{
		if (num_avarage >= arr[i])
		{
			arr_sum += arr[i];
		}
	}
	first_num = total_sum - arr_sum;
	printf("first missing number is : %ld\n", first_num);
	printf("second missing number is : %ld\n", two_nums_sum - first_num);
}


int main()
{
	size_t arr[10] = {4, 11, 7, 9, 3, 5, 12, 6, 8, 10};
	FindTwoMissingNums(arr, 10);
	return 0;
}
