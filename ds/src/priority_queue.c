/**********************
* priority queue
* Author: Tal Frank
* Reviewer: Or Zelner
* Last update: 06/05/2026
**********************/

#include <stdlib.h> /* malloc , free */
#include <stdio.h> /* NULL */
#include <assert.h> /* assert */

#include "heap.h"
#include "priority_queue.h"

struct priority_queue
{
	heap_t* heap;
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
	
	pq->heap = HeapCreate(CmpFunc);
	if (NULL == pq->heap)
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
	
	HeapDestroy(pq->heap);
	pq->heap = NULL;
	
	free(pq);
	pq = NULL;
}


int PQEnqueue(pq_t* pq, void* data)
{
	assert(NULL != pq);
	
	return HeapPush(pq->heap, data);
}


void* PQDequeue(pq_t* pq)
{
	void* data = NULL;
	assert(NULL != pq);

	data = HeapPeek(pq->heap);
	HeapPop(pq->heap);
	return data;
}

void* PQPeek(const pq_t* pq)
{
	assert(NULL != pq);
	assert(!PQIsEmpty(pq));
	
	return HeapPeek(pq->heap);
}


int PQIsEmpty(const pq_t* pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap);
}


size_t PQSize(const pq_t* pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap);
}


void PQClear(pq_t* pq)
{
	assert(NULL != pq);
	
	HeapClear(pq->heap);
}


void* PQErase(pq_t* pq, int (*IsMatch)(const void* data, const void* param),const void* param)
{	
	return HeapRemove(pq->heap, IsMatch, (void*)param);
}




