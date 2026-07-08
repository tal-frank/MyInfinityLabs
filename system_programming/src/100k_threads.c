#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define ONE_THOUSAND (1000)
#define ONE_MILION (1000000)
#define NUMBER_OF_THREADS (6)

enum
{
    SUCCESS = 0,
    FAILLURE
};

int global_arr[ONE_MILION] = {0};
long global_sum[ONE_THOUSAND] = {0};
const long num = 1000000000000000;

void* ManipulateArr(void* data)
{
    global_arr[(int)data] = (int)data;

    return NULL;
}

void* DevisorsSum(void* data)
{
    int i = 1;
    int j = num / NUMBER_OF_THREADS;
    long sum = 0;
    for(i = j * (int)data; i < j * ((int)data + 1); ++i)
    {
        if (0 == num % i)
        {
            sum += i;
        }
    }
    global_sum[(int)data] = sum;
    return NULL;
}

void FillArr(size_t size)
{
    size_t i = 0;
    pthread_t thread[ONE_MILION] = {0};
    size_t count = 0;

    for (i = 0; i < size; ++i)
    {
        if (SUCCESS != pthread_create(&thread[i], NULL, ManipulateArr, (void*)i))
        {
            perror("could not create a thread");
        }
    }

    for (i = 0; i < size; ++i)
    {
        if ((int)i == global_arr[i])
        {
            ++count;
        }
        else
        {
            printf("wrong entry index : %ld\n", i);
        }
    }

    for(i = 0; i < size; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }

    printf("number of correct entries is : %ld", count);
}

void CalcSumOfDivisorsThreads(size_t size)
{
    size_t i = 0;
    pthread_t thread[ONE_MILION] = {0};
    long sum_divisors = 0;

    for (i = 0; i < size; ++i)
    {
        if (SUCCESS != pthread_create(&thread[i], NULL, DevisorsSum, (void*)i))
        {
            perror("could not create a thread");
        }
    }

    for(i = 0; i < size; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }

    for(i = 0; i < ONE_THOUSAND; ++i)
    {
        sum_divisors += global_sum[i];
    }

    printf("sum of divisors is : %ld", sum_divisors);
}

void FillArrPragma(long size)
{
    size_t i = 0;

    #pragma omp parallel for
    for (i = 0; i < size; ++i)
    {
        global_arr[i] = i;
    }
}

int main()
{
/*
    FillArr(ONE_MILION);

    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
    CalcSumOfDivisorsThreads(NUMBER_OF_THREADS);
*/
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    FillArrPragma(num);
    
    return 0;
}