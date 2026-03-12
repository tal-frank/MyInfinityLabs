/**********************
* pointer_part_1
* Author: Tal Frank
* Reviewer: Barak Koifman
* Last update: 12/03/2026
**********************/

void SwapInt(int* var1, int* var2)
{
	*var1 = *var1 + *var2;
	*var2 = *var1 - *var2;
	*var1 = *var1 - *var2;
}

void SwapSize_t(size_t* var1, size_t* var2)
{
	*var1 = *var1 + *var2;
	*var2 = *var1 - *var2;
	*var1 = *var1 - *var2;
}


void CopyArray(const int* arr_src, const size_t size_src, int* arr_cpy, size_t size_cpy)
{
	size_t i;
	for (i = 0; i < size_src; ++i)
	{
		arr_cpy[i] = arr_src[i];
	}
}

void PrintVarAddrss()
{
	static int s_i = 7;
	int* ptr1 = &s_i;
	int i = 7;
	int* ptr2 = &i;
	int** ptr3 = &ptr2;
	int* ptr4 = (int *)malloc(sizeof(int));	

	printf("ptr1 = %p\n", (void*)ptr1);
	printf("ptr2 = %p\n", (void*)ptr2);
	printf("ptr3 = %p\n", (void*)ptr3);
	printf("ptr4 = %p\n", (void*)ptr4);
	free(ptr4);
		
}

void SwapSize_tPointers(size_t** var1, size_t** var2)
{
	SwapSize_t((size_t*)var1, (size_t*)var2);
}





