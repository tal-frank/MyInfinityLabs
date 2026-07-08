#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread API */
#include <stdio.h> /* printf */
#include <semaphore.h> /* semaphore API */
#include <stdlib.h> /* malloc , free */

#include "ts_fsq.h"
#include "circular_buffer.h"

struct TSFSQueueu
{
    pthread_mutex_t read_mutex;
    pthread_mutex_t write_mutex;
    sem_t read_sem;
    sem_t write_sem;
    size_t element_size;
    cbuff_t* cbuff;
};


ts_fsq_t* FSQCreate(size_t capacity, size_t element_size)
{
    
    ts_fsq_t* ts_fsq = (ts_fsq_t*)malloc(sizeof(ts_fsq_t));
    if (NULL == ts_fsq)
    {
        return NULL;
    }
    ts_fsq->cbuff = CBuffCreate(capacity * element_size);
    if (NULL == ts_fsq->cbuff)
    {
        return NULL;
    }

    if (0 != pthread_mutex_init(&ts_fsq->read_mutex, NULL))
    {
        return NULL;
    }
    if (0 != pthread_mutex_init(&ts_fsq->write_mutex, NULL))
    {
        return NULL;
    }
    sem_init(&ts_fsq->write_sem, 0, capacity);
    sem_init(&ts_fsq->read_sem, 0, 0);
    ts_fsq->element_size = element_size;

    return ts_fsq;
}

void FSQDestroy(ts_fsq_t* fsq)
{
    CBuffDestroy(fsq->cbuff);
    free(fsq);
}

void FSQEnqueue(ts_fsq_t* fsq, void* src)
{
    sem_wait(&fsq->write_sem);
    pthread_mutex_lock(&fsq->write_mutex);
    
    CBuffWrite(fsq->cbuff , src, fsq->element_size);

    pthread_mutex_unlock(&fsq->write_mutex);
    sem_post(&fsq->read_sem);
}

void FSQDequeue(ts_fsq_t* fsq, void* dest)
{
    sem_wait(&fsq->read_sem);
    pthread_mutex_lock(&fsq->read_mutex); 

    CBuffRead(fsq->cbuff, dest, fsq->element_size);

    pthread_mutex_unlock(&fsq->read_mutex);
    sem_post(&fsq->write_sem);
}

size_t FSQSize(const ts_fsq_t* fsq)
{
    return CBuffSize(fsq->cbuff) / fsq->element_size;
}