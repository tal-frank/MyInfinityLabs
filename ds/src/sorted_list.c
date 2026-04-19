/**********************
* sorted list
* Author: Tal Frank
* Reviewer: 
* Last update: 17/04/2026
**********************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/doubly_linked_list.h"
#include "../include/sorted_list.h"

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLERATIONS *************************/
/*-------------------------------------------------------------------------------*/

static dll_iter_t SIterToDIter(sorted_list_iter_t iter);

#ifndef NDEBUG
static sorted_list_t* ListID(sorted_list_iter_t iter);
#endif /*NDEBUG*/

/*---------------------------------------------------------*/
/************************* STRUCTS *************************/
/*---------------------------------------------------------*/

struct Sorted_list
{
	dll_t* dll;
	int (*cmp_func)(const void* param1, const void* param2);
};


/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

sorted_list_t* SortedListCreate(int (*cmp_func)(const void* param1, const void* param2))
{
	sorted_list_t* sorted_list = (sorted_list_t*)malloc(sizeof(sorted_list_t));
	if (NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->dll = DllCreate();
	if (NULL == sorted_list->dll)
	{
		free(sorted_list);
		sorted_list = NULL;
		return NULL;
	}
	
	sorted_list->cmp_func = cmp_func;
	
	return sorted_list; 
}


void SortedListDestroy(sorted_list_t* sl)
{
	DllDestroy(sl->dll);
	sl->dll = NULL;
	free(sl);
	sl = NULL;
}


/*-------------------------------------------------------------*/
/************************* BEGIN & END *************************/
/*-------------------------------------------------------------*/

sorted_list_iter_t SortedListBegin(const sorted_list_t* sl)
{
	sorted_list_iter_t iter = {0};
	
	assert(NULL != sl);	
	
	iter.inner_iter = DllBegin(sl->dll);
	#ifndef NDEBUG
	    	iter.list = (sorted_list_t*)sl;
	#endif /*NDEBUG*/
	return iter;
}


sorted_list_iter_t SortedListEnd(const sorted_list_t* sl)
{
	sorted_list_iter_t iter = {0};
	
	assert(NULL != sl);
	
	iter.inner_iter = DllEnd(sl->dll);
	#ifndef NDEBUG
	    	iter.list = (sorted_list_t*)sl;
	#endif /*NDEBUG*/
	return iter;
}


/*---------------------------------------------------------------------*/
/************************* IS EQUAL & IS EMPTY *************************/
/*---------------------------------------------------------------------*/

int SortedListIsEmpty(const sorted_list_t* sorted_list)
{
	assert(NULL != sorted_list);
	
	return DllIsEmpty(sorted_list->dll);
}


int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return (DllIsIterEqual(SIterToDIter(iter1), SIterToDIter(iter2)) 
		#ifndef NDEBUG 
			 && ListID(iter1) == ListID(iter2)
		#endif /*NDEBUG*/
		);
}


/*--------------------------------------------------------------------------------*/
/************************* GET NEXT & GET PREV & GET DATA *************************/
/*--------------------------------------------------------------------------------*/

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	iter.inner_iter = DllGetNext(SIterToDIter(iter));
	
	return iter;
}


sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	iter.inner_iter = DllGetPrev(SIterToDIter(iter));
	
	return iter;
}


void* SortedListGetData(sorted_list_iter_t iter)
{
	return DllGetData(SIterToDIter(iter));
}


/*----------------------------------------------------------------*/
/************************* POP FRONT/BACK *************************/
/*----------------------------------------------------------------*/

void* SortedListPopBack(sorted_list_t* sl)
{
	void* data = 0;
	
	assert(NULL != sl);
	
	data = SortedListGetData(SortedListPrev(SortedListEnd(sl)));
	DllPopBack(sl->dll);
	
	return data;
}


void* SortedListPopFront(sorted_list_t* sl)
{
	void* data = 0;
	
	assert(NULL != sl);
	
	data = SortedListGetData(SortedListBegin(sl));
	DllPopFront(sl->dll);
	
	return data;
}


/*-----------------------------------------------------------------*/
/************************* INSERT & REMOVE *************************/
/*-----------------------------------------------------------------*/

