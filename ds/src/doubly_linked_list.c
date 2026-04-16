/**********************
* doubly linked list
* Author: Tal Frank
* Reviewer: Ori Yoseph
* Last update: 15/04/2026
**********************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/doubly_linked_list.h"

typedef struct Dll_Node dnode_t;


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
	head_dummy->next = tail_dummy;
	tail_dummy->prev = head_dummy;
	tail_dummy->next = NULL;
	head_dummy->data = dll;
	tail_dummy->data = dll;
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
	
	return dll->head->next;
}


dll_iter_t DllEnd(const dll_t* dll)
{
	assert(NULL != dll);
	
	return dll->tail;
}


/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

size_t DllCount(const dll_t* dll)
{
	int cnt = 0;	
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
	return iter->next;
}

dll_iter_t DllGetPrev(dll_iter_t iter)
{
	return iter->prev;
}


/*---------------------------------------------------------------------*/
/************************* IS EQUAL & IS EMPTY *************************/
/*---------------------------------------------------------------------*/

int DllIsIterEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	return iter1 == iter2;
}


int DllIsEmpty(const dll_t* dll)
{
	assert(NULL != dll);

	return DllIsIterEqual(DllBegin(dll), DllEnd(dll));
}




void* DllGetData(dll_iter_t iter)
{
	return iter->data;
}


/*-----------------------------------------------------------------*/
/************************* INSERT & REMOVE *************************/
/*-----------------------------------------------------------------*/

dll_iter_t DllInsert(dll_t* dll, dll_iter_t where, const void* data)
{
	dll_iter_t prev_iter = DllGetPrev(where);

	dnode_t* new_dnode = (dnode_t*)malloc(sizeof(dnode_t));
	if (NULL == new_dnode)
	{
		return DllEnd(dll);
	}
	
	assert(NULL != dll);
	
	new_dnode->data = (void*)data;
	new_dnode->prev = prev_iter;
	new_dnode->next = where;
	
	prev_iter->next = new_dnode;
	where->prev = new_dnode;
	
	return new_dnode;
}


dll_iter_t DllRemove(dll_iter_t iter)
{
	dll_iter_t prev_iter = DllGetPrev(iter);
	dll_iter_t next_iter = DllGetNext(iter);

	assert(NULL != dll);
	
	prev_iter->next = next_iter;
	next_iter->prev = prev_iter;
	
	free(iter);
	return next_iter;
}


/*------------------------------------------------------*/
/************************* FIND *************************/
/*------------------------------------------------------*/

dll_iter_t DllFind(dll_iter_t from, dll_iter_t to, 
		   int (*comp_func)(const void* data, const void* param), const void* param)
{	
	int is_equal = comp_func(from->data, param);

	assert(from != to);

	while (!is_equal && !DllIsIterEqual(to , from))
	{
		from = from->next;
		is_equal = comp_func(from->data, param);
	}
	return from;
}

/*---------------------------------------------------------*/
/************************* FOREACH *************************/
/*---------------------------------------------------------*/

dll_iter_t DllForEach(dll_iter_t from, dll_iter_t to, 
		      int (*action_func)(void* data, void* param), void* param)
{
	int success = 1;
	while (success && !DllIsIterEqual(to , from))
	{
		success = action_func(from->data, param);
		from = from->next;
	}
	return from;
}

/*-----------------------------------------------------------------*/
/************************* PUSH FRONT/BACK *************************/
/*-----------------------------------------------------------------*/

dll_iter_t DllPushFront(dll_t* dll, void* data)
{
	assert(NULL != dll);

	return DllInsert(dll, DllBegin(dll), data);
}


dll_iter_t DllPushBack(dll_t* dll, void* data)
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

	return DllRemove(dll, DllBegin(dll));
}


dll_iter_t DllPopBack(dll_t* dll)
{
	assert(NULL != dll);
	
	return DllRemove(dll, DllGetPrev(DllEnd(dll)));
}


/*------------------------------------------------------------*/
/************************* MULTI FIND *************************/
/*------------------------------------------------------------*/

int DllMultiFind(dll_iter_t from, dll_iter_t to,
                        int (*IsMatch)(const void* list_data, const void* param),
                        const void* param, dll_t* dest_dll)
{	
	int cnt = 0;
	dll_iter_t iter = from;
	dll_iter_t null_check_iter = dest_dll->head;
	
	assert(dest_dll);
	
	while (!DllIsIterEqual(iter, to))
	{
		iter = DllFind(iter, to, IsMatch, (void*)param);
		if (!DllIsIterEqual(iter, to))
		{
			iter = DllGetNext(iter);
			++cnt;
			null_check_iter = 
			DllInsert(dest_dll, DllEnd(dest_dll), iter->data);
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
	dll_iter_t where_prev = DllGetPrev(where);
	dll_iter_t from_prev = DllGetPrev(from);
	dll_iter_t to_prev = DllGetPrev(to);
	
	where_prev->next = from;
	where->prev = to_prev;
	
	from_prev->next = to;
	to->prev = from_prev;
	
	from->prev = where_prev;
	to_prev->next  = where;
	
	return where;
}



