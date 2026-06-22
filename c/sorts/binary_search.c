/**********************
* binary search
* Author: Tal Frank
* Reviewer: Or Zellner
* Last update: 21/06/2026
**********************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc , free */
#include <assert.h> /* assert */

#include "binary_search.h"

#define MIN(num1, num2) (((num1) < (num2)) ? (num1) : (num2))

enum Status
{
    FAILURE = -1,
    SUCCESS
};

/*-----------------------------------------------------------------------------------------*/
/****************************** STATIC FUNCTIONS DECLARATIONS ******************************/
/*-----------------------------------------------------------------------------------------*/

static int RecBinarySearch(int* arr, int start, int size, int target);
static void SortPartitions(int arr[], int buffer[], int num_of_elements);
static void CopyArray(int arr[], int buffer[], int num_of_elements);
static size_t GetPivot(size_t number_of_elements);
static void SwapElements(char* element1, char* element2, size_t size_of_element);
static void MergeSortHelper (int arr[], int num_of_elements, int* buffer);

static void SortAroundPivot(void* arr, 
                            size_t* pivot,
                            size_t number_of_elements, 
                            size_t size_of_element, 
                            int (*cmp_func)(const void* num1, const void* num2));
static void PivotMovingSort(char* arr_runner, 
                            size_t start, 
                            size_t end, 
                            size_t* pivot,
                            size_t size_of_element,
                            int (*cmp_func)(const void* num1, const void* num2));

/*-----------------------------------------------------------------------------------*/
/****************************** BINARY SEARCH ITERATIVE ******************************/
/*-----------------------------------------------------------------------------------*/

int IterBinarySearch(const int* arr, size_t size, int target)
{
    size_t start = 0;
    size_t end = size - 1;
    size_t search_index = 0;

    assert (NULL != arr);

    while (start <= end && ((size_t) - 1) != end)
    {
        search_index = (start + end) / 2;
        
        if (target == arr[search_index])
        {
            return search_index;
        }

        if (target > arr[search_index])
        {
            start = search_index + 1;
        }
        else
        {
            end = search_index - 1;
        }
    }
    return FAILURE;
}

/*-----------------------------------------------------------------------------------*/
/****************************** BINARY SEARCH RECURSIVE ******************************/
/*-----------------------------------------------------------------------------------*/

int BinarySearch(const int* arr, int size, int target)
{
    assert (NULL != arr);
    
    return RecBinarySearch((int*)arr, 0, size - 1, target);
}

static int RecBinarySearch(int* arr, int start, int size, int target)
{
    int search_index = 0;

    assert (NULL != arr);

    search_index = (start + size) / 2;

    if (target == arr[search_index])
    {
        return search_index;
    }
    else if (start >= size)
    {
        return FAILURE;
    }
    else if (target > arr[search_index])
    {
        return RecBinarySearch(arr, search_index + 1, size, target);
    }
    else
    {
        return RecBinarySearch(arr, start, search_index - 1, target);
    }
}

/*----------------------------------------------------------------------*/
/****************************** MERGE SORT ******************************/
/*----------------------------------------------------------------------*/

int MergeSort (int arr[], int num_of_elements)
{
    int* buffer = 0;

    assert(NULL != arr);

    buffer = (int*)malloc(num_of_elements * sizeof(int));
    if (NULL == buffer)
    {
        return FAILURE;
    }

    MergeSortHelper (arr, num_of_elements, buffer);
    free(buffer);
    return SUCCESS;
}

static void MergeSortHelper (int arr[], int num_of_elements, int* buffer)
{
    int half_elements = num_of_elements / 2;

    assert(NULL != arr);

    if (1 == num_of_elements)
    {
        return;
    }
    
    MergeSortHelper(arr, half_elements, buffer);
    MergeSortHelper(arr + (half_elements), num_of_elements - (half_elements), buffer);

    SortPartitions(arr, buffer, num_of_elements);
    CopyArray(arr, buffer, num_of_elements);
}

/*----------------------------------------------------------------------*/
/****************************** QUICK SORT ******************************/
/*----------------------------------------------------------------------*/

void QuickSort(void* arr, 
               size_t number_of_elements, 
               size_t size_of_element, 
               int (*cmp_func)(const void* num1, const void* num2))
{
    size_t pivot = 0;

    assert(NULL != arr);
    assert(NULL != cmp_func);

    if (1 >= number_of_elements)
    {
        return;
    }

    pivot = GetPivot(number_of_elements);

    SortAroundPivot(arr, &pivot, number_of_elements, size_of_element, cmp_func);

    QuickSort(arr, 
              pivot, 
              size_of_element, 
              cmp_func);

    QuickSort((void*)((char*)arr + ((pivot + 1) * size_of_element)), 
              number_of_elements - (pivot + 1), 
              size_of_element, 
              cmp_func);
}

