/**********************
* Comparison Sort
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 21/05/2026
**********************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

/*------------------------------------------------------------------*/
/************************* HELPER FUNCTIONS *************************/
/*------------------------------------------------------------------*/

int IntCompare(const void* num1, const void* num2)
{
	return*(int*)num1 - *(int*)num2;
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

void SetRandoms(int dest[], int min, int max, size_t count) 
{
	size_t i = 0;	
	for (i = 0; i < count; ++i) 
	{
		dest[i] = rand() % (max - min + 1) + min;
	}
}

void SwapInts(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

/*-------------------------------------------------------------*/
/************************* BUBBLE SORT *************************/
/*-------------------------------------------------------------*/

void BubbleSort(int arr[], size_t size)
{
	size_t i = 0;
	int not_finished = 1;
	
	while (not_finished)
	{
		not_finished = 0;
		
		for (i = 0; i < (size - 1); ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				SwapInts(&arr[i], &arr[i + 1]);
				not_finished = 1;
			}
		}
	}
}

/*----------------------------------------------------------------*/
/************************* INSERTION SORT *************************/
/*----------------------------------------------------------------*/

void InsertionSort(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 0;
	for (i = 0; i < size; ++i)
	{
		while (j > 0 && (arr[j] < arr[j - 1]))
		{
			SwapInts(&arr[j], &arr[j - 1]);
			--j;
		}
		j = i + 1;
	}
}

/*----------------------------------------------------------------*/
/************************* SELECTION SORT *************************/
/*----------------------------------------------------------------*/

void SelectionSort(int arr[], size_t size)
{
	size_t place_to_insert = 1;
	size_t sorted_elements = 0;
	size_t i = 0;
	size_t max_i = 0;
	
	while (0 < place_to_insert)
	{
		place_to_insert = size - sorted_elements - 1;
		for (i = 0; i <= (place_to_insert); ++i)
		{
			if (arr[max_i] < arr[i])
			{
				max_i = i;
			}
		}
		SwapInts(&arr[place_to_insert], &arr[max_i]);
		max_i = 0;
		++sorted_elements;
	}
}

/*-------------------------------------------------------*/
/************************* TESTS *************************/
/*-------------------------------------------------------*/

void SortingTest(int arr[], size_t size, char* sort_name)
{
	size_t i = 0;
	printf(CYAN "%s\n" RESET_COLOR, sort_name);
	for (i = 0; i < (size - 1); ++i)
	{
		if (arr[i] > arr[i + 1])
		{
			printf (RED "---FAILD---\n" RESET_COLOR);
			printf ("%s did not sort crrectly\n\n", sort_name);
			return;
		}
	}
	printf (GREEN "---PASSED---\n" RESET_COLOR);
	printf ("%s sorted crrectly\n\n", sort_name);
}

/*-------------------------------------------------------*/
/************************* MAIN *************************/
/*-------------------------------------------------------*/

int main()
{
	int arr[5000];
	clock_t start = 0;
	clock_t end = 0;
	double cpu_time_used = 0;
	srand(time(NULL));
	printf("\n");
	
	SetRandoms(arr, 0, 10000, 5000);
/*	PrintArr(arr, 5000);
*/
	start = clock();
	BubbleSort(arr, 5000);
	end = clock();
/*	PrintArr(arr, 5000);
*/	SortingTest(arr, 5000, "BUBBLE SORT");
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for BUBBLE SORT took %f seconds to execute \n\n", cpu_time_used);
	
	SetRandoms(arr, 0, 10000, 5000);
/*	PrintArr(arr, 5000);
*/	
	start = clock();
	SelectionSort(arr, 5000);
	end = clock();
/*	PrintArr(arr, 5000);
*/	SortingTest(arr, 5000, "SELECTION SORT");
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for SELECTION SORT took %f seconds to execute \n\n", cpu_time_used);
	
	SetRandoms(arr, 0, 10000, 5000);
/*	PrintArr(arr, 5000);
*/
	start = clock();
	InsertionSort(arr, 5000);
	end = clock();
/*	PrintArr(arr, 5000);
*/	SortingTest(arr, 5000, "INSERTION SORT");
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for INSERTION SORT took %f seconds to execute \n\n", cpu_time_used);
	
		SetRandoms(arr, 0, 10000, 5000);
/*	PrintArr(arr, 5000);
*/
	start = clock();
	qsort(arr, 5000, 4, IntCompare);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for QSORT took %f seconds to execute \n\n", cpu_time_used);
	
	return 0;
}