sorted_list_iter_t SortedListInsert(sorted_list_t* sl, const void* data)
{
	sorted_list_iter_t iter = {0};
	sorted_list_iter_t end_of_list = {0};
	
	assert(NULL != sl);
	
	iter = SortedListBegin(sl);
	end_of_list = SortedListEnd(sl);
	while (!SortedListIsIterEqual(end_of_list, iter) && 
	       0 > sl->cmp_func(SortedListGetData(iter), data))
	{
		iter = SortedListNext(iter);
	}
	
	iter.inner_iter = DllInsert(sl->dll, SIterToDIter(iter), data);
	#ifndef NDEBUG 
		 iter.list = sl;
	#endif /*NDEBUG*/
	return iter;
}


sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{	
	iter.inner_iter = DllRemove(SIterToDIter(iter));
	return iter;
}


/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

size_t SortedListSize(const sorted_list_t* sorted_list)
{
	return DllCount(sorted_list->dll);
}


/*----------------------------------------------------------------*/
/************************* FIND FUNCTIONS *************************/
/*----------------------------------------------------------------*/

sorted_list_iter_t SortedListFind(const sorted_list_t* sl,
                                sorted_list_iter_t from,
                                sorted_list_iter_t to,
                                const void* param)
{
	int compare = sl->cmp_func(SortedListGetData(from), param);

	assert(NULL != sl);

	while (0 > compare && !SortedListIsIterEqual(to , from))
	{
		from = SortedListNext(from);
		compare = sl->cmp_func(SortedListGetData(from), param);
	}
	return (0 == compare) ? from : to;
}


sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*is_match_func)(const void* param1, const void* param2),
                                    const void* param)
{
	sorted_list_iter_t iter = {0};
	iter.inner_iter = DllFind(SIterToDIter(from), SIterToDIter(to), is_match_func, param);
	return iter;
}

/*---------------------------------------------------------*/
/************************* FOREACH *************************/
/*---------------------------------------------------------*/

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*action_func)(void* data, void* param),
                                    void* param)
{
	sorted_list_iter_t iter = {0};
	iter.inner_iter = DllForEach(SIterToDIter(from), SIterToDIter(to), action_func, param);
	return iter;
}


/*-------------------------------------------------------*/
/************************* MERGE *************************/
/*-------------------------------------------------------*/

void SortedListMerge(sorted_list_t* dest, sorted_list_t* src)
{
	sorted_list_iter_t iter_dest = SortedListBegin(dest);
	sorted_list_iter_t iter_src_runner = SortedListBegin(src);
	sorted_list_iter_t iter_src_cur = SortedListBegin(src);
	sorted_list_iter_t dest_end = SortedListEnd(dest);
	sorted_list_iter_t src_end = SortedListEnd(src);
	
	assert(NULL != dest);
	assert(NULL != src);
	
	while (!SortedListIsIterEqual(iter_src_runner, src_end))
	{
		while (!SortedListIsIterEqual(iter_dest, dest_end)           &&
		       0 <= dest->cmp_func(SortedListGetData(iter_src_cur), 
					   SortedListGetData(iter_dest)))
		{
			iter_dest = SortedListNext(iter_dest);
		}
		if (SortedListIsIterEqual(iter_dest, dest_end))
		{
			iter_src_runner = src_end;
		}
		else
		{
			while (!SortedListIsIterEqual(iter_src_runner, src_end)      &&
			       0 > dest->cmp_func(SortedListGetData(iter_src_runner), 
						  SortedListGetData(iter_dest)))
			{
				iter_src_runner = SortedListNext(iter_src_runner);
			}
		}
		
		DllSplice(SIterToDIter(iter_dest), SIterToDIter(iter_src_cur), 
						   SIterToDIter(iter_src_runner));
		
		iter_src_cur = iter_src_runner;
	}
}


/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/


static dll_iter_t SIterToDIter(sorted_list_iter_t iter)
{
	return iter.inner_iter;
}

#ifndef NDEBUG
static sorted_list_t* ListID(sorted_list_iter_t iter)
{
	return iter.list;
}
#endif /*NDEBUG*/
