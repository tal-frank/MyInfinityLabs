/**********************
* watchdog
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 26/07/2026
**********************/

#define _POSIX_C_SOURCE 200809L

#include <pthread.h> /* pthread_create */
#include <semaphore.h> /* sem_open */
#include <unistd.h> /* exec , fork*/
#include <fcntl.h> /* O_CREAT */
#include <time.h> /* time */
#include <signal.h> /* SIGUSER1 , sigaction */
#include <stdlib.h> /* getenv */
#include <errno.h> /* perror */

#include <stdio.h> /*tests*/

#include "watchdog.h"
#include "scheduler.h"
#include "uid.h"

#define UNUSED(x) ((void)x)

#define ATOMIC_SET_ZERO (0)
#define ATOMIC_ADD_ONE (1)
#define ONE_SEC (1)
#define FIVE_SEC (5)
#define WD_PATH ("wd.out")
#define NAMED_SEM ("sync_sem")
#define SEM_INIT (0666)

enum
{
    FALSE = 0,
    TRUE
};

/*------------------------------------------------------------------*/
/************************* GLOBAL VARIABLES *************************/
/*------------------------------------------------------------------*/

static sched_t* sched = NULL;
static volatile int counter = 0;
volatile int is_watch_dog = FALSE;
volatile int finish = 0;
volatile pid_t pid = {0};
static pthread_t sched_thread = {0};

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static void* ProcessSchedHandler(void* data);
static void CounterIncrement(int data);
static void closeWD(int data);
static int SendLivingSignal(void* data);
static int CheckCounter(void* data);
static int CheckFinish(void* data);
static wd_status_t ProcessCrushHandler(void* data);
static wd_status_t WatchdogCrushHandler(void* data);
static wd_status_t InitSched(char* argv[]);
static void InitSignals(void);
static wd_status_t InitProcess(char* argv[]);

/*----------------------------------------------------------*/
/************************* WDSTRART *************************/
/*----------------------------------------------------------*/

wd_status_t WDStart(char* argv[])
{
    wd_status_t status = SUCCESS;
    char* wd_pid_env = getenv(argv[0]);

    sem_t* sync_sem = sem_open(NAMED_SEM, O_CREAT, SEM_INIT);

    InitSignals();
    if (TRUE == is_watch_dog)
    {
        if (SUCCESS != InitSched(argv))
        {
            return SCHED_CREATE_FAILURE;
        }
        
        sem_post(sync_sem);
        kill((0 == pid) ? getppid() : pid, SIGCONT);
        SchedRun(sched);
        SchedDestroy(sched);
    }
    else if (NULL == wd_pid_env)
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
            return DAEMON_CREATE_FAILURE;
        }
    }
    else
    {
        status = InitProcess(argv);
    }
    sem_close(sync_sem);
    return status;
}

/*--------------------------------------------------------*/
/************************* WDSTOP *************************/
/*--------------------------------------------------------*/

wd_status_t WDStop(time_t timeout)
{
    wd_status_t status = SUCCESS;
    time_t time_left = timeout;
    
    kill((0 == pid) ? getppid() : pid , SIGUSR2);
    while (0 == finish && 0 != time_left)
    {
        time_left = sleep(time_left);
    }
    if (0 == finish)
    {
        finish = 1;
        status = STOP_TIMEOUT;
    }

    sem_unlink(NAMED_SEM);
    pthread_join(sched_thread, NULL);
    
    return status;
}

/*----------------------------------------------------------*/
/************************* HANDLERS *************************/
/*----------------------------------------------------------*/

static void* ProcessSchedHandler(void* data) 
{
    UNUSED(data); 
    SchedRun(sched);
    SchedDestroy(sched);
    return NULL;
}

static void CounterIncrement(int data)
{
    UNUSED(data);
    __sync_add_and_fetch(&counter, ATOMIC_ADD_ONE);
}

