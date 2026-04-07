/**********************
* queue
* Author: Tal Frank
* Reviewer: 
* Last update: 07/04/2026
**********************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/

#include "../include/queue.h"
#include "../include/singly_linked_list.h"


struct Queue
{
	sll_t* sll;
};

enum
{
	SUCCESS = 0,
	FAILURE
};


/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

queue_t* QueueCreate(void)
{
	queue_t* queue = NULL;
	
	queue = (queue_t*)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue->sll = SllCreate();
	if (NULL == queue->sll)
	{
		printf("can't creat struct\n");
		free(queue);
		return NULL;
	}
	return queue;
}


void QueueDestroy(queue_t* queue)
{
	assert(NULL != queue);	
	
	SllDestroy(queue->sll);
	queue->sll = NULL;
	free(queue);
	queue = NULL;
}


/*-------------------------------------------------------------------*/
/************************* ENQUEUE & DEQUEUE *************************/
/*-------------------------------------------------------------------*/

int QueueEnqueue(queue_t* queue, const void* element)
{
	sll_iter_t first = 0;
	
	assert(NULL != queue);
	
	first = SllBegin(queue->sll);
	
	if (SllIterIsEqual(first, SllInsertBefore(SllEnd(queue->sll), element)))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}


void QueueDequeue(queue_t* queue)
{
	assert(NULL != queue);	
	
	SllRemove(SllBegin(queue->sll));
}


/*-----------------------------------------------------------------*/
/************************* SIZE & IS EMPTY *************************/
/*-----------------------------------------------------------------*/

int QueueIsEmpty(const queue_t* queue)
{
	assert(NULL != queue);	
	
	return SllIsEmpty(queue->sll);
}


size_t QueueSize(const queue_t* queue)
{
	return SllGetLength(queue->sll);
}


/*------------------------------------------------------*/
/************************* PEEK *************************/
/*------------------------------------------------------*/

void* QueuePeek(const queue_t* queue)
{
	assert(NULL != queue);
	
	return SllGetData(SllBegin(queue->sll));
}


/*--------------------------------------------------------*/
/************************* APPEND *************************/
/*--------------------------------------------------------*/

void QueueAppend(queue_t* dest, queue_t* src)
{
	assert(NULL != dest);
	assert(NULL != src);
	dest->sll = SllAppend(dest->sll, src->sll);
}


