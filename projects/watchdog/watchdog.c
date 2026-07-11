#define _POSIX_C_SOURCE 200809L

#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* sem_open */
#include <unistd.h> /* exec , fork*/
#include <fcntl.h> /* O_CREAT */
#include <time.h> /* time */
#include <signal.h> /* SIGUSER1 , sigaction */
#include <stdlib.h> /* getenv */
#include <errno.h> /* perror */

#include "watchdog.h"
#include "scheduler.h"

#define UNUSED(x) ((void)x)

#define ONE_SEC (1)
#define FIVE_SEC (5)
#define WD_PATH ("./wd.out")

enum
{
    FALSE = 0,
    TRUE
};

/*------------------------------------------------------------------*/
/************************* GLOBAL VARIABLES *************************/
/*------------------------------------------------------------------*/

sched_t* sched = NULL;
static int counter = 0;
int is_watch_dog = FALSE;
int finish = 0;
pid_t pid = 0;

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/


/*----------------------------------------------------------*/
/************************* WDSTRART *************************/
/*----------------------------------------------------------*/

wd_status_t WDStart(char* argv[])
{
    pid_t pid = 0;
    wd_status_t status = SUCCESS;
    char* wd_pid_env = getenv(argv[0]);   
    sem_t* sync_sem = sem_open("sync_sem", O_CREAT);

    InitSignals();
      
    if (NULL == wd_pid_env)
    {
        pid = fork();
        setenv(argv[0], "1", 1);
        if (0 != pid)
        {
            status = InitProcess(argv);
        }
        else
        {
            execv(WD_PATH, argv); 
            perror("could not create watchdog");
        }
    }
    else if (TRUE == is_watch_dog)
    {
        InitSched(argv);
        sem_post("sync_sem");
        SchedRun(sched);
        SchedDestroy(sched);
    }
    else
    {
        status = InitProcess(argv);
    }

    return status;
}

/*--------------------------------------------------------*/
/************************* WDSTOP *************************/
/*--------------------------------------------------------*/

wd_status_t WDStop(time_t timeout)
{
    wd_status_t status = SUCCESS;
    finish = 1;
    kill((0 == pid) ? getpid() : getppid() , SIGUSR2);
    sem_wait("sync_sem");

    return status;
}

/*----------------------------------------------------------*/
/************************* HANDLERS *************************/
/*----------------------------------------------------------*/

static void* ProcessSchedHandler(void* data) /* todo : set arguments, decide pid transfer */
{
    UNUSED(data); 
    SchedRun(sched);
}

static void CounterIncrement(int data)
{
    UNUSED(data);
    ++counter;
}

static void closeWD(int data)
{
    UNUSED(data);
    finish = 1;
}

/*-----------------------------------------------------------------*/
/************************* TASKS FUNCTIONS *************************/
/*-----------------------------------------------------------------*/

static int SendSignal(void* data)
{
    UNUSED(data);
    kill((0 == pid) ? getpid() : getppid() , SIGUSR1);
    return SUCCESS;
}

static int CheckCounter(char argv[])
{
    if (0 == counter)
    {
        if (is_watch_dog)
        {
            WatchdogErrorHandler(argv);
        }
        else
        {
            ProcessErrorHandler(argv);
        }
    }
    counter = 0;
    return SUCCESS;
}

static int CheckFinish(void)
{
    wd_status_t status = SUCCESS;
    if (1 == finish)
    {
        if (1 == is_watch_dog)
        {
            status = WDStopSched();
        }
        else
        {
            SchedDestroy(sched);
        }
    }
    return status;
}

/*-------------------------------------------------------------*/
/************************* INITALIZERS *************************/
/*-------------------------------------------------------------*/

static void InitSched(char* argv[])
{
    sched = SchedCreate();
    SchedTaskAdd(sched,             /* todo : add failure check */
                    ONE_SEC, 
                    time(NULL) + ONE_SEC, 
                    SendSignal, 
                    NULL, 
                    NULL);
    SchedTaskAdd(sched, 
                    FIVE_SEC, 
                    time(NULL) + FIVE_SEC, 
                    CheckCounter, 
                    NULL, 
                    (void*)argv);
    SchedTaskAdd(sched, 
                    ONE_SEC, 
                    time(NULL) + ONE_SEC, 
                    CheckFinish, 
                    NULL, 
                    (void*)argv);
    return sched;
}

static void InitSignals(void)
{
    struct sigaction living_signal = {0};
    struct sigaction kill_signal = {0};

    living_signal.sa_handler = CounterIncrement;
    kill_signal.sa_handler = closeWD;

    sigaction(SIGUSR1, &living_signal, NULL);
    sigaction(SIGUSR2, &kill_signal, NULL);
}

static wd_status_t InitProcess(char* argv[])
{
    pthread_t sched_thread = 0;

    InitSched(argv);
    sem_wait("sync_sem");
    if (SUCCESS != pthread_create(&sched_thread, NULL, ProcessSchedHandler, NULL))
    {
        return THREAD_CREATE_FAILURE;
    }
    return SUCCESS;
}

/*----------------------------------------------------------------*/
/************************* ERROR HANDLERS *************************/
/*----------------------------------------------------------------*/

static void ProcessErrorHandler(void* data)
{
    char* argv[] = (char**)data;
    pid = fork();
    if (0 == pid)
    {
        exec(WD_PATH, argv); 
        perror("could not create new watchdog");
    }
    sem_wait("sync_sem");
}

static void watchdogErrorHandler(void* data)
{
    char* argv[] = (char**)data;
    pid = fork();
    if (0 == pid)
    {
        execv(argv[0], argv); 
        perror("could not create new process");
    }
}

static wd_status_t WDStopSched(void)
{
    SchedTaskAdd(sched, 
                ONE_SEC, 
                time(NULL) + ONE_SEC, 
                SchedStop, 
                NULL, 
                sched);
}