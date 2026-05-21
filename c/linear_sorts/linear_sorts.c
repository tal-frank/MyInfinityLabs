
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, rand */
#include <stdio.h> /* printf */
#include <time.h> /* clock */
#include <string.h> /* memcpy */

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"


/*----------------------------------------------------------------*/
/************************* HELP FUNCTIONS *************************/
/*----------------------------------------------------------------*/

void SetRandoms(int dest[], int min, int max, size_t count) 
{
	size_t i = 0;	
	for (i = 0; i < count; ++i) 
	{
		dest[i] = rand() % (max - min + 1) + min;
	}
}

void CopyArr(int arr[], int sorted_arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		arr[i] = sorted_arr[i];
	}
}

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d ", arr[i]);
	}
	printf("\n");
}

int FindMaxVal(int arr[], size_t size)
{
	size_t i = 0;
	int max = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	return max;
}

int FindMinVal(int arr[], size_t size)
{
	size_t i = 0;
	int min = arr[0];
	
	for (i = 1; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	return min;
}

size_t FindMaxMagnitude(int max_val, int base)
{
	int magnitude = 0;
	while (0 < max_val)
	{
		max_val /= base;
		++magnitude;
	}
	return magnitude;
}

/*-----------------------------------------------------------------------*/
/************************* COUNTING SORT HELPERS *************************/
/*-----------------------------------------------------------------------*/

void SetArrToZero(int* arr, size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		*arr = 0;
		++arr;
	}
}



void SetSortedArr(int dest_arr[], int sorted_arr[], size_t size, size_t sorted_size, int min_val)
{
	int cnt = 0;
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < size && j < sorted_size; ++j)
	{
		while (cnt < sorted_arr[j])
		{
			dest_arr[i] = j + min_val;
			++cnt;
			++i;
		}
	}	
}

void AddAdjacent(int count_arr[], size_t size)
{
	size_t i = 0;
	for (i = 1; i < size; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}
}

/*---------------------------------------------------------------*/
/************************* COUNTING SORT *************************/
/*---------------------------------------------------------------*/

void CountingSort(int arr[], size_t size)
{
	size_t i = 0;
	int max_val = FindMaxVal(arr, size);
	int min_val = FindMinVal(arr, size);
	size_t sorted_size = max_val - min_val + 1;
	int* sorted_arr = (int*)malloc(sizeof(int) * sorted_size);
	
	SetArrToZero(sorted_arr, sorted_size);
	for (i = 0; i < size; ++i)
	{
		++sorted_arr[arr[i] - min_val];
	}
	AddAdjacent(sorted_arr, sorted_size);
/*	for (i = 1; i < sorted_size; ++i)
	{
		sorted_arr[i] += sorted_arr[i - 1];
	}
*/	
	SetSortedArr(arr, sorted_arr, size, sorted_size, min_val);
	free(sorted_arr);
}

/*------------------------------------------------------------*/
/************************* RADIX SORT *************************/
/*------------------------------------------------------------*/

void CountingSortForRS(int arr[], size_t size, int base, int level)
{
	size_t i = 0;
	int j = 0;
	int* count_arr = (int*)malloc(sizeof(int) * base);
	int* sorted_arr = (int*)malloc(sizeof(int) * size);
	if (NULL == count_arr)
	{
		free(sorted_arr);
		return;
	}	
	if (NULL == sorted_arr)
	{
		free(count_arr);
		return;
	}

	SetArrToZero(count_arr, base);
	for (i = 0; i < size; ++i)
	{
		++count_arr[(arr[i] / level) % base];
	}
	AddAdjacent(count_arr, base);
/*
	for (j = 1; j < base; ++j)
	{
		count_arr[j] += count_arr[j - 1];
	}
*/
	for (j = size - 1; j >= 0; --j)
	{
		sorted_arr[count_arr[(arr[j] / level) % base] - 1] = arr[j];
		--count_arr[(arr[j] / level) % base];
	}
		
	CopyArr(arr, sorted_arr, size);

	free(count_arr);
	free(sorted_arr);
}

void RadixSort(int arr[], size_t size, size_t base)
{
	size_t i = 0;
	int max_val = FindMaxVal(arr, size);

	for (i = 1; (max_val / i) > 0; i *= base)
	{
		CountingSortForRS(arr, size, base, i);
	}
}

/*---------------------------------------------------------------*/
/************************* TEST FUNCTION *************************/
/*---------------------------------------------------------------*/

void SortingTest(int arr[], size_t size, char* sort_name)
{
	size_t i = 0;
	printf(CYAN "%s\n" RESET_COLOR, sort_name);
	for (i = 0; i < (size - 1); ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf (RED "---FAILD---\n" RESET_COLOR);
			printf ("%s did not sort corectly\n\n", sort_name);
			return;
		}
	}
	printf (GREEN "---PASSED---\n" RESET_COLOR);
	printf ("%s sorted corectly\n\n", sort_name);
}

/*------------------------------------------------------*/
/************************* MAIN *************************/
/*------------------------------------------------------*/

int main()
{
	int arr[5000];
	clock_t start = 0;
	clock_t end = 0;
	double cpu_time_used = 0;
	srand(time(NULL));
	printf("\n");
	
	SetRandoms(arr, 0, 500, 5000);
/*	PrintArr(arr, 5000);
*/
	start = clock();
	CountingSort(arr, 5000);
	end = clock();
/*	PrintArr(arr, 5000);
*/	SortingTest(arr, 5000, "COUNTING SORT");
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for COUNTING SORT took %f seconds to execute \n\n", cpu_time_used);
	
	SetRandoms(arr, 0, 9999999, 5000);
/*	PrintArr(arr, 20);
*/
	start = clock();
	RadixSort(arr, 5000, 10);
	end = clock();
/*	PrintArr(arr, 20);
*/	SortingTest(arr, 5000, "RADIX SORT");
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for RADIX SORT took %f seconds to execute \n\n", cpu_time_used);
	return 0;
}



