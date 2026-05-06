/**********************
* priority queue
* Author: Tal Frank
* Reviewer: 
* Last update: 06/05/2026
**********************/

#include <stdlib.h> /* malloc , free */
#include <stdio.h> /* NULL */
#include <assert.h> /* assert */

#include "sorted_list.h"
#include "priority_queue.h"

struct priority_queue
{
	sorted_list_t* sl;
};

typedef enum
{
	SUCCESS = 0,
	FAILURE = 1
}status_t;

pq_t* PQCreate(int (*CmpFunc)(const void* data, const void* param))
{
	pq_t* p_q = (pq_t*)malloc(sizeof(p_q));
	if (NULL == p_q)
	{
		return NULL;
	}
	
	p_q->sl = SortedListCreate(CmpFunc);
	if (NULL == p_q->sl)
	{
		free(p_q);
		p_q = NULL;
		return NULL;
	}
	
	return p_q;
}


void PQDestroy(pq_t* pq)
{
	assert(NULL != pq);	
	
	SortedListDestroy(pq->sl);
	free(pq);
}


int PQEnqueue(pq_t* pq, const void* data)
{
	assert(NULL != pq);

	if (SortedListIsIterEqual(SortedListInsert(pq->sl, data), SortedListEnd(pq->sl)))
	{
		return FAILURE;
	}
	
	return SUCCESS;
}


void* PQDequeue(pq_t* pq)
{
	assert(NULL != pq);
	
	return SortedListPopFront(pq->sl);
}

void* PQPeek(const pq_t* pq)
{
	assert(NULL != pq);
	
	return SortedListGetData(SortedListBegin(pq->sl));
}


int PQIsEmpty(const pq_t* pq)
{
	assert(NULL != pq);
	
	return SortedListIsEmpty(pq->sl);
}


size_t PQSize(const pq_t* pq)
{
	assert(NULL != pq);
	
	return SortedListSize(pq->sl);
}


void PQClear(pq_t* pq)
{
	assert(NULL != pq);
	
	while(!SortedListIsEmpty(pq->sl))
	{
		SortedListPopFront(pq->sl);
	}
}


void* PQErase(pq_t* pq, int (*IsMatch)(const void* data, const void* param),const void* param)
{
	void* data = NULL;
	sorted_list_iter_t iter = {0};
	
	assert(NULL != pq);
	
	iter = SortedListFindIf(SortedListBegin(pq->sl), SortedListEnd(pq->sl), IsMatch, param);
	data = SortedListGetData(iter);
	SortedListRemove(iter);
	
	return data;
}




