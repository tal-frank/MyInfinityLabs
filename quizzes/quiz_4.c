#include <stddef.h>
#include <stdio.h>

struct sum_of_two
{
	int index_1;
	int index_2;
	int is_sum;
};


struct sum_of_two IsSumFound (int arr[], int sum, size_t size)
{
	int i, j;
	struct sum_of_two sum_arr;
	
	sum_arr.index_1 = 0;
	sum_arr.index_2 = 0;
	sum_arr.is_sum = 0;
	i = 0;
	j = size - 1;
	
	while (j > i)
	{
		if ((arr[i] + arr[j]) == sum)
		{
			sum_arr.index_1 = i;
			sum_arr.index_2 = j;
			sum_arr.is_sum = 1;
			return sum_arr;
		}
		(arr[i] + arr[j]) > sum ? --j : ++i;
	}
	return sum_arr;
}

int main()
{
	int sum;
	int arr[] = {1,3,4,5,6,8,8,15,16,21,35};
	struct sum_of_two is_sum_found;
	
	sum = 30;
	is_sum_found = IsSumFound(arr, sum, 11);
	printf("is sum found? %d\n" , is_sum_found.is_sum);
	printf("index1 =  %d\nindex2 = %d\n" , is_sum_found.index_1, is_sum_found.index_2);
	
	return 0;
}















