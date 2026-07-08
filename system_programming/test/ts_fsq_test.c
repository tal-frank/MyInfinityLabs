
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread API */
#include <stdio.h> /* printf */
#include <semaphore.h> /* semaphore API */

#include "ts_fsq.h"

#define TWENTY (20)

typedef struct fsq
{
    ts_fsq_t* fsq;
    int data;
}fsq_t;

enum
{
    SUCCESS = 0,
    FAILLURE
};

void* FSQDequeueWrapper(void* data)
{
    ts_fsq_t* fsq = ((fsq_t*)data)->fsq;
    int num[1] = {0};   
    FSQDequeue(fsq, (void*)num);

    printf("message was : %d\n", num[0]);

    return NULL;
}

void* FSQEnqueueWrapper(void* data)
{
    ts_fsq_t* fsq = ((fsq_t*)data)->fsq;
    int num[1] = {0};
    num[0] = ((fsq_t*)data)->data;
    FSQEnqueue(fsq, (void*)num);

    return NULL;
}

int main()
{
    size_t i = 0;
    pthread_t thread[TWENTY] = {0};
    ts_fsq_t* fsq = FSQCreate(2, 4);
    fsq_t fsq_data[TWENTY] = {0};

    for (i = 0; i < TWENTY / 2; ++i)
    {
        fsq_data[i].fsq = fsq;
        fsq_data[i].data = i + 1;
        if (SUCCESS != pthread_create(&thread[i], NULL, FSQEnqueueWrapper, (void*)&fsq_data[i]))
        {
            perror("could not create a thread");
        }
    }

    for (i = TWENTY / 2; i < TWENTY; ++i)
    {
        fsq_data[i].fsq = fsq;
        if (SUCCESS != pthread_create(&thread[i], NULL, FSQDequeueWrapper, (void*)&fsq_data[i]))
        {
            perror("could not create a thread");
        }
    }

    for(i = 0; i < TWENTY; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }
    FSQDestroy(fsq);
    return 0;
}