/*----------------------------------------------------------------------------*/
/****************************** STATIC FUNCTIONS ******************************/
/*----------------------------------------------------------------------------*/

static void SortPartitions(int arr[], int buffer[], int num_of_elements)
{
    int i = 0;
    int j = 0;
    int half_elements = num_of_elements / 2;
    int k = half_elements;
    
    while (half_elements > j && num_of_elements > (k))
    {
        buffer[i++] = MIN(arr[j], arr[k]);
        (arr[j] > arr[k]) ? ++k : ++j;      
    }

    while(half_elements > j)
    {
        buffer[i++] = arr[j++];
    }

    while (num_of_elements > (k))
    {
        buffer[i++] = arr[k++];
    }
}

static void CopyArray(int arr[], int buffer[], int num_of_elements)
{
    int i = 0;
    for(i = 0; i < num_of_elements; ++i)
    {
        arr[i] = buffer[i];
    }
}

static size_t GetPivot(size_t number_of_elements)
{
    return rand() % (number_of_elements);
}

static void SortAroundPivot(void* arr, 
                            size_t* pivot,
                            size_t number_of_elements, 
                            size_t size_of_element, 
                            int (*cmp_func)(const void* num1, const void* num2))
{
    size_t start = 0;
    size_t end = number_of_elements - 1;
    char* arr_runner = (char*)arr;
    size_t start_index = 0;
    size_t pivot_index = 0;
    size_t end_index = 0;

    while (*pivot != start && *pivot != end)
    {
        start_index = start * size_of_element;
        pivot_index = *pivot * size_of_element;
        end_index = end * size_of_element;
        if (0 > cmp_func(&arr_runner[pivot_index], 
                         &arr_runner[start_index]) 
         && 0 <= cmp_func(&arr_runner[pivot_index], 
                          &arr_runner[end_index]))
        {
            SwapElements(&arr_runner[start_index], 
                         &arr_runner[end_index], 
                         size_of_element);
        }
        else
        {
            start = (0 < cmp_func(&arr_runner[start_index], 
                                  &arr_runner[pivot_index])) ? 
                                  start : start + 1;
            end = (0 >= cmp_func(&arr_runner[end_index], 
                                 &arr_runner[pivot_index])) ? 
                                 end : end - 1;
        }
    }
    
    PivotMovingSort(arr_runner, start, end, pivot, size_of_element, cmp_func);
}

static void SwapElements(char* element1, char* element2, size_t size_of_element)
{
    size_t i = 0;
    char temp = 0;
    for(i = 0; i < size_of_element; ++i)
    {
        temp = *element1; 
        *element1 = *element2;
        *element2 = temp;
        element1 += 1;
        element2 += 1;
    }
}

static void PivotMovingSort(char* arr_runner, 
                            size_t start, 
                            size_t end, 
                            size_t* pivot,
                            size_t size_of_element,
                            int (*cmp_func)(const void* num1, const void* num2))
{
    size_t i = 1;
    while (*pivot >= start + i)
    {
        if (0 > cmp_func(&arr_runner[*pivot * size_of_element], 
                         &arr_runner[(*pivot - i) * size_of_element]))
        {
            SwapElements(&arr_runner[(*pivot - 1) * size_of_element], 
                         &arr_runner[(*pivot - i) * size_of_element], 
                         size_of_element);
            SwapElements(&arr_runner[*pivot * size_of_element], 
                         &arr_runner[(*pivot - 1) * size_of_element], 
                         size_of_element);
            *pivot -= 1;
            i -= 1;
        }
        ++i;
    }

    while (*pivot + i <= end)
    {
        if (0 < cmp_func(&arr_runner[*pivot * size_of_element], 
                        &arr_runner[(*pivot + i) * size_of_element]))
        {
            SwapElements(&arr_runner[(*pivot + 1) * size_of_element], 
                         &arr_runner[(*pivot + i) * size_of_element], 
                         size_of_element);
            SwapElements(&arr_runner[*pivot * size_of_element], 
                         &arr_runner[(*pivot + 1) * size_of_element], 
                         size_of_element);
            *pivot += 1;
            i -= 1;
        }
        ++i;
    }
}