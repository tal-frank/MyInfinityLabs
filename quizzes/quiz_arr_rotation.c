#include <stddef.h>
#include <stdio.h>

void SwapChars(char* ch1, char* ch2)
{
    char temp = *ch1;
    *ch1 = *ch2;
    *ch2 = temp;
}

void FlipArr(char arr[], size_t start, size_t end)
{
    size_t i = 0;
    for(i = start; i < end; ++i, --end)
    {
        SwapChars(&arr[i], &arr[end]);
    }
}

void RotateArr2(char arr[], size_t size, size_t rotation)
{
    FlipArr(arr, 0, size - rotation - 1);
    FlipArr(arr, size - rotation, size - 1);
    FlipArr(arr, 0, size - 1);
}

void RecRotateArr(char arr[], size_t size, size_t rotation, size_t i)
{
    char temp = arr[i];
    if(size == i)
    {
        return;
    }

    RecRotateArr(arr, size, rotation, i + 1);
    arr[(i + rotation) % size] = temp;
}

void RotateArr(char arr[], size_t size, size_t rotation) 
{
    RecRotateArr(arr, size, rotation, 0);
}

void PrintArr(char arr[], size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    char arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RotateArr(arr, 11, 3);
    PrintArr(arr, 11);
    RotateArr2(arr, 11, 3);
    PrintArr(arr, 11);
    return 0;
}