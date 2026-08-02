/**********************
* shuffle and sort dictionary
* Author: Tal Frank
* Reviewer: Moshe Moiseev
* Last update: 01/08/2026
**********************/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <time.h>

#define UNUSED(x) (void)(x)

#define NUMBER_OF_DICT (32)
#define NUM_OF_WORDS (104334)
#define MAX_NUM_OF_THREADS (100)
#define NUM_OF_WORDS_SEVERAL_DICT ((NUMBER_OF_DICT) * (NUM_OF_WORDS))

/*------------------------------------------------------------------------------------------------------------------*/
/************************************************* STRUCTS & ENAMS **************************************************/
/*------------------------------------------------------------------------------------------------------------------*/
enum
{
    SUCCESS = 0,
    FAILURE
};


typedef struct thread_sort_part
{
    size_t start_index;
    size_t num_of_elements;
    char** dictionary;
}thread_sort_part_t;

typedef struct thread_merge_part
{
    size_t start_index;
    size_t num_of_elements;
    char** dictionary;
    char** auxilary_dict;
}thread_merge_part_t;

/*--------------------------------------------------------------------------------------------------------------------------------*/
/************************************************* STATIC FUNCTIONS DECLARATIONS **************************************************/
/*--------------------------------------------------------------------------------------------------------------------------------*/

static int RandomCompareFunc(const void* data1, const void* data2);
static int CmpFunc(const void* data1, const void* data2);
static void* ThreadSortPart(void* data);
static int RandomCompareFunc(const void* data1, const void* data2);
static void MergePartitions(char* arr[], char* buffer[], size_t num_of_elements);
static void CopyArray(char* arr[], char* buffer[], int num_of_elements);
static void* ThreadMergePartitions(void* data);

/*----------------------------------------------------------------------------------------------------------------*/
/************************************************* MAIN FUNCTUIN **************************************************/
/*----------------------------------------------------------------------------------------------------------------*/

