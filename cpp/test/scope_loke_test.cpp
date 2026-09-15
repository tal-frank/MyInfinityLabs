#include <pthread.h>
#include <cstddef>
#include <unistd.h>
#include <iostream>

#include "scope_lock.hpp"

enum
{
    SUCCESS = 0,
    FAILURE
};

void* PrintSomething(void* mutex)
{
    LockHolder lock(*(pthread_mutex_t*)mutex);
    sleep(2);
    std::cout << "thread finished" << std::endl;
    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_t mutex;
    if (0 != pthread_mutex_init(&mutex, NULL)) 
    {
        std::cout << "could not create mutex" << std::endl;
    }

    if (SUCCESS != pthread_create(&thread1, NULL, PrintSomething, (void*)&mutex)
     || SUCCESS != pthread_create(&thread1, NULL, PrintSomething, (void*)&mutex))
    {
        std::cout << "could not create thread" << std::endl;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}