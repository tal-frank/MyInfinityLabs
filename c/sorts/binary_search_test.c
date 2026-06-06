#include <stdio.h>
#include <time.h> /* clock */

#include "binary_search.c"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

int IntCompare(const void* num1, const void* num2)
{
	return*(int*)num1 - *(int*)num2;
}

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

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d ", arr[i]);
    }
}

static void SetRandoms(int dest[], int min, int max, size_t count) 
{
	size_t i = 0;	
	for (i = 0; i < count; ++i) 
	{
		dest[i] = rand() % (max - min + 1) + min;
	}
}

void IterBinarySearchTest(int arr[], size_t size, int target)
{
    int target_index = 0;
    target_index = IterBinarySearch(arr, size, target);
    printf("%d is at index: %d\n", target, target_index);
}

void RecBinarySearchTest(int arr[], size_t size, int target)
{
    int target_index = 0;
    target_index = BinarySearch(arr, size, target);
    printf("%d is at index: %d\n", target, target_index);
}

int main()
{
    int arr[20] = {2, 3, 4, 7, 8, 9, 12, 14, 17, 19, 23, 24, 25, 27, 30, 32, 36, 41, 43, 50};
    int merge_random_arr[50000];
    int quick_random_arr[50000];
    clock_t start = 0;
	clock_t end = 0;
	double cpu_time_used = 0;

    srand(time(NULL));
    SetRandoms(merge_random_arr, 1, 500000, 50000);
    SetRandoms(quick_random_arr, 1, 500000, 50000);

    printf(CYAN "ITERATIVE BINARY SEARCH TEST\n" RESET_COLOR);
    IterBinarySearchTest(arr, 20, 2);
    IterBinarySearchTest(arr, 20, 3);
    IterBinarySearchTest(arr, 20, 4);
    IterBinarySearchTest(arr, 20, 7);   
    IterBinarySearchTest(arr, 20, 8);
    IterBinarySearchTest(arr, 20, 9);
    IterBinarySearchTest(arr, 20, 12);
    IterBinarySearchTest(arr, 20, 14);
    IterBinarySearchTest(arr, 20, 17);
    IterBinarySearchTest(arr, 20, 19);
    IterBinarySearchTest(arr, 20, 23);
    IterBinarySearchTest(arr, 20, 24);
    IterBinarySearchTest(arr, 20, 25);
    IterBinarySearchTest(arr, 20, 27);
    IterBinarySearchTest(arr, 20, 30);
    IterBinarySearchTest(arr, 20, 32);
    IterBinarySearchTest(arr, 20, 36);
    IterBinarySearchTest(arr, 20, 41);
    IterBinarySearchTest(arr, 20, 43);
    IterBinarySearchTest(arr, 20, 50);
    IterBinarySearchTest(arr, 20, 47);
    IterBinarySearchTest(arr, 20, 16);
    IterBinarySearchTest(arr, 20, 0);
    IterBinarySearchTest(arr, 20, 6);
    IterBinarySearchTest(arr, 20, 60);
    IterBinarySearchTest(arr, 20, 1);
    IterBinarySearchTest(arr, 20, -60);

    printf("\n");

    printf(CYAN "RECURSIVE BINARY SEARCH TEST\n" RESET_COLOR);
    RecBinarySearchTest(arr, 20, 2);
    RecBinarySearchTest(arr, 20, 3);
    RecBinarySearchTest(arr, 20, 4);
    RecBinarySearchTest(arr, 20, 7);   
    RecBinarySearchTest(arr, 20, 8);
    RecBinarySearchTest(arr, 20, 9);
    RecBinarySearchTest(arr, 20, 12);
    RecBinarySearchTest(arr, 20, 14);
    RecBinarySearchTest(arr, 20, 17);
    RecBinarySearchTest(arr, 20, 19);
    RecBinarySearchTest(arr, 20, 23);
    RecBinarySearchTest(arr, 20, 24);
    RecBinarySearchTest(arr, 20, 25);
    RecBinarySearchTest(arr, 20, 27);
    RecBinarySearchTest(arr, 20, 30);
    RecBinarySearchTest(arr, 20, 32);
    RecBinarySearchTest(arr, 20, 36);
    RecBinarySearchTest(arr, 20, 41);
    RecBinarySearchTest(arr, 20, 43);
    RecBinarySearchTest(arr, 20, 50);
    RecBinarySearchTest(arr, 20, 47);
    RecBinarySearchTest(arr, 20, 16);
    RecBinarySearchTest(arr, 20, 0);
    RecBinarySearchTest(arr, 20, 6);
    RecBinarySearchTest(arr, 20, 60);
    RecBinarySearchTest(arr, 20, 1);
    RecBinarySearchTest(arr, 20, -60);

    printf("\n");
    printf(CYAN "MERGE SORT TEST\n" RESET_COLOR);
/*  
    PrintArr(random_arr, 30);
    printf("\n");
*/  
    start = clock();
    MergeSort(merge_random_arr, 50000);
/*
    qsort(random_arr, 5000, 4, IntCompare);
*/
    end = clock();
/*
    PrintArr(random_arr, 30);
    printf("\n");
*/
    SortingTest(merge_random_arr, 50000, "MERGE_SORT");
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for MERGE_SORT took %f seconds to execute \n\n", cpu_time_used);

    printf(CYAN "QUICK SORT TEST\n" RESET_COLOR);
/* 
    PrintArr(quick_random_arr, 5000);
    printf("\n");
*/  
    start = clock();
    QuickSort(quick_random_arr, 50000, 4, IntCompare);

    end = clock();
/*
    PrintArr(quick_random_arr, 5000);
    printf("\n");
*/
    SortingTest(quick_random_arr, 50000, "QUICK_SORT");
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("for QUICK SORT took %f seconds to execute \n\n", cpu_time_used);
    return 0;
}