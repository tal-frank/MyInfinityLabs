/**********************
* task
* Author: Tal Frank
* Reviewer: 
* Last update: 10/05/2026
**********************/

#include <stddef.h> /* NULL */
#include <stdlib.h> /* malloc , free*/
#include <assert.h> /* assert */
#include <time.h> /* time() , time_t */

#include "priority_queue.h"
#include "task.h"
#include "uid.h" /* uid API */

struct Task
{
    ilrd_uid_t uid;
    time_t time_to_run;
    size_t interval; 
    int (*op_func)(void* params);
    int (*clean_func)(void* params);
    void* params;   
};

/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

task_t* TaskCreate(size_t interval,
                   time_t time_to_run,
                   int (*op_func)(void* params),
                   int (*clean_func)(void* params),
                   void* params)
{
	task_t* task = (task_t*)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}
	
	assert(NULL != op_func);
	
	task->uid = UIDCreate();
	if (UIDIsEqual(task->uid, UIDBadUID))
	{
		free(task);
		task = NULL;
		return NULL;
	}
	
	task->interval = interval;
	task->time_to_run = time_to_run;
	task->op_func = op_func;
	task->clean_func = clean_func;
	task->params = params;
	
	return task;
}


void TaskDestroy(task_t* task)
{
	assert(NULL != task);
	
	if (NULL != task->clean_func)
	{
		task->clean_func(task->params);
	}
	free(task);
	task = NULL;
}


/*---------------------------------------------------------*/
/************************* GET UID *************************/
/*---------------------------------------------------------*/

ilrd_uid_t TaskGetUid(const task_t* task)
{
	assert(NULL != task);
	
	return task->uid;
}

/*--------------------------------------------------------------------------*/
/************************* GET & UPDATE TIME TO RUN *************************/
/*--------------------------------------------------------------------------*/

void TaskUpdateTimeToRun(task_t* task)
{
	assert(NULL != task);
	
	task->time_to_run += task->interval;
}

time_t TaskGetTimeToRun(const task_t* task)
{
	assert(NULL != task);
	
	return task->time_to_run;
}


/*--------------------------------------------------------------------------*/
/************************* IS REPEATABLE & IS EQUAL *************************/
/*--------------------------------------------------------------------------*/

int TaskIsRepeatable(const task_t* task)
{
	assert(NULL != task);
	
	return 0 != task->interval;
}

int TaskIsEqual(const task_t* task1, const task_t* task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	return UIDIsEqual(task1->uid, task2->uid);
}

/*----------------------------------------------------------*/
/************************* TASK RUN *************************/
/*----------------------------------------------------------*/

int TaskRun(task_t* task)
{
	assert(NULL != task);
	
	return task->op_func(task->params);
}


