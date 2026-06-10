#include <stddef.h>
#include <stdio.h>

void PrintArr(int arr[], size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf(" %d ", arr[i]);
    }
    
}

void SwapElements(int arr[], size_t start, size_t end)
{
    int temp = arr[start];
    
    arr[start] = arr[end];
    arr[end] = temp;
}

void BitSort(int arr[], size_t size)
{
    size_t start = 0;
    size_t end = size - 1;

    while (start < end)
    {
        if (1 == arr[start] && 0 == arr[end])
        {
            SwapElements(arr, arr[start], arr[end]);
            ++start;
            --end;
        }
        else
        {
            start = (0 == arr[start]) ? start + 1 : start;
            end = (1 == arr[end] ? end - 1 : end);    
        }
    }
}

int main()
{
    int arr[20] = {0, 1, 0, 0, 1, 1 ,0 ,1 ,0 ,1 ,0 ,0 ,1 , 0, 1 ,0 ,0 ,1 ,0 ,1};
    
    BitSort(arr, 20);
    PrintArr(arr, 20);
    printf("\n");
    
    return 0;
}
