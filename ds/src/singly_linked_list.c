/**********************
* singly linked list
* Author: Tal Frank
* Reviewer: Matan Shaked
* Last update: 05/04/2026
**********************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /*assert*/

#include "../include/singly_linked_list.h"

#define UNUSED(x) ((void)x)

typedef struct Node node_t;

/*------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATION *************************/
/*------------------------------------------------------------------------------*/

static node_t* IterToNode(sll_iter_t iter);
static sll_iter_t NodeToIter(node_t* node);
static void LinkNodes(node_t* node_1, node_t* node_2);

/*-------------------------------------------------------------*/
/************************* SLL STRUCTS *************************/
/*-------------------------------------------------------------*/

struct Node
{
	node_t* next;
	void* data;
};


struct Single_linked_list
{
	node_t* head;
	node_t* tail;
};


/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

int CountForEach(void* data, void* cnt)
{
	UNUSED(data);
	*(int*)cnt += 1;
	return 0;
}


/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

sll_t* SllCreate(void)
{
	sll_t* sll = (sll_t*)malloc(sizeof(sll_t));
	node_t* dummy = (node_t*)malloc(sizeof(node_t));
	if (NULL == sll)
	{
		printf("can't creat struct\n");
		return NULL;
	}
	
	if (NULL == dummy)
	{
		printf("can't creat struct\n");
		free(sll);
		return NULL;
	}
	
	dummy->next = NULL;
	dummy->data = sll;
	sll->head = dummy;
	sll->tail = dummy;
	
	return sll;
}


void SllDestroy(sll_t* sll)
{
	node_t* freed = SllBegin(sll);
	node_t* iter = SllBegin(sll);
	
	while (!SllIterIsEqual(SllEnd(sll), iter))
	{
		iter = iter->next;
		free(freed);
		freed = iter;
	}
	free(sll->tail);
	free(sll);
}


/*------------------------------------------------------------------------*/
/************************* BEGIN & END & GET NEXT *************************/
/*------------------------------------------------------------------------*/

sll_iter_t SllBegin(const sll_t* sll)
{
	assert(NULL != sll);	
	
	return NodeToIter(sll->head);
}


sll_iter_t SllEnd(const sll_t* sll)
{
	assert(NULL != sll);

	return NodeToIter(sll->tail);
}


sll_iter_t SllGetNext(sll_iter_t iter)
{
	node_t* node = IterToNode(iter);
	
	assert(NULL != node);
	
	node = node->next;
	return NodeToIter(node);
}


/*---------------------------------------------------------------------*/
/************************* IS EQUAL & IS EMPTY *************************/
/*---------------------------------------------------------------------*/

int SllIsEmpty(const sll_t* sll)
{
	assert(NULL != sll);
	
	return SllIterIsEqual(SllEnd(sll), SllBegin(sll));
}


int SllIterIsEqual(sll_iter_t iter1, sll_iter_t iter2)
{	
	return IterToNode(iter1) == IterToNode(iter2);
}


/*--------------------------------------------------------*/
/************************* LENGTH *************************/
/*--------------------------------------------------------*/

size_t SllGetLength(const sll_t* sll)
{
	size_t cnt = 0;
	node_t* cnt_iter = SllBegin(sll);
	node_t* end = SllEnd(sll);
	
	assert(NULL != sll);
	
	while(!SllIterIsEqual(cnt_iter, end))
	{
		cnt_iter = SllGetNext(cnt_iter);
		++cnt;
	}
	return cnt;
}


size_t SllCount(sll_iter_t from, sll_iter_t to)
{
	size_t cnt = 0;
	SllForEach(from, to, CountForEach, &cnt);
	return cnt;
}

/*-----------------------------------------------------------------*/
/************************* INSERT & REMOVE *************************/
/*-----------------------------------------------------------------*/

sll_iter_t SllInsertBefore(sll_iter_t where, const void* data)
{
	node_t* insert = (node_t*)malloc(sizeof(node_t));
	node_t* where_n = IterToNode(where);
	
	if (NULL == insert)
	{
		printf("can't creat struct\n");
		return NULL;
	}
			
	insert->data = where_n->data;
	insert->next = where_n->next;
	
	where->data = (void*)data;
	LinkNodes(where_n, insert);

	if(NULL == insert->next)
	{
		((sll_t*)insert->data)->tail = insert;
	}
	
	return NodeToIter(insert);
}


sll_iter_t SllRemove(sll_iter_t iter)
{
	node_t* temp = SllGetNext(IterToNode(iter));
	node_t* node = IterToNode(iter);
	
	node->data = SllGetData(SllGetNext(node));
	LinkNodes(node, SllGetNext(SllGetNext(node)));

	if(NULL == iter->next)
	{
		((sll_t*)iter->data)->tail = iter;
	}
	
	free(temp);
	
	return iter;
}


/*---------------------------------------------------------------*/
/************************* GET & SET DATA*************************/
/*---------------------------------------------------------------*/

