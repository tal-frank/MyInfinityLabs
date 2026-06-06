#include <stddef.h>
#include <stdlib.h>

enum Status
{
    FAILURE = -1,
    SUCCESS
};

static int RecBinarySearch(int arr[], int start, int size, int target);
static int min(int num1, int num2);
/*
static void PrintArr2(int arr[], size_t size);
*/
static void SortPartitions(int arr[], int buffer[], int num_of_elements);
static void CopyArray(int arr[], int buffer[], int num_of_elements);
static size_t GetPivot(size_t number_of_elements);
static void SwapElements(char* element1, char* element2, size_t size_of_element);

static void SortAroundPivot(void* arr, 
                            size_t* pivot,
                            size_t number_of_elements, 
                            size_t size_of_element, 
                            int (*cmp_func)(const void* num1, const void* num2));

int IterBinarySearch(int arr[], size_t size, int target)
{
    int start = 0;
    int end = size - 1;
    int search_index = (start + end) / 2;

    while (start <= end)
    {
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

        search_index = (start + end) / 2;
    }
    return FAILURE;
}


int BinarySearch(int arr[], int size, int target)
{
    return RecBinarySearch(arr, 0, size - 1, target);
}

static int RecBinarySearch(int arr[], int start, int size, int target)
{
    int search_index = (start + (size)) / 2;
    if (target == arr[search_index])
    {
        return search_index;
    }
    else if (start > size)
    {
        return FAILURE;
    }
    if (target > arr[search_index])
    {
        return RecBinarySearch(arr, search_index + 1, size, target);
    }
    else
    {
        return RecBinarySearch(arr, start, search_index - 1, target);
    }
}

int MergeSort (int arr[], int num_of_elements)
{
    int half_elements = num_of_elements / 2;
    int* buffer = NULL;

    if (1 == num_of_elements)
    {
        return SUCCESS;
    }

    buffer = (int*)malloc(num_of_elements * sizeof(int));
    if (NULL == buffer)
    {
        return FAILURE;
    }

    MergeSort(arr, half_elements);
    MergeSort(arr + (half_elements), num_of_elements - (half_elements));

    SortPartitions(arr, buffer, num_of_elements);
    CopyArray(arr, buffer, num_of_elements);
 
    free(buffer);
    buffer = NULL;
    return SUCCESS;
}

void QuickSort(void* arr, 
               size_t number_of_elements, 
               size_t size_of_element, 
               int (*cmp_func)(const void* num1, const void* num2))
{
    size_t pivot = 0;
    if (1 >= number_of_elements)
    {
        return;
    }

    pivot = GetPivot(number_of_elements);

    SortAroundPivot(arr, &pivot, number_of_elements, size_of_element, cmp_func);

    QuickSort((void*)((char*)arr), 
              pivot, 
              size_of_element, 
              cmp_func);

    QuickSort((void*)((char*)arr + ((pivot + 1) * size_of_element)), 
              number_of_elements - (pivot + 1), 
              size_of_element, 
              cmp_func);
}


static void SortPartitions(int arr[], int buffer[], int num_of_elements)
{
    int i = 0;
    int j = 0;
    int k = num_of_elements / 2;
    int half_elements = num_of_elements / 2;
    for (i = 0; i < num_of_elements; ++i)
    {
        buffer[i] = min(arr[j], arr[k]);
        if (num_of_elements <= (k))
        {
            buffer[i] = arr[j++];
        }
        else if (half_elements <= j)
        {
            buffer[i] = arr[k++];
        }
        else
        {
            (arr[j] > arr[k]) ? ++k : ++j;
        }
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
/*
static void PrintArr2(int arr[], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		printf(" %d ", arr[i]);
    }
}
*/
static int min(int num1, int num2)
{
    return (num1 < num2) ? num1 : num2;
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
    size_t i = 1;
    size_t start = 0;
    size_t end = number_of_elements - 1;
    char* arr_runner = (char*)arr;
    while (*pivot != start && *pivot != end)
    {
        if (0 > cmp_func(&arr_runner[*pivot * size_of_element], 
                          &arr_runner[start * size_of_element]) 
         && 0 <= cmp_func(&arr_runner[*pivot * size_of_element], 
                         &arr_runner[end * size_of_element]))
        {
            SwapElements(&arr_runner[start * size_of_element], 
                         &arr_runner[end * size_of_element], 
                         size_of_element);
        }
        else
        {
            start = (0 < cmp_func(&arr_runner[start * size_of_element], 
                                  &arr_runner[*pivot * size_of_element])) ? 
                                  start : start + 1;
            end = (0 >= cmp_func(&arr_runner[end * size_of_element], 
                                &arr_runner[*pivot * size_of_element])) ? 
                                end : end - 1;
        }
    }
    
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
    i = 1;
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