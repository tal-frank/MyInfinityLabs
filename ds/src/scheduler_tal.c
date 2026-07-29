/**********************
* schedualer
* Author: Tal Frank
* Reviewer: Moshe Moiseev
* Last update: 10/05/2026
**********************/

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc , free*/
#include <assert.h> /* assert */
#include <time.h> /* time() , time_t */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "priority_queue.h"
#include "task.h"
#include "uid.h"

#define NOT_EMPTY (0)
#define RUN (1)
#define DONT_RUN (0)

struct Scheduler
{
    pq_t* pq;
    task_t* current_task;
    int to_run;
};

typedef enum
{
	FAILURE = -1,
	SUCCESS
}status_t;


/*------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATION *************************/
/*------------------------------------------------------------------------------*/

static int UidIsEqualWrapper(const void* sched1, const void* sched2);
static int SchedTaskCmp(const void* sched1_param, const void* sched2_param);
static status_t UpdateAndPush(sched_t* sched);
static void WaitForOperationTime(time_t ttr);


/*-----------------------------------------------------------------*/
/************************* CREAT & DESTROY *************************/
/*-----------------------------------------------------------------*/

sched_t* SchedCreate(void)
{
	sched_t* sched = (sched_t*)malloc(sizeof(sched_t));
	if (NULL == sched)
	{
		return NULL;
	}
	sched->pq = PQCreate(SchedTaskCmp);
	if (NULL == sched->pq)
	{
		free(sched);
		sched = NULL;
		return NULL;
	}
	sched->current_task = NULL;
	sched->to_run = DONT_RUN;
	
	return sched;
}


void SchedDestroy(sched_t* sched)
{
	assert(NULL != sched);
	
	SchedClear(sched);
	PQDestroy(sched->pq);
	sched->pq = NULL;
	free(sched);
	sched = NULL;
}


/*----------------------------------------------------------*/
/************************* IS EMPTY *************************/
/*----------------------------------------------------------*/

int SchedIsEmpty(const sched_t* sched)
{
	assert(NULL != sched);
	
	if (NULL != sched->current_task)
	{
		return NOT_EMPTY;
	}
	return PQIsEmpty(sched->pq);
}





/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

size_t SchedCount(const sched_t* sched)
{
	assert(NULL != sched);
	
	if (NULL != sched->current_task)
	{
		return 1 + PQSize(sched->pq);
	}
	
	return PQSize(sched->pq);
}


/*----------------------------------------------------------------*/
/************************* CLEAR & REMOVE *************************/
/*----------------------------------------------------------------*/

void SchedClear(sched_t* sched)
{
	assert(NULL != sched);
	
	while (!SchedIsEmpty(sched))
	{
		TaskDestroy((task_t*)PQDequeue(sched->pq));
	}
}


int SchedTaskRemove(sched_t* sched, ilrd_uid_t uid)
{
	task_t* task = NULL;
	
	assert(NULL != sched);
	
	if (NULL != sched->current_task &&
	    UIDIsEqual(uid, TaskGetUid(sched->current_task)))
	{
		sched->current_task = NULL;
		return SUCCESS;
	}
	
	task = PQErase(sched->pq, UidIsEqualWrapper , &uid);
	if (NULL == task)
	{
		return FAILURE;
	}
	TaskDestroy(task);

	return SUCCESS;
}


/*----------------------------------------------------------*/
/************************* ADD TASK *************************/
/*----------------------------------------------------------*/

ilrd_uid_t SchedTaskAdd(sched_t* sched,
                   	size_t interval,
                   	time_t time_to_run,
                   	int (*op_func)(void* param),
                   	int (*clean_func)(void* param),
                   	void* param)
{
	task_t* task = NULL;
	
	assert(NULL != sched);
	assert(NULL != op_func);
	
	task = TaskCreate(interval, time_to_run, op_func, clean_func, param);
	if (NULL == task)
	{
		return UIDBadUID;
	}
	
	if (SUCCESS != PQEnqueue(sched->pq, task))
	{
		TaskDestroy(task);
		task = NULL;
		return UIDBadUID;
	}
	
	return TaskGetUid(task);
}


/*------------------------------------------------------------*/
/************************* RUN & STOP *************************/
/*------------------------------------------------------------*/

int SchedRun(sched_t* sched)
{
	time_t current_time = 0;
	task_t* task = NULL;
	sched->to_run = RUN;
	time(&current_time);
	
	assert(NULL != sched);
	
	while (sched->to_run && !SchedIsEmpty(sched))
	{
		sched->current_task = (task_t*)PQDequeue(sched->pq);
		task = sched->current_task;
		
		WaitForOperationTime(TaskGetTimeToRun(task));
		
		if ((SUCCESS != TaskRun(task) || 
		    !TaskIsRepeatable(task))  ||
		    NULL == sched->current_task)
		{
			TaskDestroy(task);
			task = NULL;
			sched->current_task = NULL;
			continue;
		}

		if (FAILURE == UpdateAndPush(sched))
		{
			sched->to_run = DONT_RUN;
			return FAILURE;
		}

		sched->current_task = NULL;
	}

	return SUCCESS;
}

void SchedStop(sched_t* sched)
{
	assert(NULL != sched);
	
	sched->to_run = DONT_RUN;
}

/*------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATION *************************/
/*------------------------------------------------------------------------------*/

static void WaitForOperationTime(time_t ttr)
{
	time_t time_to_run = ttr - time(NULL);
	while(time_to_run)
	{
		time_to_run = sleep(time_to_run);
	}
}

static status_t UpdateAndPush(sched_t* sched)
{
	TaskUpdateTimeToRun(sched->current_task);
	if (SUCCESS != PQEnqueue(sched->pq, sched->current_task))
	{
		TaskDestroy(sched->current_task);
		return FAILURE;
	}
	return SUCCESS;
}

static int UidIsEqualWrapper(const void* data, const void* param_uid)
{
	task_t* task = (task_t*)data;
	ilrd_uid_t* uid = (ilrd_uid_t*)param_uid;
	
	return UIDIsEqual(TaskGetUid(task), *uid);
}


static int SchedTaskCmp(const void* task1_param, const void* task2_param)
{
	task_t* task1 = (task_t*)task1_param;
	task_t* task2 = (task_t*)task2_param;
	
	return TaskGetTimeToRun(task1) - TaskGetTimeToRun(task2);
}