void* SllGetData(sll_iter_t iter)
{
	node_t* node = IterToNode(iter);
	return NodeToIter(node)->data;
}


void SllSetData(sll_iter_t iter, const void* data)
{		
	node_t* node = IterToNode(iter);
	node->data = (void*)data;
}


/*------------------------------------------------------*/
/************************* FIND *************************/
/*------------------------------------------------------*/

sll_iter_t SllFind(sll_iter_t from, sll_iter_t to, 
		   int (*is_match_func)(void* data, void* param), void* param)
{	
	int is_equal = is_match_func(SllGetData(from), param);

	assert(from != to);

	while (!is_equal && !SllIterIsEqual(to, from))
	{
		from = SllGetNext(from);
		is_equal = is_match_func(SllGetData(from), param);
	}
	return from;
}


/*----------------------------------------------------------*/
/************************* FOR EACH *************************/
/*----------------------------------------------------------*/

sll_iter_t SllForEach(sll_iter_t from, sll_iter_t to, 
		      int (*action_func)(void* data, void* param), void* param)
{
	int failure = 0;
	while (!SllIterIsEqual(to , from) && !failure)
	{
		failure = action_func(from->data, param);
		from = SllGetNext(from);
	}
	return from;
}


/*-----------------------------------------------------------*/
/************************* FLIP LIST *************************/
/*-----------------------------------------------------------*/

sll_iter_t Flip(sll_iter_t head)
{
	node_t* prev_node = head;
	node_t* cur_node = head;
	node_t* next_node = head;
	
	assert(NULL != head);
	assert(NULL != head->next);
	
	cur_node = SllGetNext(cur_node);
	next_node = SllGetNext(next_node);
	next_node = SllGetNext(next_node);
	
	prev_node->next = NULL;
	
	while (NULL != next_node->next)
	{
		cur_node->next = prev_node;
		prev_node = cur_node;
		cur_node = next_node;
		next_node = SllGetNext(next_node);
	}
	free(cur_node->next);
	cur_node->next = prev_node;
	
	
	return cur_node;
}


/*----------------------------------------------------------*/
/************************* HAS LOOP *************************/
/*----------------------------------------------------------*/

void SllSetAddr(sll_iter_t iter, sll_iter_t iter_next)
{
	assert(NULL != iter);	
	
	iter->next = iter_next;
}


int HasLoop(const sll_iter_t head)
{
	node_t* one_step = head;
	node_t* two_steps = head;

	assert(NULL != head);
	assert(NULL != head->next);

	do
	{
		if ((NULL == two_steps->next) || (NULL == two_steps->next->next))
		{
			return 0;
		}
		one_step = SllGetNext(one_step);
		two_steps = SllGetNext(two_steps);
		two_steps = SllGetNext(two_steps);
	} while (!SllIterIsEqual(one_step, two_steps));
	
	return 1;
}


/*-------------------------------------------------------------------*/
/************************* FIND INTERSECTION *************************/
/*-------------------------------------------------------------------*/

static size_t GetLength(const sll_iter_t iter)
{
	size_t cnt = 0;
	node_t* cnt_iter = iter;
	
	assert(NULL != cnt_iter);
	
	while(NULL != cnt_iter)
	{
		cnt_iter = cnt_iter->next;
		++cnt;
	}
	return cnt;
}


sll_iter_t FindIntersection(sll_iter_t head1, sll_iter_t head2)
{
	node_t* iter1 = head1;
	node_t* iter2 = head2;
	size_t len1 = 0;
	size_t len2 = 0;
	int difference = 0;
	int i = 0;
	
	assert(NULL != head1);
	assert(NULL != head2);

	len1 = GetLength(iter1);
	len2 = GetLength(iter2);
		
	difference = (long)(len1 - len2);    
	for (i = 0; i < difference; ++i)
	{
		head1 = SllGetNext(head1);
	}

	difference = (long)(len2 - len1);
	for (i = 0; i < difference; ++i)
	{
		head2 = SllGetNext(head2);
	}
	
	while (NULL != head1)
	{
		if (SllIterIsEqual(head1, head2))
		{
			return head1;
		}
		head1 = SllGetNext(head1);
		head2 = SllGetNext(head2);
	}
	
	return head1;
}


/*--------------------------------------------------------*/
/************************* APPEND *************************/
/*--------------------------------------------------------*/

void SllAppend(sll_t* dest, sll_t* src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	if (SllIsEmpty(src))
	{
		return;
	}
	
	SllSetData(SllEnd(dest), SllGetData(SllBegin(src)));
	SllSetAddr(SllEnd(dest), SllGetNext(SllBegin(src)));
	
	SllSetData(SllEnd(src), dest);
	dest->tail = src->tail;

	SllSetData(SllBegin(src), src);
	SllSetAddr(SllBegin(src), NULL);
	src->tail = src->head;
}


