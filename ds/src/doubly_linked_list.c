/**********************
* doubly linked list
* Author: Tal Frank
* Reviewer: Ori Yoseph
* Last update: 15/04/2026
**********************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "doubly_linked_list.h"

typedef struct Dll_Node dnode_t;

/*------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATION *************************/
/*------------------------------------------------------------------------------*/

static dll_iter_t NodeToIter(dnode_t* dnode);
static dnode_t* IterToNode(dll_iter_t iter);
static void LinkNodes(dnode_t* node_1, dnode_t* node_2);


/*---------------------------------------------------------*/
/************************* STRUCTS *************************/
/*---------------------------------------------------------*/

struct Doubly_linked_list
{
	dnode_t* head;
	dnode_t* tail;
};


struct Dll_Node
{
	dnode_t* next;
	dnode_t* prev;
	void* data;
};


/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

dll_t* DllCreate(void)
{
	dnode_t* head_dummy = NULL;
	dnode_t* tail_dummy = NULL;

	dll_t* dll = (dll_t*)malloc(sizeof(dll_t));
	if (NULL == dll)
	{
		return NULL;
	}
	
	head_dummy = (dnode_t*)malloc(sizeof(dnode_t));
	if (NULL == head_dummy)
	{
		free(dll);
		return NULL;
	}
	
	tail_dummy = (dnode_t*)malloc(sizeof(dnode_t));
	if (NULL == tail_dummy)
	{
		free(dll);
		free(head_dummy);
		return NULL;
	}
	
	head_dummy->prev = NULL;
	tail_dummy->next = NULL;

	head_dummy->data = dll;
	tail_dummy->data = dll;

	LinkNodes(head_dummy, tail_dummy);
	
	dll->head = head_dummy;
	dll->tail = tail_dummy;
	
	return dll;
}


void DllDestroy(dll_t* dll)
{
	dnode_t* freed = dll->head;
	dnode_t* iter = dll->head;
	
	assert(NULL != dll);
	
	while (!DllIsIterEqual(DllEnd(dll), iter))
	{
		iter = iter->next;
		free(freed);
		freed = iter;
	}
	free(dll->tail);
	free(dll);
}


/*-------------------------------------------------------------*/
/************************* BEGIN & END *************************/
/*-------------------------------------------------------------*/

dll_iter_t DllBegin(const dll_t* dll)
{	
	assert(NULL != dll);
	
	return DllGetNext(NodeToIter(dll->head));
}


dll_iter_t DllEnd(const dll_t* dll)
{
	assert(NULL != dll);
	
	return NodeToIter(dll->tail);
}


/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

size_t DllCount(const dll_t* dll)
{
	size_t cnt = 0;	
	dll_iter_t cnt_iter = DllBegin(dll);
	dll_iter_t end = DllEnd(dll);
	
	while(!DllIsIterEqual(cnt_iter, end))
	{
		cnt_iter = DllGetNext(cnt_iter);
		++cnt;
	}
	return cnt;
}


/*---------------------------------------------------------------------*/
/************************* GET NEXT & GET PREV *************************/
/*---------------------------------------------------------------------*/

dll_iter_t DllGetNext(dll_iter_t iter)
{
	dnode_t* dnode = IterToNode(iter);
	
	assert(NULL != dnode);
	
	dnode = dnode->next;
	return NodeToIter(dnode);
}

dll_iter_t DllGetPrev(dll_iter_t iter)
{
	dnode_t* dnode = IterToNode(iter);
	
	assert(NULL != dnode);
	
	dnode = dnode->prev;
	return NodeToIter(dnode);
}


/*---------------------------------------------------------------------*/
/************************* IS EQUAL & IS EMPTY *************************/
/*---------------------------------------------------------------------*/

int DllIsIterEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	return IterToNode(iter1) == IterToNode(iter2);
}


int DllIsEmpty(const dll_t* dll)
{
	assert(NULL != dll);

	return DllIsIterEqual(DllBegin(dll), DllEnd(dll));
}


void* DllGetData(dll_iter_t iter)
{
	dnode_t* dnode = IterToNode(iter);
	return NodeToIter(dnode->data);
}


/*-----------------------------------------------------------------*/
/************************* INSERT & REMOVE *************************/
/*-----------------------------------------------------------------*/

dll_iter_t DllInsert(dll_t* dll, dll_iter_t where, const void* data)
{
	dnode_t* prev_node = IterToNode(DllGetPrev(where));
	dnode_t* where_n = IterToNode(where);
	dnode_t* new_dnode = NULL;
	
	assert(NULL != dll);

	new_dnode = (dnode_t*)malloc(sizeof(dnode_t));
	if (NULL == new_dnode)
	{
		return DllEnd(dll);
	}
	
	new_dnode->data = (void*)data;
	LinkNodes(prev_node, new_dnode);
	LinkNodes(new_dnode, where_n);
	
	return NodeToIter(new_dnode);
}


