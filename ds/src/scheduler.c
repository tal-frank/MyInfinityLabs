/*
 * Author: Ori Joseph
 * Reviewer: Roman
 * Last changed: 11.5.26
 * */
#include <stdlib.h> /* malloc, free, NULL*/
#include <assert.h> /* assert */
#include <time.h>   /* time */
#include <unistd.h> /* sleep */

#include "priority_queue.h"
#include "task.h"
#include "uid.h"
#include "scheduler.h"

struct Scheduler
{
    pq_t *pq;
    task_t *curr_task;
    volatile int stop_flag;
};

typedef enum
{
    FAIL = -1,
    SUCCESS = 0
} status_t;

static int SchedTaskCmp(const void *task1, const void *task2);
static int SchedTaskIsMatch(const void *task, const void *uid);
static void SleepUntilExecutionTime(const task_t *task);

sched_t *SchedCreate()
{
    pq_t *pq = NULL;
    sched_t *sched = (sched_t *)malloc(sizeof(sched_t));
    if (NULL == sched)
    {
        return NULL;
    }

    pq = PQCreate(&SchedTaskCmp);
    if (NULL == pq)
    {
        free(sched);
        sched = NULL;
        return NULL;
    }

    sched->pq = pq;
    sched->curr_task = NULL;
    sched->stop_flag = 0;

    return sched;
}

void SchedDestroy(sched_t *sched)
{
    assert(NULL != sched);
    SchedClear(sched);
    PQDestroy(sched->pq);
    sched->pq = NULL;
    free(sched);
    sched = NULL;
}

ilrd_uid_t SchedTaskAdd(sched_t *sched,
                        size_t interval,
                        time_t time_to_run,
                        int (*op_func)(void *param),
                        int (*clean_func)(void *param),
                        void *param)
{
    status_t status = SUCCESS;
    task_t *task = NULL;

    assert(NULL != op_func);
    assert(NULL != sched);

    task = TaskCreate(interval, time_to_run, op_func,
                      clean_func, param);
    if (NULL == task)
    {
        return UIDBadUID;
    }

    status = PQEnqueue(sched->pq, task);
    if (SUCCESS != status)
    {
        TaskDestroy(task);
        return UIDBadUID;
    }

    return TaskGetUid(task);
}

int SchedTaskRemove(sched_t *sched, ilrd_uid_t uid)
{
    task_t *task = NULL;

    assert(NULL != sched);

    if (NULL != sched->curr_task &&
        UIDIsEqual(uid, TaskGetUid(sched->curr_task)))
    {
        sched->curr_task = NULL;
        return SUCCESS;
    }

    task = (task_t *)PQErase(sched->pq, SchedTaskIsMatch, &uid);
    if (NULL == task)
    {
        return FAIL;
    }

    TaskDestroy(task);
    return SUCCESS;
}

int SchedRun(sched_t *sched)
{
    task_t *task = NULL;
    int status = SUCCESS;

    assert(NULL != sched);

    sched->stop_flag = 0;

    while (!sched->stop_flag &&
           !SchedIsEmpty(sched))
    {
        task = PQDequeue(sched->pq);
        sched->curr_task = task;

        SleepUntilExecutionTime(task);

        status = TaskRun(task);

        if (SUCCESS != status ||
            !TaskIsRepeatable(task) ||
            NULL == sched->curr_task)
        {
            TaskDestroy(task);
        }
        else
        {
            TaskUpdateTimeToRun(task);
            status = PQEnqueue(sched->pq, task);
            if (SUCCESS != status)
            {
                TaskDestroy(task);
                sched->curr_task = NULL;
                return status;
            }
        }

        sched->curr_task = NULL;
    }
    return SUCCESS;
}

void SchedStop(sched_t *sched)
{
    assert(NULL != sched);
    sched->stop_flag = 1;
}

int SchedIsEmpty(const sched_t *sched)
{
    assert(NULL != sched);
    return NULL == sched->curr_task && PQIsEmpty(sched->pq);
}

size_t SchedCount(const sched_t *sched)
{
    size_t count = 0;

    assert(NULL != sched);

    count = PQSize(sched->pq);
    if (NULL != sched->curr_task)
    {
        ++count;
    }
    return count;
}

void SchedClear(sched_t *sched)
{
    task_t *task = NULL;

    assert(NULL != sched);

    while (!SchedIsEmpty(sched))
    {
        task = (task_t *)PQDequeue(sched->pq);
        TaskDestroy(task);
    }

    sched->curr_task = NULL;
}

static int SchedTaskCmp(const void *task1, const void *task2)
{
    return (int)TaskGetTimeToRun((task_t *)task1) - (int)TaskGetTimeToRun((task_t *)task2);
}

static int SchedTaskIsMatch(const void *task, const void *uid)
{
    return UIDIsEqual(TaskGetUid((task_t *)task), *(ilrd_uid_t *)uid);
}

static void SleepUntilExecutionTime(const task_t *task)
{
    time_t ttr = TaskGetTimeToRun(task);
    while (ttr > time(NULL))
    {
        sleep(ttr - time(NULL));
    }
}


