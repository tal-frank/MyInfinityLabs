/**********************
* multithreaded counting sort
* Author: Tal Frank
* Reviewer: Almog Nimni
* Last update: 30/07/2026
**********************/

#include <stddef.h> /* size_t */
#include <unistd.h> /* sysconf */
#include <stdlib.h> /* calloc */
#include <pthread.h> /* pthread_create */
#include <errno.h> /* perror */
#include <string.h> /* memset */

#define NUMBER_OF_THREADS (100)
#define MAX_CHAR (256)

enum
{
    SUCCESS = 0,
    FAILURE
};

typedef struct thread_sort_part
{
    size_t start_index;
    size_t num_of_elements;
    char* arr;
}thread_sort_part_t;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
size_t sorted_arr[MAX_CHAR] = {0};

static void AddAdjacent(size_t count_arr[], size_t size);
static void SetSortedArr(char dest_arr[], size_t sorted_arr[], size_t size, size_t sorted_size);
void* ThreadCountingSort(void* data);

void MultiThreadedCountingSort(char arr[], size_t size, size_t number_of_threads)
{
    size_t i = 0;
    size_t start_index = 0;
    int thread_num_of_elements = (size / number_of_threads);
    pthread_t threads[NUMBER_OF_THREADS] = {0};
    thread_sort_part_t parts[NUMBER_OF_THREADS] = {0};

    memset(sorted_arr, 0, sizeof(size_t) * MAX_CHAR);
    
    for (i = 0; i < number_of_threads; ++i)
    {
        parts[i].arr = arr;
        parts[i].start_index = start_index;
        parts[i].num_of_elements = thread_num_of_elements;

        if (SUCCESS != pthread_create(&threads[i], NULL, ThreadCountingSort, &parts[i]))
        {
            perror("could not create thread");
        }
        start_index += thread_num_of_elements;
    }
    
    for (i = 0; i < number_of_threads; ++i)
    {
        if (SUCCESS != pthread_join(threads[i], NULL))
        {
            perror("could not destroy thread");
        }
    }

    /* AddAdjacent(sorted_arr, MAX_CHAR); */
    
    SetSortedArr(arr, sorted_arr, size, MAX_CHAR);
}

static void SetSortedArr(char dest_arr[], size_t histogram[], size_t size, size_t sorted_size)
{
    size_t cnt = 0;
    size_t write_i = 0;
    size_t read_i = 0;
    for (write_i = 0; write_i < size && read_i < sorted_size; ++read_i)
    {
        cnt = 0;
        while (cnt < histogram[read_i])
        {
            dest_arr[write_i] = read_i;
            ++cnt;
            ++write_i;
        }
    }	
}

void* ThreadCountingSort(void* data)
{
    size_t i = 0;
    size_t start_index = ((thread_sort_part_t*)data)->start_index;
    char* arr = ((thread_sort_part_t*)data)->arr;
    size_t num_of_elements = ((thread_sort_part_t*)data)->num_of_elements;
    size_t sorted_part_arr[MAX_CHAR] = {0};
    
    for (i = start_index; i < (start_index + num_of_elements); ++i)
    {
        ++sorted_part_arr[(int)arr[i]];
    }

    pthread_mutex_lock(&mutex);
    for (i = 0; i < MAX_CHAR; ++i)
    {
        sorted_arr[i] += sorted_part_arr[i];
    }
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

static void AddAdjacent(size_t count_arr[], size_t size)
{
    size_t i = 0;
    for (i = 1; i < size; ++i)
    {
        count_arr[i] += count_arr[i - 1];
    }
}