dll_iter_t DllRemove(dll_iter_t iter)
{
	dnode_t* prev_node = IterToNode(DllGetPrev(iter));
	dnode_t* next_node = IterToNode(DllGetNext(iter));
	
	LinkNodes(prev_node, next_node);
	
	free(IterToNode(iter));
	return IterToNode(next_node);
}


/*------------------------------------------------------*/
/************************* FIND *************************/
/*------------------------------------------------------*/

dll_iter_t DllFind(dll_iter_t from, dll_iter_t to, 
		   int (*comp_func)(const void* data, const void* param), const void* param)
{	
	int compare = comp_func(DllGetData(from), param);

	assert(from != to);

	while (!DllIsIterEqual(to , from) && 0 != compare)
	{
		from = from->next;
		compare = comp_func(DllGetData(from), param);
	}
	return from;
}

/*---------------------------------------------------------*/
/************************* FOREACH *************************/
/*---------------------------------------------------------*/

dll_iter_t DllForEach(dll_iter_t from, dll_iter_t to, 
		      int (*action_func)(void* data, void* param), void* param)
{
	int failure = 0;
	while (!DllIsIterEqual(to , from) && !failure)
	{
		failure = action_func(DllGetData(from), param);
		from = DllGetNext(from);
	}
	return from;
}

/*-----------------------------------------------------------------*/
/************************* PUSH FRONT/BACK *************************/
/*-----------------------------------------------------------------*/

dll_iter_t DllPushFront(dll_t* dll, const void* data)
{
	assert(NULL != dll);

	return DllInsert(dll, DllBegin(dll), data);
}


dll_iter_t DllPushBack(dll_t* dll, const void* data)
{
	assert(NULL != dll);

	return DllInsert(dll, DllEnd(dll), data);
}


/*----------------------------------------------------------------*/
/************************* POP FRONT/BACK *************************/
/*----------------------------------------------------------------*/

dll_iter_t DllPopFront(dll_t* dll)
{
	assert(NULL != dll);

	return DllRemove(DllBegin(dll));
}


dll_iter_t DllPopBack(dll_t* dll)
{
	assert(NULL != dll);
	
	return DllRemove(DllGetPrev(DllEnd(dll)));
}


/*------------------------------------------------------------*/
/************************* MULTI FIND *************************/
/*------------------------------------------------------------*/

int DllMultiFind(dll_iter_t from, dll_iter_t to,
                        int (*IsMatch)(const void* list_data, const void* param),
                        const void* param, dll_t* dest_dll)
{	
	int cnt = 0;
	dll_iter_t null_check_iter = 0;
	
	assert(NULL != dest_dll);
	
	null_check_iter = DllBegin(dest_dll);
	
	while (!DllIsIterEqual(from, to))
	{
		from = DllFind(from, to, IsMatch, (void*)param);
		if (!DllIsIterEqual(from, to))
		{
			from = DllGetNext(from);
			++cnt;
			
			null_check_iter = 
			DllInsert(dest_dll, DllEnd(dest_dll), DllGetData(from));
			if (DllIsIterEqual(null_check_iter, DllEnd(dest_dll)))
			{
				return -1;
			}	
		}
	}
	return cnt;
}


/*--------------------------------------------------------*/
/************************* SPLICE *************************/
/*--------------------------------------------------------*/

dll_iter_t DllSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to)
{
	dnode_t* where_n = IterToNode(where);
	dnode_t* from_n = IterToNode(from);
	dnode_t* to_n = IterToNode(to);

	dnode_t* where_prev = IterToNode(DllGetPrev(where));
	dnode_t* from_prev = IterToNode(DllGetPrev(from));
	dnode_t* to_prev = IterToNode(DllGetPrev(to));
	
	LinkNodes(from_prev, to_n);
	LinkNodes(where_prev, from_n);
	LinkNodes(to_prev, where_n);
	
	return where;

}


/*-----------------------------------------------------------------*/
/************************* STATIC FUNCTION *************************/
/*-----------------------------------------------------------------*/

static void LinkNodes(dnode_t* node_1, dnode_t* node_2)
{
	node_1->next = node_2;
	node_2->prev = node_1;
}

static dll_iter_t NodeToIter(dnode_t* dnode)
{
	return (dll_iter_t)dnode;
}

static dnode_t* IterToNode(dll_iter_t iter)
{
	return (dnode_t*)iter;
}

