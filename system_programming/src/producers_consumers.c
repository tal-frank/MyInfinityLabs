
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread API */
#include <stdio.h> /* printf */
#include <semaphore.h> /* semaphore API */

#include "circular_buffer.h"
#include "doubly_linked_list.h"

#define TWO (2)
#define TEN (10)
#define TWENTY (20)

enum
{
    SUCCESS = 0,
    FAILLURE
};

typedef struct cbuff_lock
{
    cbuff_t* cbuff;
    pthread_mutex_t* mutex;
    char message;
}cbuff_lock_t;

typedef struct dll_lock
{
    dll_t* dll;
    pthread_mutex_t* mutex;
    int message;
}dll_lock_t;

pthread_cond_t ready = {0};
int wait = 1;
int message_number = 0;
sem_t write_sem = {0};
sem_t read_sem = {0};
sem_t number_thread_sem = {0};
volatile int lock = 0;

void SpinLockInsetr()
{
    while (1 == lock);
}

void SpinLockPop()
{
    while (0 == lock);
}

void* InsertDll(void* data)
{
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message = 0;
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;
    
    pthread_mutex_lock(mutex);
    
    message = ((dll_lock_t*)data)->message;
    DllPushBack(dll ,(void*)message);
    
    pthread_mutex_unlock(mutex);
    
    printf("message sent\n");

    return NULL;
}

void* PopDll(void* data)
{
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message = 0;
    int is_empty = 1;
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;
    while (is_empty)
    {
        pthread_mutex_lock(mutex); 
        if (!DllIsEmpty(dll))
        {
            is_empty = 0;
        }
        pthread_mutex_unlock(mutex);
    }
    
    pthread_mutex_lock(mutex); 

    message = (int)DllGetData(DllBegin(dll));
    DllPopFront(dll);

    pthread_mutex_unlock(mutex);
    
    printf("message recieved : %d\n", message);

    return NULL;
}

void* InsertCBuffTwoSem(void* data)
{
    cbuff_t* cbuff = ((cbuff_lock_t*)data)->cbuff;
    char message = 0;
    pthread_mutex_t* mutex = ((cbuff_lock_t*)data)->mutex;
    message = ((cbuff_lock_t*)data)->message;
    sem_wait(&write_sem);

    pthread_mutex_lock(mutex);
    
    CBuffWrite(cbuff ,&message, 1);

    pthread_mutex_unlock(mutex);
    
    printf("message sent\n");
    sem_post(&read_sem);

    return NULL;
}

void* PopCBuffTwoSem(void* data)
{
    cbuff_t* cbuff = ((cbuff_lock_t*)data)->cbuff;
    char message = 0;
    pthread_mutex_t* mutex = ((cbuff_lock_t*)data)->mutex;

    sem_wait(&read_sem);
    pthread_mutex_lock(mutex); 

    CBuffRead(cbuff, (void*)&message, 1);

    pthread_mutex_unlock(mutex);
    sem_post(&write_sem);

    printf("message recieved : %d\n", message);

    return NULL;
}

void* InsertDllOneSem(void* data)
{
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message = 0;
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;

    pthread_mutex_lock(mutex);
    
    message = ((dll_lock_t*)data)->message;
    DllPushBack(dll ,(void*)message);
    
    pthread_mutex_unlock(mutex);
    
    printf("message sent\n");
    sem_post(&read_sem);

    return NULL;
}

void* PopDllOneSem(void* data)
{
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message = 0;
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;

    sem_wait(&read_sem);
    
    pthread_mutex_lock(mutex); 

    message = (int)DllGetData(DllBegin(dll));
    DllPopFront(dll);

    pthread_mutex_unlock(mutex);
    
    printf("message recieved : %d\n", message);

    return NULL;
}

void* InsertCBuff(void* data)
{
    size_t i = 0;
    cbuff_t* cbuff = (cbuff_t*)data;
    char arr[5] = {1, 2, 3, 4, 5};
    for (i = 0; i < 5; ++i)
    {
        CBuffWrite(cbuff, (void*)&arr[i], 1);
        printf("sent a message.\n"); 
        __sync_lock_test_and_set(&lock, 1);
        SpinLockInsetr();
    }
    return NULL;
}

void* PopCBuff(void* data)
{
    size_t i = 0;
    cbuff_t* cbuff = (cbuff_t*)data;
    char arr[1] = {0};
    for (i = 0; i < 5; ++i)
    {
        SpinLockPop();
        CBuffRead(cbuff, arr, 1);
        printf("recieved message : %d\n", arr[0]);
        __sync_lock_release(&lock);
    }

    CBuffDestroy(cbuff);
    return NULL;
}

