#include <stdio.h>
#include "pointer1.h"


void CopyArrTest(int arr[], int new_arr[], int size)
{
	int i;
	for (i = 0; i < size; ++i)
	{
		if (arr[i] != new_arr[i])
		{
			printf("arr[%d] = %d , new_arr[%d] = %d\n", i, arr[i], i, new_arr[i]);
		}
	}
	printf("success\n");
}


int main()
{
	int arr_cpy1[6];
	int arr1[] = {1,2,3,4,5,6};
	int arr_cpy2[5];
	int arr2[] = {1,2,5,4,1};
	int arr_cpy3[2];
	int arr3[] = {15,32};
	int arr_cpy4[1];
	int arr4[] = {4};
	int arr_cpy6[10];
	int arr6[] = {1,2,5,47,42,2,23,4,7,94};
	
	CopyArray(arr1, 6, arr_cpy1, 6);
	CopyArray(arr2, 5, arr_cpy2, 5);
	CopyArray(arr3, 2, arr_cpy3, 2);
	CopyArray(arr4, 1, arr_cpy4, 1);
	CopyArray(arr6, 10, arr_cpy6, 10);
	
	CopyArrTest(arr1, arr_cpy1, 6);
	CopyArrTest(arr2, arr_cpy2, 5);
	CopyArrTest(arr3, arr_cpy3, 2);
	CopyArrTest(arr4, arr_cpy4, 1);
	CopyArrTest(arr6, arr_cpy6, 10);
	
	PrintVarAddrss();


	size_t size1 = 5;
	size_t size2 = 1;
	size_t* size1_ptr = &size1;
	size_t* size2_ptr = &size2;
	size_t** size1_pp = &size1_ptr;
	size_t** size2_pp = &size2_ptr;
	
	printf("size1_ptr = %p\nsize2_ptr = %p\n", (void*)size1_ptr, (void*)size2_ptr);
	printf("\n\n");
	SwapSize_tPointers(size1_pp, size2_pp);
	printf("size1_ptr = %p\nsize2_ptr = %p\n", (void*)size1_ptr, (void*)size2_ptr);
	printf("\n\n");



}










