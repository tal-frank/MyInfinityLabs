
#include <stdio.h>
#include <stddef.h>

int SearchCircularArray(int arr[], size_t size, int num)
{
	size_t jump = size / 2;
	size_t index = jump;
	
	while (arr[index] > arr[(index - 1) % size] || arr[index] > arr[(index + 1) % size])
	{
		if (jump > 1)
		{
			jump /= 2;
		}
		index = (index + ((arr[0] < arr[index]) ? jump : -jump)) % size;
	}
	
	jump = (num >= arr[0]) ? (index / 2) : ((size - index) / 2);
	index = (num >= arr[0]) ? jump : (index + jump);
	if (0 == index)
	{
		index = size / 2;
		jump = index;
	}
	
	while (arr[index] != num)
	{
		if (jump > 1)
		{
			jump /= 2;
		}
		index += (num > arr[index]) ? jump : -jump;
	}
	
	return index;
}


int main()
{
/*	int arr[] = {4, 6, 8, 12, 14, 18, 23, 27, 35, 39, 51, 73, 86, 105, 135, 178, 190, 210, 248, 285};
*/	int arr[] = {135, 178, 190, 210, 248, 285, 4, 6, 8, 12, 14, 18, 23, 27, 35, 39, 51, 73, 86, 105};

/*	int arr2[] = {0, 1, 2, 3, 4, 5};
*/	int arr2[] = {2, 3, 4, 5, 0, 1};
	int index = 0;
	
	printf("\narray 1:\n");
	index = SearchCircularArray(arr, 20, 4);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 6);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 8);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 12);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 14);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 18);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 23);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 27);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 35);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 39);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 51);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 73);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 86);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 105);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 135);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 178);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 190);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 210);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 248);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr, 20, 285);
	printf("index = %d\n", index);
	
	printf("\narray 2:\n");
	
	index = SearchCircularArray(arr2, 6, 1);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr2, 6, 2);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr2, 6, 3);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr2, 6, 4);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr2, 6, 5);
	printf("index = %d\n", index);
	index = SearchCircularArray(arr2, 6, 0);
	printf("index = %d\n", index);

	return 0;
}