int main()
{
    size_t i = 0;
    long file_size = 0;
    char* dict_buffer = NULL;
    char* dict_buffer_runner = dict_buffer;
    char** dictionary = NULL;
    char** shuffled_dictionary = NULL;
    char** auxilary_dict = NULL;
    char separators[] = {"\n"};
    thread_sort_part_t parts[MAX_NUM_OF_THREADS] = {0};
    thread_merge_part_t merge_part[MAX_NUM_OF_THREADS] = {0};
    size_t start_index = 0;
    size_t thread_num_of_elements = 0;
    size_t merge_num_of_elements = 0;
    size_t number_of_threads = 0;
    size_t merge_num_of_threads = 0;
    pthread_t threads[MAX_NUM_OF_THREADS] = {0};
    struct timespec start = {0};
    struct timespec end = {0};
    double time_taken = 0;
    int ret_val = 0;
    FILE* file = fopen("/usr/share/dict/words", "r");
    if (NULL == file)
    {
        perror("failed open file");
        return FAILURE;
    }

    dictionary = (char**)malloc(sizeof(size_t) * NUM_OF_WORDS_SEVERAL_DICT);
    if(NULL == dictionary)
    {
        return FAILURE;
    }
    shuffled_dictionary = (char**)malloc(sizeof(size_t) * NUM_OF_WORDS_SEVERAL_DICT);
    if(NULL == shuffled_dictionary)
    {
        free(dictionary);
        return FAILURE;
    }
    auxilary_dict = (char**)malloc(sizeof(size_t) * NUM_OF_WORDS_SEVERAL_DICT);
    if(NULL == auxilary_dict)
    {
        free(dictionary);
        free(dict_buffer);
        return FAILURE;
    }

    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    dict_buffer = (char*)malloc(NUMBER_OF_DICT * file_size);
    if(NULL == auxilary_dict)
    {
        free(dictionary);
        free(dict_buffer);
        free(auxilary_dict);
        return FAILURE;
    }
    rewind(file);
    for(i = 0; i < NUMBER_OF_DICT; ++i)
    {
        ret_val = fread(dict_buffer + i * file_size, 1, file_size , file);
        rewind(file);
    }
    fclose(file);

    i = 0;
    dict_buffer_runner = strtok(dict_buffer, separators);
    while (NULL != dict_buffer_runner && i < NUM_OF_WORDS_SEVERAL_DICT)
    {
        dict_buffer_runner = strtok(NULL, separators);
        dictionary[i++] = dict_buffer;
        dict_buffer = dict_buffer_runner;
    }

    qsort(dictionary, NUM_OF_WORDS_SEVERAL_DICT, sizeof(char*), RandomCompareFunc);
    qsort(dictionary, NUM_OF_WORDS_SEVERAL_DICT, sizeof(char*), RandomCompareFunc);
    qsort(dictionary, NUM_OF_WORDS_SEVERAL_DICT, sizeof(char*), RandomCompareFunc);
    qsort(dictionary, NUM_OF_WORDS_SEVERAL_DICT, sizeof(char*), RandomCompareFunc);

    memcpy(shuffled_dictionary, dictionary, NUM_OF_WORDS_SEVERAL_DICT);

    for (number_of_threads = 1; number_of_threads < 65; number_of_threads *= 2)
    {
        memcpy(dictionary, shuffled_dictionary, NUM_OF_WORDS_SEVERAL_DICT);
        thread_num_of_elements = (NUM_OF_WORDS * NUMBER_OF_DICT) / number_of_threads;

        clock_gettime(CLOCK_MONOTONIC, &start);

        /*-----------------------------------------------------------*/
        /********** sorting each part with separate threads **********/

        for (i = 0; i < number_of_threads; ++i)
        {
            parts[i].dictionary = dictionary;
            parts[i].start_index = start_index;
            parts[i].num_of_elements = thread_num_of_elements;
            if (SUCCESS != pthread_create(&threads[i], NULL, ThreadSortPart, &parts[i]))
            {
                perror("failed to create thread\n");
            }
            start_index += thread_num_of_elements;
        }

        for (i = 0; i < number_of_threads; ++i)
        {
            if (SUCCESS != pthread_join(threads[i], NULL))
            {
                perror("could not destroy thread\n");
            }
        }

        /*----------------------------------------------------------------*/
        /********** merging the parts back with separate threads **********/

        merge_num_of_elements = thread_num_of_elements;
        merge_num_of_threads = number_of_threads;
        while (merge_num_of_elements <= (NUM_OF_WORDS_SEVERAL_DICT) / 2)
        {
            merge_num_of_elements *= 2;
            merge_num_of_threads = merge_num_of_threads / 2;
            for (start_index = 0; start_index < NUM_OF_WORDS; 
                start_index += merge_num_of_elements)
            {
                for (i = 0; i < merge_num_of_threads; ++i)
                {
                    merge_part[i].dictionary = dictionary;
                    merge_part[i].start_index = start_index;
                    merge_part[i].num_of_elements = merge_num_of_elements;
                    merge_part[i].auxilary_dict = auxilary_dict;
                if (SUCCESS != pthread_create(&threads[i], NULL, ThreadMergePartitions, &merge_part[i]))
                {
                    perror("failed to create thread\n");
                }
                start_index += merge_num_of_elements;
                }
            }
            for (i = 0; i < merge_num_of_threads; ++i)
            {
                if (SUCCESS != pthread_join(threads[i], NULL))
                {
                    perror("could not destroy thread\n");
                }
            }
        }
        start_index = 0;

        clock_gettime(CLOCK_MONOTONIC, &end);
        time_taken = (end.tv_sec - start.tv_sec)
                 + (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Num of threads: %ld Execution Time: %f\n\n", number_of_threads ,time_taken);
    }

    return 0;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/************************************************* STATIC FUNCTIONS **************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/

static void* ThreadMergePartitions(void* data)
{
    char** dictionary = ((thread_merge_part_t*)data)->dictionary;
    char** auxilary_dict = ((thread_merge_part_t*)data)->auxilary_dict;
    size_t num_of_elements = ((thread_merge_part_t*)data)->num_of_elements;
    size_t start_index = ((thread_merge_part_t*)data)->start_index;

    MergePartitions(dictionary + start_index, auxilary_dict + start_index, num_of_elements);
    CopyArray(dictionary + start_index, auxilary_dict + start_index, num_of_elements);

    return NULL;
}

static void CopyArray(char* arr[], char* buffer[], int num_of_elements)
{
    memcpy(arr, buffer, num_of_elements);
}

static void MergePartitions(char* arr[], char* buffer[], size_t num_of_elements)
{
    size_t i = 0;
    size_t left_part_i = 0;
    size_t half_elements = num_of_elements / 2;
    size_t right_part_i = half_elements;
    
    while (half_elements > left_part_i && num_of_elements > right_part_i)
    {
        buffer[i++] = 0 > strcmp(arr[left_part_i], arr[right_part_i]) ? 
                                 arr[left_part_i++] : arr[right_part_i++];
    }

    while(half_elements > left_part_i)
    {
        buffer[i++] = arr[left_part_i++];
    }

    while (num_of_elements > (right_part_i))
    {
        buffer[i++] = arr[right_part_i++];
    }
}


static void* ThreadSortPart(void* data)
{
    size_t start_index = ((thread_sort_part_t*)data)->start_index;
    char** dictionary = ((thread_sort_part_t*)data)->dictionary;
    size_t num_of_elements = ((thread_sort_part_t*)data)->num_of_elements;

    qsort(dictionary + start_index, num_of_elements, sizeof(char*), CmpFunc);
    return NULL;
}

/*------------------------------------------------------------------------*/
/***************************** CMP FUNCTIONS ******************************/
/*------------------------------------------------------------------------*/

static int RandomCompareFunc(const void* data1, const void* data2)
{
    UNUSED(data1);
    UNUSED(data2);
    
    return -1 + rand() % 3;
}

static int CmpFunc(const void* data1, const void* data2)
{
    char** str1 = (char**)data1;
    char** str2 = (char**)data2;

    return strcmp(*str1, *str2);
}