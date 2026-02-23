#include <stdlib.h>

int main()
{
	
	int* arr1 = (int*)malloc(100);
	int arr2[10];
	int var = 1;
	int* ptr = arr2;

	free(ptr);
	printf("arr2 : %d\n" , arr2[11]); 
	printf("ptr : %d\n" , *ptr);
	if (arr1[0] == 0)
	{
		printf("not valid\n");
	}

	while (var != 0)
	{
		++var;
	}
	
	
}
