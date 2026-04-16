
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "../include/doubly_linked_list.h"

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


struct Dll_Node
{
	dnode_t* next;
	dnode_t* prev;
	void* data;
};

static int num1 = 1;
static int num2 = 2;
static int num3 = 3;
static int num4 = 4;
static int num5 = 5;
static int num6 = 6;
static int num7 = 7;
static int num8 = 8;
static int num9 = 9;


int AddNum(void* data, void* num)
{
	*(int*)data += *(int*)num;
	return 0;
}

int is_equal(const void* num1, const void* num2)
{
	return *(int*)num1 == *(int*)num2 ? 0 : 1;
}


/*--------------------------------------------------------*/
/************************* CREATE *************************/
/*--------------------------------------------------------*/

void CreateDestroyTest(void)
{
	dll_t* dll = DllCreate();
	
	printf("started " CYAN "CREATE" RESET_COLOR " test:\n");
	
	if (NULL == dll)
	{
		printf(RED " create FAILED/destroy 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	if (NULL != dll->tail->next 	 ||
	    NULL != dll->head->prev 	 ||
	    dll->head->next != dll->tail ||
	    dll->head != dll->tail->prev)
	{
		printf(RED " create/destroy FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "create/destroy PASSED\n\n" RESET_COLOR);
}


/*--------------------------------------------------------*/
/************************* INSERT *************************/
/*--------------------------------------------------------*/

void InsertTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = dll->tail;
	
	printf("started " CYAN "INSERT" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	
	if (5 != *(int*)dll->head->next->data ||
	    4 != *(int*)dll->head->next->next->data ||
	    3 != *(int*)dll->head->next->next->next->data ||
	    2 != *(int*)dll->head->next->next->next->next->data ||
	    1 != *(int*)dll->head->next->next->next->next->next->data)
	{
		printf(RED " insert FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllInsert(dll, iter->next->next, &num6);
	iter = DllInsert(dll, iter->next->next, &num7);
	iter = DllInsert(dll, iter->next->next->next, &num8);
	
	if (5 != *(int*)dll->head->next->data ||
	    4 != *(int*)dll->head->next->next->data ||
	    6 != *(int*)dll->head->next->next->next->data ||
	    3 != *(int*)dll->head->next->next->next->next->data ||
	    7 != *(int*)dll->head->next->next->next->next->next->data ||
	    2 != *(int*)dll->head->next->next->next->next->next->next->data ||
	    1 != *(int*)dll->head->next->next->next->next->next->next->next->data ||
	    8 != *(int*)dll->head->next->next->next->next->next->next->next->next->data)
	{
		printf(RED " insert FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "insert PASSED\n\n" RESET_COLOR);
}

/*----------------------------------------------------------*/
/************************* GET DATA *************************/
/*----------------------------------------------------------*/


void GetDataTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = dll->tail;
	int i = 0;
	
	printf("started " CYAN "GET DATA" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);

	for (i = 5; i > 0; --i)
	{
		if (i != *(int*)DllGetData(iter))
		{
			printf(RED " get data FAILED %d\n\n" RESET_COLOR, i);
			DllDestroy(dll);
			return;
		}
		iter = iter->next;
	}
	
	DllDestroy(dll);
	printf(GREEN "get data PASSED\n\n" RESET_COLOR);
}


/*-------------------------------------------------------*/
/************************* BEGIN *************************/
/*-------------------------------------------------------*/

void BeginTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = dll->tail;
	
	printf("started " CYAN "BEGIN" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	
	iter = iter->next->next;
	iter = DllBegin(dll);
	if (dll->head->next != iter)
	{
		printf(RED " begin FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = iter->next->next->next->next->next;
	iter = DllBegin(dll);
	if (dll->head->next != iter)
	{
		printf(RED " begin FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "begin PASSED\n\n" RESET_COLOR);
}


/*-----------------------------------------------------*/
/************************* END *************************/
/*-----------------------------------------------------*/

void EndTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "END" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);

	iter = DllEnd(dll);
	if (dll->tail != iter)
	{
		printf(RED " end FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = iter->prev->prev;
	iter = DllEnd(dll);
	if (dll->tail != iter)
	{
		printf(RED " end FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "end PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* GET NEXT *************************/
/*----------------------------------------------------------*/

void GetNextTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "GET NEXT" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	
	while(iter != DllEnd(dll))
	{
		if (iter->next != DllGetNext(iter))
		{
			printf(RED " get next FAILED\n\n" RESET_COLOR);
			DllDestroy(dll);
			return;
		}
		iter = iter->next;
	} 
	
	DllDestroy(dll);
	printf(GREEN "get next PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* GET PREV *************************/
/*----------------------------------------------------------*/

void GetPrevTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "GET PREV" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	
	iter = DllEnd(dll);
	while(iter != DllBegin(dll))
	{
		if (iter->prev != DllGetPrev(iter))
		{
			printf(RED " get prev FAILED\n\n" RESET_COLOR);
			DllDestroy(dll);
			return;
		}
		iter = iter->prev;
	} 
	
	DllDestroy(dll);
	printf(GREEN "get prev PASSED\n\n" RESET_COLOR);
}


/*--------------------------------------------------------*/
/************************* REMOVE *************************/
/*--------------------------------------------------------*/

void RemoveTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "REMOVE" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	iter = DllInsert(dll, iter, &num6);
	iter = DllInsert(dll, iter, &num7);
	iter = DllInsert(dll, iter, &num8);

	iter = DllRemove(iter);

	if (7 != *(int*)DllGetData(DllBegin(dll)))
	{
		printf(RED " remove FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllRemove(iter);

	if (3 != *(int*)DllGetData(iter))
	{
		printf(RED " remove FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllRemove(iter);

	if (2 != *(int*)DllGetData(DllGetPrev(iter)))
	{
		printf(RED " remove FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "remove PASSED\n\n" RESET_COLOR);
}


/*------------------------------------------------------*/
/************************* PUSH *************************/
/*------------------------------------------------------*/

void PushFrontBackTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "PUSH FRONT/BACK" RESET_COLOR " test:\n");
	
	DllPushBack(dll, &num5);
	iter = DllEnd(dll);
	if (5 != *(int*)DllGetData(DllGetPrev(iter)))
	{
		printf(RED " push back FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllRemove(DllGetPrev(iter));	
	DllPushFront(dll, &num6);
	iter = DllBegin(dll);
	if (6 != *(int*)DllGetData(iter))
	{
		printf(RED " push front FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);	

	DllPushBack(dll, &num4);	
	iter = DllEnd(dll);
	
	if (4 != *(int*)DllGetData(DllGetPrev(iter)))
	{
		printf(RED " push back FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllPushFront(dll, &num7);
	iter = DllBegin(dll);
	if (7 != *(int*)DllGetData(iter))
	{
		printf(RED " push front FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "push front/back PASSED\n\n" RESET_COLOR);
}


/*-----------------------------------------------------*/
/************************* POP *************************/
/*-----------------------------------------------------*/

void PopFrontBackTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "POP FRONT/BACK" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	iter = DllInsert(dll, iter, &num6);
	iter = DllInsert(dll, iter, &num7);
	iter = DllInsert(dll, iter, &num8);
	
	DllPopBack(dll);
	iter = DllEnd(dll);
	if (2 != *(int*)DllGetData(DllGetPrev(iter)))
	{
		printf(RED " pop back FAILED\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllPopFront(dll);
	iter = DllBegin(dll);
	if (7 != *(int*)DllGetData(iter))
	{
		printf(RED " pop back FAILED\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "pop front/back PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* IS_EMPTY *************************/
/*----------------------------------------------------------*/

void IsEmptyTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "IS EMPTY" RESET_COLOR " test:\n");
	
	if (!DllIsEmpty(dll))
	{
		printf(RED " is empty FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllInsert(dll, iter, &num1);	
	if (DllIsEmpty(dll))
	{
		printf(RED " is empty FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllRemove(iter);
	if (!DllIsEmpty(dll))
	{
		printf(RED " is empty FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	DllDestroy(dll);
	printf(GREEN "is empty PASSED\n\n" RESET_COLOR);
}


/*----------------------------------------------------------*/
/************************* IS EQUAL *************************/
/*----------------------------------------------------------*/

void IsEqualTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter1 = 0;
	dll_iter_t iter2 = 0;
	
	printf("started " CYAN "IS EQUAL" RESET_COLOR " test:\n");
	
	iter1 = DllBegin(dll);
	iter2 = DllEnd(dll);
	if (!DllIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter2 = DllInsert(dll, DllBegin(dll), &num1);
	iter1 = DllBegin(dll);
	iter2 = DllGetNext(iter2);
	if (DllIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter1 = DllGetNext(iter1);
	if (!DllIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter1 = DllBegin(dll);
	iter2 = DllBegin(dll);
	if (!DllIsIterEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 4\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	printf(GREEN "is equal PASSED\n\n" RESET_COLOR);
	DllDestroy(dll);
}


/*-------------------------------------------------------*/
/************************* COUNT *************************/
/*-------------------------------------------------------*/

void CountTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = DllBegin(dll);
	
	printf("started " CYAN "COUNT" RESET_COLOR " test:\n");
	
	if (0 != DllCount(dll))
	{
		printf(RED "count FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllInsert(dll, iter, &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	
	if (4 != DllCount(dll))
	{
		printf(RED "count FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}

	iter = DllRemove(iter);
	iter = DllRemove(iter);

	if (2 != DllCount(dll))
	{
		printf(RED "count FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	printf(GREEN "count PASSED\n\n" RESET_COLOR);
	DllDestroy(dll);
}


/*------------------------------------------------------*/
/************************* FIND *************************/
/*------------------------------------------------------*/

void FindTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter = 0;

	printf("started " CYAN "FIND" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, DllBegin(dll), &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);
	iter = DllInsert(dll, iter, &num6);
	iter = DllInsert(dll, iter, &num7);	
	iter = DllInsert(dll, iter, &num8);
	iter = DllInsert(dll, iter, &num9);
	
	iter = DllFind(DllBegin(dll), DllEnd(dll), is_equal, &num6);
	if (6 != *(int*)DllGetData(iter))
	{
		printf(RED "find FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllFind(iter, DllEnd(dll), is_equal, &num4);
	if (4 != *(int*)DllGetData(iter))
	{
		printf(RED "find FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllBegin(dll);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllFind(iter, DllEnd(dll), is_equal, &num7);
	if (!DllIsIterEqual(iter, DllEnd(dll)))
	{
		printf(RED "find FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	iter = DllBegin(dll);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	iter = DllFind(DllBegin(dll), iter, is_equal, &num7);
	if (7 != *(int*)DllGetData(iter))
	{
		printf(RED "find FAILED 4\n\n" RESET_COLOR);
		DllDestroy(dll);
		return;
	}
	
	printf(GREEN "find PASSED\n\n" RESET_COLOR);
	DllDestroy(dll);
}


/*------------------------------------------------------------*/
/************************* MULTI FIND *************************/
/*------------------------------------------------------------*/

void MultiFind(void)
{
	dll_t* dll = DllCreate();
	dll_t* dll_found = DllCreate();
	dll_iter_t iter = 0;
	int cnt = 0;

	printf("started " CYAN "MULTI FIND" RESET_COLOR " test:\n");
	
	iter = DllInsert(dll, DllBegin(dll), &num1);
	iter = DllInsert(dll, iter, &num2);
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);	
	iter = DllInsert(dll, iter, &num8);
	iter = DllInsert(dll, iter, &num9);
	
	iter = DllInsert(dll, iter, &num3);
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num5);	
	iter = DllInsert(dll, iter, &num8);
	
	iter = DllInsert(dll, iter, &num4);
	iter = DllInsert(dll, iter, &num8);
	
	cnt = DllMultiFind(DllBegin(dll), DllEnd(dll), is_equal, &num4, dll_found);
	if (3 != cnt || 3 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	cnt = DllMultiFind(DllBegin(dll), DllEnd(dll), is_equal, &num3, dll_found);
	if (2 != cnt || 5 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	iter = DllBegin(dll);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);
	cnt = DllMultiFind(iter, DllEnd(dll), is_equal, &num4, dll_found);
	if (2 != cnt || 7 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 3\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	cnt = DllMultiFind(DllBegin(dll), DllEnd(dll), is_equal, &num6, dll_found);
	if (0 != cnt || 7 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 4\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	iter = DllBegin(dll);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);	
	cnt = DllMultiFind(DllBegin(dll), iter, is_equal, &num4, dll_found);
	if (1 != cnt || 8 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 5\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	iter = DllBegin(dll);
	iter = DllGetNext(iter);
	iter = DllGetNext(iter);	
	cnt = DllMultiFind(DllBegin(dll), iter, is_equal, &num3, dll_found);
	if (0 != cnt || 8 != DllCount(dll_found))
	{
		printf(RED "multi find FAILED 6\n\n" RESET_COLOR);
		DllDestroy(dll);
		DllDestroy(dll_found);
		return;
	}
	
	printf(GREEN "multi find PASSED\n\n" RESET_COLOR);
	DllDestroy(dll);
	DllDestroy(dll_found);
}


/*----------------------------------------------------------*/
/************************* FOR EACH *************************/
/*----------------------------------------------------------*/

void ForEachTest(void)
{
	dll_t* dll = DllCreate();
	dll_iter_t iter1 = 0;
	dll_iter_t iter2 = 0;
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
	
	iter1 = DllInsert(dll, DllBegin(dll), &number9);
	iter1 = DllInsert(dll, iter1, &number8);
	iter1 = DllInsert(dll, iter1, &number7);
	iter1 = DllInsert(dll, iter1, &number6);
	iter1 = DllInsert(dll, iter1, &number5);
	iter1 = DllInsert(dll, iter1, &number4);
	iter1 = DllInsert(dll, iter1, &number3);	
	iter1 = DllInsert(dll, iter1, &number2);
	iter1 = DllInsert(dll, iter1, &number1);
	iter1 = DllBegin(dll);
	
	iter1 = DllForEach(DllBegin(dll), DllEnd(dll), AddNum, &num1);
	iter1 = DllBegin(dll);
	
	check = 2;
	
	while(!DllIsIterEqual(iter1, DllEnd(dll)))
	{
		if ((check) != *(int*)DllGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			DllDestroy(dll);
			return;
		}
		iter1 = DllGetNext(iter1);
		++check;
	}
	
	iter1 = DllBegin(dll);
	iter1 = DllGetNext(iter1);
	iter1 = DllGetNext(iter1);

	iter2 = DllBegin(dll);
	iter2 = DllGetNext(iter2);
	iter2 = DllGetNext(iter2);
	iter2 = DllGetNext(iter2);
	iter2 = DllGetNext(iter2);
	iter2 = DllGetNext(iter2);
	iter2 = DllGetNext(iter2);
	
	DllForEach(iter1, iter2, AddNum, &num1);
	check = 5;
	
	
	while(!DllIsIterEqual(iter1, iter2))
	{
		if ((check) != *(int*)DllGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			DllDestroy(dll);
			return;
		}
		iter1 = DllGetNext(iter1);
		++check;
	}
	
	printf(GREEN "for each PASSED\n\n" RESET_COLOR);
	DllDestroy(dll);
}


/*--------------------------------------------------------*/
/************************* SPLICE *************************/
/*--------------------------------------------------------*/

void SpliceTest()
{
	dll_t* dll_1 = DllCreate();
	dll_t* dll_2 = DllCreate();
	dll_iter_t iter_1 = 0;
	dll_iter_t iter_2 = 0;
	dll_iter_t iter_2_to = 0;

	printf("started " CYAN "SPLICE" RESET_COLOR " test:\n");
	
	iter_1 = DllInsert(dll_1, DllBegin(dll_1), &num1);
	iter_1 = DllInsert(dll_1, iter_1, &num2);
	iter_1 = DllInsert(dll_1, iter_1, &num3);
	iter_1 = DllInsert(dll_1, iter_1, &num4);
	iter_1 = DllInsert(dll_1, iter_1, &num5);	
	iter_1 = DllInsert(dll_1, iter_1, &num6);
	iter_1 = DllInsert(dll_1, iter_1, &num7);
	
	iter_2 = DllInsert(dll_2, DllBegin(dll_2), &num1);
	iter_2 = DllInsert(dll_2, iter_2, &num2);
	iter_2 = DllInsert(dll_2, iter_2, &num3);
	iter_2 = DllInsert(dll_2, iter_2, &num4);
	iter_2 = DllInsert(dll_2, iter_2, &num5);	
	iter_2 = DllInsert(dll_2, iter_2, &num6);
	iter_2 = DllInsert(dll_2, iter_2, &num7);
	
	iter_2 = DllGetNext(iter_2);
	iter_2 = DllGetNext(iter_2);
	iter_2 = DllGetNext(iter_2);
	
	DllSplice(iter_2, DllBegin(dll_1), DllEnd(dll_1));
	iter_2 = DllBegin(dll_2);
	if (0 != DllCount(dll_1) || 14 != DllCount(dll_2)         ||
	    *(int*)iter_2->next->data != 6 			  ||
	    *(int*)iter_2->next->next->data != 5 		  ||
	    *(int*)iter_2->next->next->next->data != 7		  ||
	    *(int*)iter_2->next->next->next->next->data != 6)
	{
		printf(RED "splice FAILED 1\n\n" RESET_COLOR);
		DllDestroy(dll_2);
		DllDestroy(dll_1);
		return;
	}
	
	iter_1 = DllBegin(dll_1);
	
	iter_2 = DllBegin(dll_2);
	iter_2 = DllGetNext(iter_2);
	iter_2 = DllGetNext(iter_2);
	
	iter_2_to = DllBegin(dll_2);
	iter_2_to = DllGetNext(iter_2_to);
	iter_2_to = DllGetNext(iter_2_to);
	iter_2_to = DllGetNext(iter_2_to);
	iter_2_to = DllGetNext(iter_2_to);
	iter_2_to = DllGetNext(iter_2_to);
	iter_2_to = DllGetNext(iter_2_to);
	
	DllSplice(iter_1, iter_2, iter_2_to);
	iter_1 = DllBegin(dll_1);
	if (4 != DllCount(dll_1) || 10 != DllCount(dll_2)         ||
	    *(int*)iter_1->data != 5 				  ||
	    *(int*)iter_1->next->data != 7 			  ||
	    *(int*)iter_1->next->next->data != 6 		  ||
	    *(int*)iter_1->next->next->next->data != 5)
	{
		printf(RED "splice FAILED 2\n\n" RESET_COLOR);
		DllDestroy(dll_2);
		DllDestroy(dll_1);
		return;
	}
	
	printf(GREEN "splice PASSED\n\n" RESET_COLOR);
	DllDestroy(dll_1);
	DllDestroy(dll_2);
}


/*------------------------------------------------------*/
/************************* MAIN *************************/
/*------------------------------------------------------*/

int main()
{
	printf("\n");
	
	CreateDestroyTest();
	InsertTest();
	GetDataTest();
	BeginTest();
	EndTest();
	GetNextTest();
	GetPrevTest();
	RemoveTest();
	PushFrontBackTest();
	PopFrontBackTest();
	IsEmptyTest();
	IsEqualTest();
	CountTest();
	FindTest();
	ForEachTest();
	MultiFind();
	SpliceTest();
	
	return 0;
}


