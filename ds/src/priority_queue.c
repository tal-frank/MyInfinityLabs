/**********************
* priority queue
* Author: Tal Frank
* Reviewer: Or Zelner
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
	pq_t* pq = (pq_t*)malloc(sizeof(pq_t));
	if (NULL == pq)
	{
		return NULL;
	}
	
	pq->sl = SortedListCreate(CmpFunc);
	if (NULL == pq->sl)
	{
		free(pq);
		pq = NULL;
		return NULL;
	}
	
	return pq;
}


void PQDestroy(pq_t* pq)
{
	assert(NULL != pq);	
	
	SortedListDestroy(pq->sl);
	pq->sl = NULL;
	
	free(pq);
	pq = NULL;
}


int PQEnqueue(pq_t* pq, const void* data)
{
	assert(NULL != pq);
	
	return (SortedListIsIterEqual(SortedListInsert(pq->sl, data), SortedListEnd(pq->sl)));
}


void* PQDequeue(pq_t* pq)
{
	assert(NULL != pq);
	
	return SortedListPopFront(pq->sl);
}

void* PQPeek(const pq_t* pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
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
	sorted_list_iter_t element_to_remove = {0};
	
	assert(NULL != pq);
	
	element_to_remove = SortedListFindIf(SortedListBegin(pq->sl), SortedListEnd(pq->sl), IsMatch, param);
	if (!SortedListIsIterEqual(element_to_remove, SortedListEnd(pq->sl)))
	{
		data = SortedListGetData(element_to_remove);
		SortedListRemove(element_to_remove);
	}
	
	return data;
}




