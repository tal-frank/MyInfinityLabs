#include<stdio.h> /* printf */

#include "../include/sorted_list.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

typedef struct Dll_Node dnode_t;

struct Doubly_linked_list
{
	dnode_t* head;
	dnode_t* tail;
};

struct Sorted_list
{
	dll_t* dll;
	int (*cmp_func)(const void* param1, const void* param2);
};

struct Dll_Node
{
	dnode_t* next;
	dnode_t* prev;
	void* data;
};

typedef struct building
{
	size_t height;
	size_t space;
}build_t;


static int num1 = 1;
static int num2 = 2;
static int num3 = 3;
static int num4 = 4;
static int num5 = 5;
static int num6 = 6;
static int num7 = 7;
static int num8 = 8;
static int num9 = 9;


int cmp_func(const void* num1, const void* num2)
{
	return *(int*)num1 - *(int*)num2;
}

int AddNum(void* data, void* num)
{
	*(int*)data += *(int*)num;
	return 0;
}

int BuildingHeightComp(const void* building1, const void* building2)
{
	build_t building1_t = *(build_t*)building1;
	build_t building2_t = *(build_t*)building2;
	
	return (int)(building1_t.height - building2_t.height);
}

int BuildingSpaceComp(const void* building1, const void* building2)
{
	build_t building1_t = *(build_t*)building1;
	build_t building2_t = *(build_t*)building2;
	return !(0 == (building1_t.space - building2_t.space));
}

/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

void CreatTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	
	printf("started " CYAN "CREATE" RESET_COLOR " test:\n");
	
	if (NULL == sl)
	{
		printf(RED " create FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	if (NULL != sl->dll->tail->next 	 ||
	    NULL != sl->dll->head->prev 	 ||
	    sl->dll->head->next != sl->dll->tail ||
	    sl->dll->head != sl->dll->tail->prev ||
	    sl->cmp_func != cmp_func)
	{
		printf(RED " create/destroy FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "create/destroy PASSED\n\n" RESET_COLOR);
}


/*--------------------------------------------------------*/
/************************* INSERT *************************/
/*--------------------------------------------------------*/

void InsertTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	
	printf("started " CYAN "INSERT" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num5);
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num3);
	
	if (1 != *(int*)sl->dll->head->next->data ||
	    2 != *(int*)sl->dll->head->next->next->data ||
	    3 != *(int*)sl->dll->head->next->next->next->data ||
	    4 != *(int*)sl->dll->head->next->next->next->next->data ||
	    5 != *(int*)sl->dll->head->next->next->next->next->next->data)
	{
		printf(RED " insert FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListInsert(sl, &num8);
	SortedListInsert(sl, &num7);
	SortedListInsert(sl, &num5);
	
	if (1 != *(int*)sl->dll->head->next->data ||
	    2 != *(int*)sl->dll->head->next->next->data ||
	    3 != *(int*)sl->dll->head->next->next->next->data ||
	    4 != *(int*)sl->dll->head->next->next->next->next->data ||
	    5 != *(int*)sl->dll->head->next->next->next->next->next->data ||
	    5 != *(int*)sl->dll->head->next->next->next->next->next->next->data ||
	    7 != *(int*)sl->dll->head->next->next->next->next->next->next->next->data ||
	    8 != *(int*)sl->dll->head->next->next->next->next->next->next->next->next->data)
	{
		printf(RED " insert FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "insert PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* GET DATA *************************/
/*----------------------------------------------------------*/

void GetDataTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = {0};
	int i = 0;
	
	printf("started " CYAN "GET DATA" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num5);
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num3);

	iter.inner_iter = sl->dll->head->next;
	for (i = 1; i <= 5; ++i)
	{
		if (i != *(int*)SortedListGetData(iter))
		{
			printf(RED " get data FAILED %d\n\n" RESET_COLOR, i);
			SortedListDestroy(sl);
			return;
		}
		iter.inner_iter = iter.inner_iter->next;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "get data PASSED\n\n" RESET_COLOR);
}


/*-------------------------------------------------------*/
/************************* BEGIN *************************/
/*-------------------------------------------------------*/

void BeginTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = {0};
	iter.inner_iter = sl->dll->tail;
	
	printf("started " CYAN "BEGIN" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num5);
	
	iter.inner_iter = sl->dll->head->next->next->next;
	iter = SortedListBegin(sl);
	if (sl->dll->head->next != iter.inner_iter
	#ifndef NDEBUG
	    	 || iter.list != sl
	#endif /*NDEBUG*/ 
	    )
	{
		printf(RED " begin FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter.inner_iter = iter.inner_iter->next->next->next->next->next;
	iter = SortedListBegin(sl);
	if (sl->dll->head->next != iter.inner_iter
	#ifndef NDEBUG
	    	 || iter.list != sl
	#endif /*NDEBUG*/
	)
	{
		printf(RED " begin FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "begin PASSED\n\n" RESET_COLOR);
}


/*-----------------------------------------------------*/
/************************* END *************************/
/*-----------------------------------------------------*/

void EndTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = {0};
	iter = SortedListBegin(sl);
	
	printf("started " CYAN "END" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num5);
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num4);

	iter = SortedListBegin(sl);
	iter = SortedListEnd(sl);
	if (sl->dll->tail != iter.inner_iter
	#ifndef NDEBUG
	    	 || iter.list != sl
	#endif /*NDEBUG*/
	)
	{
		printf(RED "end FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter.inner_iter = iter.inner_iter->prev->prev->prev;
	iter = SortedListEnd(sl);
	if (sl->dll->tail != iter.inner_iter
	#ifndef NDEBUG
	    	 || iter.list != sl
	#endif /*NDEBUG*/
	)
	{
		printf(RED "end FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "end PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* GET NEXT *************************/
/*----------------------------------------------------------*/

void GetNextTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = SortedListBegin(sl);
	
	printf("started " CYAN "GET NEXT" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num5);
	SortedListInsert(sl, &num4);
	
	while(iter.inner_iter != SortedListEnd(sl).inner_iter)
	{
		if (iter.inner_iter->next != SortedListNext(iter).inner_iter
		#ifndef NDEBUG
	    		 || iter.list != sl
		#endif /*NDEBUG*/
		)
		{
			printf(RED " get next FAILED\n\n" RESET_COLOR);
			SortedListDestroy(sl);
			return;
		}
		iter.inner_iter = iter.inner_iter->next;
	} 
	
	SortedListDestroy(sl);
	printf(GREEN "get next PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* GET PREV *************************/
/*----------------------------------------------------------*/

void GetPrevTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = SortedListBegin(sl);
	
	printf("started " CYAN "GET PREV" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num5);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num1);
	
	iter = SortedListEnd(sl);
	while(iter.inner_iter != SortedListBegin(sl).inner_iter)
	{
		if (iter.inner_iter->prev != SortedListPrev(iter).inner_iter
		#ifndef NDEBUG
	    		 || iter.list != sl
		#endif /*NDEBUG*/
		)
		{
			printf(RED " get prev FAILED\n\n" RESET_COLOR);
			SortedListDestroy(sl);
			return;
		}
		iter.inner_iter = iter.inner_iter->prev;
	} 
	
	SortedListDestroy(sl);
	printf(GREEN "get prev PASSED\n\n" RESET_COLOR);
}


/*--------------------------------------------------------*/
/************************* REMOVE *************************/
/*--------------------------------------------------------*/

void RemoveTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = {0};
	
	printf("started " CYAN "REMOVE" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num6);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num9);
	SortedListInsert(sl, &num7);
	SortedListInsert(sl, &num6);
	
	iter = SortedListBegin(sl);
	iter = SortedListRemove(iter);

	if (3 != *(int*)SortedListGetData(SortedListBegin(sl)))
	{
		printf(RED " remove FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}

	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	iter = SortedListRemove(iter);

	if (6 != *(int*)SortedListGetData(iter))
	{
		printf(RED " remove FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	iter = SortedListRemove(iter);

	if (7 != *(int*)SortedListGetData(SortedListPrev(iter)))
	{
		printf(RED " remove FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "remove PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* IS_EMPTY *************************/
/*----------------------------------------------------------*/

void IsEmptyTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = SortedListBegin(sl);
	
	printf("started " CYAN "IS EMPTY" RESET_COLOR " test:\n");
	
	if (!SortedListIsEmpty(sl))
	{
		printf(RED " is empty FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter = SortedListInsert(sl, &num1);	
	if (SortedListIsEmpty(sl))
	{
		printf(RED " is empty FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListRemove(iter);
	if (!SortedListIsEmpty(sl))
	{
		printf(RED " is empty FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "is empty PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* IS EQUAL *************************/
/*----------------------------------------------------------*/

void IsEqualTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter1 = {0};
	sorted_list_iter_t iter2 = {0};
	
	printf("started " CYAN "IS EQUAL" RESET_COLOR " test:\n");
	
	iter1 = SortedListBegin(sl);
	iter2 = SortedListEnd(sl);
	if (!SortedListIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter2 = SortedListInsert(sl, &num1);
	iter1 = SortedListBegin(sl);
	iter2 = SortedListNext(iter2);
	if (SortedListIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListNext(iter1);
	if (!SortedListIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListBegin(sl);
	iter2 = SortedListBegin(sl);
	if (!SortedListIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 4\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	printf(GREEN "is equal PASSED\n\n" RESET_COLOR);
	SortedListDestroy(sl);
}


/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

void CountTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = SortedListBegin(sl);
	
	printf("started " CYAN "COUNT" RESET_COLOR " test:\n");
	
	if (0 != SortedListSize(sl))
	{
		printf(RED "count FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter = SortedListInsert(sl, &num3);
	iter = SortedListInsert(sl, &num2);
	iter = SortedListInsert(sl, &num2);
	iter = SortedListInsert(sl, &num2);
	
	if (4 != SortedListSize(sl))
	{
		printf(RED "count FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}

	iter = SortedListRemove(iter);
	iter = SortedListRemove(iter);

	if (2 != SortedListSize(sl))
	{
		printf(RED "count FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	printf(GREEN "count PASSED\n\n" RESET_COLOR);
	SortedListDestroy(sl);
}


/*------------------------------------------------------*/
/************************* FIND *************************/
/*------------------------------------------------------*/

void FindTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter1 = {0};
	sorted_list_iter_t iter2 = {0};

	printf("started " CYAN "FIND" RESET_COLOR " test:\n");
	
	iter1 = SortedListInsert(sl, &num1);
	iter1 = SortedListInsert(sl, &num2);
	iter1 = SortedListInsert(sl, &num9);
	iter1 = SortedListInsert(sl, &num8);
	iter1 = SortedListInsert(sl, &num5);
	iter1 = SortedListInsert(sl, &num6);
	iter1 = SortedListInsert(sl, &num5);	
	iter1 = SortedListInsert(sl, &num4);
	iter1 = SortedListInsert(sl, &num9);
	
	iter1 = SortedListFind(sl, SortedListBegin(sl), SortedListEnd(sl), &num4);
	if (4 != *(int*)SortedListGetData(iter1))
	{
		printf(RED "find FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListFind(sl, iter1, SortedListEnd(sl), &num6);
	if (6 != *(int*)SortedListGetData(iter1))
	{
		printf(RED "find FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListBegin(sl);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListFind(sl, iter1, SortedListEnd(sl), &num7);
	if (!SortedListIsIterEqual(iter1, SortedListEnd(sl)))
	{
		printf(RED "find FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListBegin(sl);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter2 = SortedListFind(sl, SortedListBegin(sl), iter1, &num8);
	if (!SortedListIsIterEqual(iter1, iter2))
	{
		printf(RED "find FAILED 4\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListBegin(sl);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);
	iter2 = SortedListFind(sl, SortedListBegin(sl), iter1, &num2);
	if (2 != *(int*)SortedListGetData(iter2))
	{
		printf(RED "find FAILED 4\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	printf(GREEN "find PASSED\n\n" RESET_COLOR);
	SortedListDestroy(sl);
}


/*----------------------------------------------------------*/
/************************* FOR EACH *************************/
/*----------------------------------------------------------*/

void ForEachTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	sorted_list_iter_t iter1 = {0};
	sorted_list_iter_t iter2 = {0};
	int check = 0;
	int number1 = 1;
	int number2 = 2;
	int number3 = 3;
	int number4 = 4;
	int number5 = 5;
	int number6 = 6;
	int number7 = 7;
	int number8 = 8;
	int number9 = 9;
	
	printf("started " CYAN "FOR EACH" RESET_COLOR " test:\n");
	
	iter1 = SortedListInsert(sl, &number9);
	iter1 = SortedListInsert(sl, &number8);
	iter1 = SortedListInsert(sl, &number7);
	iter1 = SortedListInsert(sl, &number6);
	iter1 = SortedListInsert(sl, &number5);
	iter1 = SortedListInsert(sl, &number4);
	iter1 = SortedListInsert(sl, &number3);	
	iter1 = SortedListInsert(sl, &number2);
	iter1 = SortedListInsert(sl, &number1);
	iter1 = SortedListBegin(sl);
	
	iter1 = SortedListForEach(SortedListBegin(sl), SortedListEnd(sl), AddNum, &num1);
	iter1 = SortedListBegin(sl);
	
	check = 2;
	
	while(!SortedListIsIterEqual(iter1, SortedListEnd(sl)))
	{
		if ((check) != *(int*)SortedListGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			SortedListDestroy(sl);
			return;
		}
		iter1 = SortedListNext(iter1);
		++check;
	}
	
	iter1 = SortedListBegin(sl);
	iter1 = SortedListNext(iter1);
	iter1 = SortedListNext(iter1);

	iter2 = SortedListBegin(sl);
	iter2 = SortedListNext(iter2);
	iter2 = SortedListNext(iter2);
	iter2 = SortedListNext(iter2);
	iter2 = SortedListNext(iter2);
	iter2 = SortedListNext(iter2);
	iter2 = SortedListNext(iter2);
	
	SortedListForEach(iter1, iter2, AddNum, &num1);
	check = 5;
	
	
	while(!SortedListIsIterEqual(iter1, iter2))
	{
		if ((check) != *(int*)SortedListGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			SortedListDestroy(sl);
			return;
		}
		iter1 = SortedListNext(iter1);
		++check;
	}
	
	printf(GREEN "for each PASSED\n\n" RESET_COLOR);
	SortedListDestroy(sl);
}


/*-------------------------------------------------------*/
/************************* MERGE *************************/
/*-------------------------------------------------------*/

void MergeTest(void)
{
	sorted_list_t* sl1 = SortedListCreate(cmp_func);
	sorted_list_t* sl2 = SortedListCreate(cmp_func);
	sorted_list_iter_t iter = SortedListBegin(sl1);
	
	printf("started " CYAN "Merge" RESET_COLOR " test:\n");
	
	SortedListInsert(sl1, &num1);
	SortedListInsert(sl1, &num2);
	SortedListInsert(sl1, &num9);
	SortedListInsert(sl1, &num8);
	SortedListInsert(sl1, &num5);
	SortedListInsert(sl1, &num6);
	SortedListInsert(sl1, &num5);	
	SortedListInsert(sl1, &num4);
	SortedListInsert(sl1, &num9);
		
	SortedListInsert(sl2, &num4);
	SortedListInsert(sl2, &num2);
	SortedListInsert(sl2, &num3);
	SortedListInsert(sl2, &num6);
	SortedListInsert(sl2, &num3);
	SortedListInsert(sl2, &num9);
	SortedListInsert(sl2, &num7);
	SortedListInsert(sl2, &num6);
	
	SortedListMerge(sl1, sl2);
	
	if (17 != SortedListSize(sl1) || 0 != SortedListSize(sl2))
	{
		printf(RED "merge FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl1);
		SortedListDestroy(sl2);
		return;
	}
	
	iter = SortedListBegin(sl1);
	iter = SortedListNext(iter);
	while (!SortedListIsIterEqual(iter, SortedListEnd(sl1)))
	{
		if (*(int*)SortedListGetData(iter) <
		    *(int*)SortedListGetData(SortedListPrev(iter)))
		{
			printf(RED "merge FAILED 2\n\n" RESET_COLOR);
			SortedListDestroy(sl1);
			SortedListDestroy(sl2);
			return;
		}
		iter = SortedListNext(iter);
	}
	
	SortedListMerge(sl1, sl2);
	
	if (17 != SortedListSize(sl1) || 0 != SortedListSize(sl2))
	{
		printf(RED "merge FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl1);
		SortedListDestroy(sl2);
		return;
	}
	
	SortedListMerge(sl2, sl1);
	
	if (0 != SortedListSize(sl1) || 17 != SortedListSize(sl2))
	{
		printf(RED "merge FAILED 3\n\n" RESET_COLOR);
		SortedListDestroy(sl1);
		SortedListDestroy(sl2);
		return;
	}
	
	printf(GREEN "merge PASSED\n\n" RESET_COLOR);
	SortedListDestroy(sl1);
	SortedListDestroy(sl2);
}


/*-----------------------------------------------------*/
/************************* POP *************************/
/*-----------------------------------------------------*/

void PopFrontBackTest(void)
{
	sorted_list_t* sl = SortedListCreate(cmp_func);
	
	printf("started " CYAN "POP FRONT/BACK" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &num2);
	SortedListInsert(sl, &num6);
	SortedListInsert(sl, &num8);
	SortedListInsert(sl, &num3);
	SortedListInsert(sl, &num7);
	SortedListInsert(sl, &num1);
	SortedListInsert(sl, &num4);
	SortedListInsert(sl, &num5);
	
	if (8 != *(int*)SortedListPopBack(sl) ||
	    7 != *(int*)SortedListGetData(SortedListPrev(SortedListEnd(sl))))
	{
		printf(RED " pop back FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	if (1 != *(int*)SortedListPopFront(sl) ||
	    2 != *(int*)SortedListGetData(SortedListBegin(sl)))
	{
		printf(RED "pop back FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "pop front/back PASSED\n\n" RESET_COLOR);
}


/*---------------------------------------------------------*/
/************************* FIND IF *************************/
/*---------------------------------------------------------*/

void FindIfTest(void)
{
	sorted_list_t* sl = SortedListCreate(BuildingHeightComp);
	sorted_list_iter_t iter1 = {0};
	
	build_t data = {0};	
	build_t build1 = {4, 7};
	build_t build2 = {5, 2};
	build_t build3 = {7, 3};
	build_t build4 = {1, 5};
	build_t build5 = {2, 9};
	build_t build6 = {5, 6};
	build_t build7 = {3, 8};
	build_t build8 = {8, 4};

	printf("started " CYAN "FIND IF" RESET_COLOR " test:\n");
	
	SortedListInsert(sl, &build1);
	SortedListInsert(sl, &build2);
	SortedListInsert(sl, &build3);
	SortedListInsert(sl, &build4);
	SortedListInsert(sl, &build5);
	SortedListInsert(sl, &build6);
	SortedListInsert(sl, &build7);
	SortedListInsert(sl, &build8);
	
	iter1 = SortedListFind(sl, SortedListBegin(sl), SortedListEnd(sl), &build4);
	data = *(build_t*)SortedListGetData(iter1);
	if (1 != data.height)
	{
		printf(RED "find if FAILED 1\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	iter1 = SortedListFindIf(SortedListBegin(sl), SortedListEnd(sl), 
		BuildingSpaceComp, &build7);
	data = *(build_t*)SortedListGetData(iter1);
	if (8 != data.space)
	{
		printf(RED "find if FAILED 2\n\n" RESET_COLOR);
		SortedListDestroy(sl);
		return;
	}
	
	SortedListDestroy(sl);
	printf(GREEN "find if PASSED\n\n" RESET_COLOR);
}


/*------------------------------------------------------*/
/************************* MAIN *************************/
/*------------------------------------------------------*/

int main()
{
	printf("\n");
	
	CreatTest();
	InsertTest();
	GetDataTest();
	BeginTest();
	EndTest();
	GetNextTest();
	GetPrevTest();
	RemoveTest();
	IsEmptyTest();
	IsEqualTest();
	CountTest();
	FindTest();
	ForEachTest();
	PopFrontBackTest();
	MergeTest();
	FindIfTest();
	return 0;
}


