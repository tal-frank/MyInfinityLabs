#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>

int IterBinarySearch(const int* arr, size_t size, int target);

int BinarySearch(const int* arr, int size, int target);

int MergeSort (int arr[], int num_of_elements);

void QuickSort(void* arr, 
               size_t number_of_elements, 
               size_t size_of_element, 
               int (*cmp_func)(const void* num1, const void* num2));



#endif /** End of __DOUBLY_LINKED_LIST_H__ */