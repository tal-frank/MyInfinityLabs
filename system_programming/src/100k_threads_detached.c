#include <stddef.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define ONE_MILION (1000000)

enum
{
    SUCCESS = 0,
    FAILLURE
};

int global_arr[ONE_MILION] = {0};
const long num = 5000000000000;

void* ManipulateArr(void* data)
{
    global_arr[(int)data] = (int)data;

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
        if (pthread_detach(thread[i]))
        {
            perror("could not detach a thread");
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


    printf("number of correct entries is : %ld", count);

}

void DevisorsSum(void)
{
    int i = 1;
    int j = 0;
    long sum = 0;
    #pragma omp parallel for
    for (j = 0; j < 100; ++j)
    {
        #pragma omp parallel for
        for(i = 1; i < num; ++i)
        {
            if (0 == num % i)
            {
                sum += i;
            }
        }
    }
    printf("divisors sum is : %ld", sum);
}

int main()
{
/*
    FillArr(ONE_MILION);
*/
    DevisorsSum();

    return 0;
}