void* InsertDllBarrier(void* data)
{
    size_t i = 0;
    size_t j = 0;
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message[TWENTY - 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;
    
    while (i < TWENTY - 1)
    {
        for (j = 0; j < TWENTY - 1; ++j)
        {
            sem_wait(&number_thread_sem);
        }        
        pthread_mutex_lock(mutex);
        
        DllPushFront(dll, &message[i]);
        message_number += 1;
        pthread_cond_broadcast(&ready);
        pthread_mutex_unlock(mutex);
        
        ++i;
    }
    return NULL;
}

void* PopDllBarrier(void* data)
{
    size_t i = 0;
    dll_t* dll = ((dll_lock_t*)data)->dll;
    int message = 0;
    int thread_message_number = 0;
    pthread_mutex_t* mutex = ((dll_lock_t*)data)->mutex;
    
    while (i < TWENTY - 1)
    {     
        thread_message_number = message_number;
        sem_post(&number_thread_sem);
        
        pthread_mutex_lock(mutex);
        while (thread_message_number == message_number)
        {
            pthread_cond_wait(&ready, mutex);
        }  
        message = *(int*)DllGetData(DllBegin(dll));
        pthread_mutex_unlock(mutex);
        
        ++i;
        printf("message number %ld is : %d\n", i, message);
    }

    return NULL;
}

void Exercise1(void)
{
    size_t i = 0;
    pthread_t thread[TWO] = {0};
    cbuff_t* cbuff = CBuffCreate(10);

    if (SUCCESS != pthread_create(&thread[0], NULL, InsertCBuff, (void*)cbuff))
    {
        perror("could not create a thread");
    }

    if (SUCCESS != pthread_create(&thread[1], NULL, PopCBuff, (void*)cbuff))
    {
        perror("could not create a thread");
    }

    for(i = 0; i < TWO; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }
}

void Exercise2(void)
{
    size_t i = 0;
    pthread_t thread[TEN] = {0};
    dll_t* dll = DllCreate();
    pthread_mutex_t mutex = {0};
    dll_lock_t dll_lock[TEN] = {0};
    if (0 != pthread_mutex_init(&mutex, NULL)) 
    {
        return;
    }
    for (i = 0; i < TEN / 2; ++i)
    {
        dll_lock[i].dll = dll;
        dll_lock[i].mutex = &mutex;
        dll_lock[i].message = i + 1;
        if (SUCCESS != pthread_create(&thread[i], NULL, InsertDll, (void*)&dll_lock[i]))
        {
            perror("could not create a thread");
        }
    }

    for (i = TEN / 2; i < TEN; ++i)
    {
        dll_lock[i].dll = dll;
        dll_lock[i].mutex = &mutex;
        if (SUCCESS != pthread_create(&thread[i], NULL, PopDll, (void*)&dll_lock[i]))
        {
            perror("could not create a thread");
        }
    }

    for(i = 0; i < TEN; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }
    DllDestroy(dll);
}

void Exercise3(void)
{
    size_t i = 0;
    pthread_t thread[TEN] = {0};
    dll_t* dll = DllCreate();
    pthread_mutex_t mutex = {0};
    dll_lock_t dll_lock[TEN] = {0};

    sem_init(&read_sem, 0, 0);

    if (0 != pthread_mutex_init(&mutex, NULL)) 
    {
        return;
    }
    for (i = 0; i < TEN / 2; ++i)
    {
        dll_lock[i].dll = dll;
        dll_lock[i].mutex = &mutex;
        dll_lock[i].message = i + 1;
        if (SUCCESS != pthread_create(&thread[i], NULL, InsertDllOneSem, (void*)&dll_lock[i]))
        {
            perror("could not create a thread");
        }
    }

    for (i = TEN / 2; i < TEN; ++i)
    {
        dll_lock[i].dll = dll;
        dll_lock[i].mutex = &mutex;
        if (SUCCESS != pthread_create(&thread[i], NULL, PopDllOneSem, (void*)&dll_lock[i]))
        {
            perror("could not create a thread");
        }
    }

    for(i = 0; i < TEN; ++i)
    {
        if (SUCCESS != pthread_join(thread[i], NULL))
        {
            perror("could not destroy a thread");
        }
    }
    DllDestroy(dll);
}

void Exercise4(void)
{
    size_t i = 0;
    pthread_t thread[TWENTY] = {0};
    cbuff_t* cbuff = CBuffCreate(5);
    pthread_mutex_t mutex = {0};
    cbuff_lock_t cbuff_lock[TWENTY] = {0};

    sem_init(&write_sem, 0, 5);
    sem_init(&read_sem, 0, 0);

    if (0 != pthread_mutex_init(&mutex, NULL))
    {
        return;
    }
    for (i = 0; i < TWENTY / 2; ++i)
    {
        cbuff_lock[i].cbuff = cbuff;
        cbuff_lock[i].mutex = &mutex;
        cbuff_lock[i].message = (char)(i + 1);

        if (SUCCESS != pthread_create(&thread[i], NULL, InsertCBuffTwoSem, (void*)&cbuff_lock[i]))
        {
            perror("could not create a thread");
        }
    }

    for (i = TWENTY / 2; i < TWENTY; ++i)
    {
        cbuff_lock[i].cbuff = cbuff;
        cbuff_lock[i].mutex = &mutex;
        if (SUCCESS != pthread_create(&thread[i], NULL, PopCBuffTwoSem, (void*)&cbuff_lock[i]))
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
    CBuffDestroy(cbuff);
}

void Exercise6(void)
{
    size_t i = 0;
    pthread_t thread[TWENTY] = {0};
    dll_t* dll = DllCreate();
    pthread_mutex_t mutex = {0};
    dll_lock_t dll_lock[TWENTY] = {0};

    sem_init(&number_thread_sem, 0, 0);
    pthread_cond_init(&ready, NULL);

    if (0 != pthread_mutex_init(&mutex, NULL)) 
    {
        return;
    }
    
    dll_lock[0].dll = dll;
    dll_lock[0].mutex = &mutex;

    if (SUCCESS != pthread_create(&thread[0], NULL, InsertDllBarrier, (void*)&dll_lock[0]))
    {
        perror("could not create a thread");
    }

    for (i = 1; i < TWENTY; ++i)
    {
        dll_lock[i].dll = dll;
        dll_lock[i].mutex = &mutex;
        if (SUCCESS != pthread_create(&thread[i], NULL, PopDllBarrier, (void*)&dll_lock[i]))
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
    pthread_cond_destroy(&ready);
    DllDestroy(dll);
}

int main()
{
    printf("exercise 1:\n");
    Exercise1();
    printf("\nexercise 2:\n");
    Exercise2();
    printf("\nexercise 3:\n");
    Exercise3();
    printf("\nexercise 4:\n");
    Exercise4();
    printf("\nexercise 6:\n");
    Exercise6();

    return 0;
}