static void closeWD(int data)
{
    UNUSED(data);
    finish = 1;
}

/*-----------------------------------------------------------------*/
/************************* TASKS FUNCTIONS *************************/
/*-----------------------------------------------------------------*/

static int SendLivingSignal(void* data)
{
    UNUSED(data);
    kill((0 == pid) ? getppid() : pid, SIGUSR1);
    return SUCCESS;
}

static int CheckCounter(void* data)
{
    wd_status_t status = SUCCESS;
    char** argv = (char**)data;
    FILE* wd_log = fopen("watchdog_log.txt","a");
    if (0 == counter)
    {
        if (is_watch_dog)
        {
            status = WatchdogCrushHandler(argv);
        }
        else
        {
            status = ProcessCrushHandler(argv);
        }
    }

    fprintf(wd_log, "counter = %d -- process pid = %d\n", counter, getpid());
    fclose(wd_log);
    __sync_lock_test_and_set(&counter, ATOMIC_SET_ZERO);

    return status;
}

static int CheckFinish(void* data)
{
    wd_status_t status = SUCCESS;
    
    UNUSED(data);
    if (1 == finish)
    {
        SchedStop(sched);
        kill((0 == pid) ? getppid() : pid , SIGUSR2);
    }
    return status;
}

/*-------------------------------------------------------------*/
/************************* INITALIZERS *************************/
/*-------------------------------------------------------------*/

static wd_status_t InitSched(char* argv[])
{
    sched = SchedCreate();
    if (NULL == sched)
    {
        return SCHED_CREATE_FAILURE;
    }
    if (UIDIsEqual(UIDBadUID, SchedTaskAdd(sched,
                                           ONE_SEC, 
                                           0, 
                                           SendLivingSignal, 
                                           NULL, 
                                           NULL)))
    {
        return SCHED_CREATE_FAILURE;
    }
    if (UIDIsEqual(UIDBadUID, SchedTaskAdd(sched, 
                                           FIVE_SEC, 
                                           time(NULL) + FIVE_SEC, 
                                           CheckCounter, 
                                           NULL, 
                                           (void*)argv)))
    {
        return SCHED_CREATE_FAILURE;
    }
    if (UIDIsEqual(UIDBadUID, SchedTaskAdd(sched, 
                                           ONE_SEC, 
                                           0, 
                                           CheckFinish, 
                                           NULL, 
                                           NULL)))
    {
        return SCHED_CREATE_FAILURE;
    }
    return SUCCESS;
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
    sem_t* sync_sem = {0};
    
    sync_sem = sem_open(NAMED_SEM, O_CREAT, SEM_INIT);
    sem_wait(sync_sem);
   
    if (SUCCESS != InitSched(argv))
    {
        return SCHED_CREATE_FAILURE;
    }
    
    if (SUCCESS != pthread_create(&sched_thread, NULL, ProcessSchedHandler, NULL))
    {
        return THREAD_CREATE_FAILURE;
    }

    sem_close(sync_sem);
    return SUCCESS;
}

/*----------------------------------------------------------------*/
/************************* ERROR HANDLERS *************************/
/*----------------------------------------------------------------*/

static wd_status_t ProcessCrushHandler(void* data)
{
    char** argv = (char**)data;
    sem_t* sync_sem = {0};
    pid = fork();
    if (0 == pid)
    {
        execv(WD_PATH, argv); 
        return DAEMON_CREATE_FAILURE;
    }
    kill(getpid() , SIGSTOP);
    sync_sem = sem_open(NAMED_SEM, O_CREAT, SEM_INIT);
    sem_wait(sync_sem);
    sem_close(sync_sem);
    return SUCCESS;
}

static wd_status_t WatchdogCrushHandler(void* data)
{
    char** argv = (char**)data;

    pid = fork();
    if (0 == pid)
    {
        execv(argv[0], argv); 
        return REVIVE_USR_PROC_FAILURE;
    }
    return SUCCESS;
}

