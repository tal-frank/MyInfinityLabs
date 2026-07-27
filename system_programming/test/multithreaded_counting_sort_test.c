#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include "../src/multithreaded_counting_sort.c"

#define SIZE_OF_DICT (1000000)

int main()
{
    char* arr = NULL;
    long file_size = 0;
    long i = 0;
    struct timespec start = {0};
    struct timespec end = {0};
    double time_taken = 0;

    FILE* file = fopen("/usr/share/dict/words", "r");
    if (NULL == file)
    {
        printf("can't open file\n");
        return 0;
    }
    
    /****************************************************************************** 1 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    arr = (char*)malloc(8 * file_size);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 1);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 1 Execution Time: %f\n", time_taken);

    /****************************************************************************** 2 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 2);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 2 Execution Time: %f\n", time_taken);

    /****************************************************************************** 4 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 4);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 4 Execution Time: %f\n", time_taken);

    /****************************************************************************** 8 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 8);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 8 Execution Time: %f\n", time_taken);

    /****************************************************************************** 16 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 16);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 16 Execution Time: %f\n", time_taken);

    /****************************************************************************** 32 thread **********/
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    for(i = 0; i < 8; ++i)
    {
        fread(arr + i * file_size, 1, file_size , file);
        rewind(file);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    MultiThreadedCountingSort(arr, 8 * file_size, 32);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Num of threads: 32 Execution Time: %f\n", time_taken);
    

    /* for (i = 0; i < 8 * file_size; ++i)
    {
        printf(" %d ", arr[i]);
    }
    for (i = 0; i < 8 * file_size; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            printf("ERROR\n");
        }
        else
        {
            printf("SUCCESS\n");
        }
    } */
    free(arr);
    return 0;
}