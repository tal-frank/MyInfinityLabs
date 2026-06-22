#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Biggest_surface_indexes
{
    size_t start;
    size_t end;
} bsi_t;

int min(int num1, int num2)
{
    return num1 > num2 ? num2 : num1;
}

void PrintArr(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d ", arr[i]);
    }
}

void SetRandomArr(int arr[], size_t size)
{
	size_t i = 0;
	int rand_num = rand() % size;
	printf ("rand_num = %d\n", rand_num);
	for (i = 0; i < size; ++i)
	{
        rand_num = rand() % size;
		arr[i] = (rand_num % ((int)size + 1));
	}
}

bsi_t BiggestSurface(int arr[], size_t size)
{
    bsi_t bsi = {0};
    long max_surface = 0;
    long curr_surface = 0;
    size_t end_i = size - 1;
    size_t start_i = 0;
    while (end_i > start_i)
    {
        curr_surface = (long)((end_i - start_i) * min(arr[end_i], arr[start_i]));
        if (curr_surface > max_surface)
        {
            max_surface = curr_surface;
            bsi.start = start_i;
            bsi.end = end_i;
        }

        arr[end_i] > arr[start_i] ? ++start_i : --end_i;
    }

    return bsi;
}

int main()
{
    int arr[100] = {0};
    bsi_t bsi = {0};
    SetRandomArr(arr, 100);
    PrintArr(arr, 100);

    bsi = BiggestSurface(arr, 100);
    printf("\n");
    printf ("start = %ld\n", bsi.start);
    printf ("end = %ld\n", bsi.end);

    return 0;
}