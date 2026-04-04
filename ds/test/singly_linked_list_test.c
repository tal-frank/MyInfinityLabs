
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

#include "../include/singly_linked_list.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"


static int num1 = 1;
static int num2 = 2;
static int num3 = 3;
static int num4 = 4;
static int num5 = 5;
static int num6 = 6;
static int num7 = 7;
static int num8 = 8;
static int num9 = 9;
static int num10 = 10;
static int num11 = 11;

int AddNum(void* data, void* num)
{
	*(int*)data += *(int*)num;
	return 1;
}


int is_equal(void* num1, void* num2)
{
	return *(int*)num1 == *(int*)num2 ? 1 : 0;
}


/*-------------------------------------------------------------*/
/************************* INSERT TEST *************************/
/*-------------------------------------------------------------*/

void InsertTest(void)
{
	int i = 0;
	int check = 0;
	int arr[9] = {6, 1, 7, 2, 3, 8, 9, 4, 5};
	
	sll_t* sll = SllCreate();
	sll_iter_t iter2 = SllBegin(sll);
	sll_iter_t iter1 = 0;
	
	printf("started " CYAN "INSERT BEFORE " RESET_COLOR "test:\n");
	
	iter1 = SllInsertBefore(SllBegin(sll), &num1);
	iter1 = SllInsertBefore(iter1, &num2);
	iter1 = SllInsertBefore(iter1, &num3);
	iter1 = SllInsertBefore(iter1, &num4);
	iter1 = SllInsertBefore(iter1, &num5);
	iter2 = SllInsertBefore(iter2, &num6);
	iter2 = SllGetNext(iter2);
	iter2 = SllInsertBefore(iter2, &num7);	
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllInsertBefore(iter2, &num8);
	iter2 = SllInsertBefore(iter2, &num9);
	
	iter1 = SllBegin(sll);
	while (!SllIterIsEqual(iter1, SllEnd(sll)))
	{
		check = *(int*)SllGetData(iter1);
		if (check != arr[i])
		{
			printf(RED "insert before FAILED\n" RESET_COLOR);
			printf("failure at %d place\n\n", i);
			SllDestroy(sll);
			return;
		}
		iter1 = SllGetNext(iter1);
		++i;
	}
	printf(GREEN "insert before PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*-------------------------------------------------------------*/
/************************* REMOVE TEST *************************/
/*-------------------------------------------------------------*/

void RemoveTest(void)
{
	int i = 0;
	int check = 0;
	int arr[7] = {2, 6, 9, 10, 7, 11, 5};
	
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	
	printf("started " CYAN "REMOVE" RESET_COLOR " test:\n");
	
	iter = SllInsertBefore(SllBegin(sll), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllBegin(sll);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	
	iter = SllRemove(iter);
	
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllBegin(sll);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	
	
	iter = SllRemove(iter);
	
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);
	iter = SllInsertBefore(iter, &num8);
	iter = SllBegin(sll);
	
	iter = SllRemove(iter);
	
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllInsertBefore(iter, &num9);
	iter = SllInsertBefore(iter, &num10);
	iter = SllGetNext(iter);
	
	iter = SllRemove(iter);
	
	iter = SllInsertBefore(iter, &num11);
	iter = SllBegin(sll);
	while (!SllIterIsEqual(iter, SllEnd(sll)))
	{
		check = *(int*)SllGetData(iter);
		if (check != arr[i])
		{
			printf(RED "remove FAILED\n" RESET_COLOR);
			printf("failure at %d place\n\n", i);
			SllDestroy(sll);
			return;
		}
		iter = SllGetNext(iter);
		++i;
	}
	printf(GREEN "remove PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*------------------------------------------------------------*/
/************************* BEGIN TEST *************************/
/*------------------------------------------------------------*/

void BeginTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	
	printf("started " CYAN "BEGIN" RESET_COLOR " test:\n");
	
	iter = SllBegin(sll);
	
	if (!SllIterIsEqual(SllBegin(sll), iter))
	{
		printf(RED "begin FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}

	iter = SllInsertBefore(SllBegin(sll), &num1);	
	iter = SllInsertBefore(iter, &num2);
	
	if (1 == *(int*)SllGetData(iter))
	{
		printf(RED "begin after insert FAILED\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllBegin(sll);
	
	if (1 != *(int*)SllGetData(iter))
	{
		printf(RED "begin FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	printf(GREEN "begin PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*----------------------------------------------------------*/
/************************* END TEST *************************/
/*----------------------------------------------------------*/

void EndTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	
	printf("started " CYAN "END" RESET_COLOR " test:\n");
	
	iter = SllEnd(sll);
	
	if (!SllIterIsEqual(SllEnd(sll), iter))
	{
		printf(RED "End FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}

	iter = SllInsertBefore(SllEnd(sll), &num1);	
	iter = SllInsertBefore(iter, &num2);
	
	if (!SllIterIsEqual(SllEnd(sll), iter))
	{
		printf(RED "end after insert FAILED\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllBegin(sll);
	
	if (SllIterIsEqual(SllEnd(sll), iter))
	{
		printf(RED "end FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllEnd(sll);
	
	if (!SllIterIsEqual(SllEnd(sll), iter))
	{
		printf(RED "end FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	printf(GREEN "End PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*-----------------------------------------------------------*/
/************************* NEXT TEST *************************/
/*-----------------------------------------------------------*/

void NextTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	sll_iter_t iter1 = 0;
	sll_iter_t iter2 = 0;
	sll_iter_t iter3 = 0;
	
	printf("started " CYAN "NEXT" RESET_COLOR "test:\n");
	
	iter1 = SllInsertBefore(SllBegin(sll), &num1);
	iter2 = SllInsertBefore(iter1, &num2);
	iter3 = SllInsertBefore(iter2, &num3);
	
	iter = SllBegin(sll);

	iter = SllGetNext(iter);
	if (!SllIterIsEqual(iter1, iter))
	{
		printf(RED "next FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllGetNext(iter);
	if (!SllIterIsEqual(iter2, iter))
	{
		printf(RED "next FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllGetNext(iter);
	if (!SllIterIsEqual(iter3, iter))
	{
		printf(RED "next FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	printf(GREEN "next PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}	


/*-------------------------------------------------------------*/
/************************* LENGTH TEST *************************/
/*-------------------------------------------------------------*/

void LengthTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	
	printf("started " CYAN "LENGTH" RESET_COLOR " test:\n");
	if (0 != SllGetLength(sll))
	{
		printf(RED "length FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(SllBegin(sll), &num1);
	if (1 != SllGetLength(sll))
	{
		printf(RED "length FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(iter, &num2);
	if (2 != SllGetLength(sll))
	{
		printf(RED "length FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(iter, &num3);
	if (3 != SllGetLength(sll))
	{
		printf(RED "length FAILED 4\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllBegin(sll);
	iter = SllGetNext(iter);
	iter = SllRemove(iter);
	if (2 != SllGetLength(sll))
	{
		printf(RED "length FAILED 5\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	printf(GREEN "length PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*---------------------------------------------------------------*/
/************************* IS EQUAL TEST *************************/
/*---------------------------------------------------------------*/

void IsEqualTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter1 = 0;
	sll_iter_t iter2 = 0;
	
	printf("started " CYAN "IS EQUAL" RESET_COLOR " test:\n");
	
	iter1 = SllBegin(sll);
	iter2 = SllEnd(sll);
	if (!SllIterIsEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter2 = SllInsertBefore(SllBegin(sll), &num1);
	
	if (SllIterIsEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter1 = SllGetNext(iter1);
	if (!SllIterIsEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter1 = SllBegin(sll);
	iter2 = SllBegin(sll);
	if (!SllIterIsEqual(iter1, iter2))
	{
		printf(RED "is equal FAILED 4\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	printf(GREEN "is equal PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*---------------------------------------------------------------*/
/************************* GET DATA TEST *************************/
/*---------------------------------------------------------------*/

void GetDataTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = SllBegin(sll);
	int check = 0;
	int num = 0;
	int i = 0;
	
	printf("started " CYAN "GET DATA" RESET_COLOR " test:\n");
		
	while (!SllIterIsEqual(iter, SllEnd(sll)))
	{
		num = num1 << i;
		iter = SllInsertBefore(iter, &(num));
		check = *(int*)SllGetData(iter);
		if (check != num1 << i)
		{
			printf(RED "get data FAILED\n\n" RESET_COLOR);
			SllDestroy(sll);
			return;
		}
		++i;
	}
	printf(GREEN "get data PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*---------------------------------------------------------------*/
/************************* SET DATA TEST *************************/
/*---------------------------------------------------------------*/

void SetDataTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = SllBegin(sll);
	int check = 0;
	int num = 0;
	int i = 0;
	
	printf("started " CYAN "SET DATA" RESET_COLOR " test:\n");

	iter = SllInsertBefore(SllBegin(sll), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	
	iter = SllBegin(sll);	
	while (!SllIterIsEqual(iter, SllEnd(sll)))
	{
		num = num1 << i;
		SllSetData(iter, &(num));
		check = *(int*)SllGetData(iter);
		if (check != num1 << i)
		{
			printf(RED "set data FAILED\n\n" RESET_COLOR);
			SllDestroy(sll);
			return;
		}
		
		iter = SllGetNext(iter);
		++i;
	}
	printf(GREEN "set data PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*---------------------------------------------------------------*/
/************************* IS EMPTY TEST *************************/
/*---------------------------------------------------------------*/

void IsEmptyTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	
	printf("started " CYAN "IS EMPTY" RESET_COLOR " test:\n");
	if (!IsEmpty(sll))
	{
		printf(RED "is empty FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllInsertBefore(SllBegin(sll), &num1);
	if (IsEmpty(sll))
	{
		printf(RED "is empty FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllBegin(sll);
	iter = SllRemove(iter);
	if (!IsEmpty(sll))
	{
		printf(RED "is empty FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	printf(GREEN "is empty PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*-----------------------------------------------------------*/
/************************* FIND TEST *************************/
/*-----------------------------------------------------------*/

void FindTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;

	printf("started " CYAN "FIND" RESET_COLOR " test:\n");
	
	iter = SllInsertBefore(SllBegin(sll), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);	
	iter = SllInsertBefore(iter, &num8);
	iter = SllInsertBefore(iter, &num9);
	
	iter = SllFind(SllBegin(sll), SllEnd(sll), is_equal, &num4);
	if (4 != *(int*)SllGetData(iter))
	{
		printf(RED "find FAILED 1\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllFind(iter, SllEnd(sll), is_equal, &num6);
	if (6 != *(int*)SllGetData(iter))
	{
		printf(RED "find FAILED 2\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllFind(iter, SllEnd(sll), is_equal, &num4);
	if (!SllIterIsEqual(iter, SllEnd(sll)))
	{
		printf(RED "find FAILED 3\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	
	iter = SllBegin(sll);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllFind(SllBegin(sll), iter, is_equal, &num9);
	if (6 != *(int*)SllGetData(iter))
	{
		printf(RED "find FAILED 4\n\n" RESET_COLOR);
		SllDestroy(sll);
		return;
	}
	printf(GREEN "find PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*---------------------------------------------------------------*/
/************************* FOR EACH TEST *************************/
/*---------------------------------------------------------------*/

void ForEachTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter1 = 0;
	sll_iter_t iter2 = 0;
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
	
	iter1 = SllInsertBefore(SllBegin(sll), &number1);
	iter1 = SllInsertBefore(iter1, &number2);
	iter1 = SllInsertBefore(iter1, &number3);
	iter1 = SllInsertBefore(iter1, &number4);
	iter1 = SllInsertBefore(iter1, &number5);
	iter1 = SllInsertBefore(iter1, &number6);
	iter1 = SllInsertBefore(iter1, &number7);	
	iter1 = SllInsertBefore(iter1, &number8);
	iter1 = SllInsertBefore(iter1, &number9);
	iter1 = SllBegin(sll);
	
	iter1 = SllForEach(SllBegin(sll), SllEnd(sll), AddNum, &num1);
	iter1 = SllBegin(sll);
	
	check = 2;
	
	while(!SllIterIsEqual(iter1, SllEnd(sll)))
	{
		if ((check) != *(int*)SllGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			SllDestroy(sll);
			return;
		}
		iter1 = SllGetNext(iter1);
		++check;
	}
	
	iter1 = SllBegin(sll);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);

	iter2 = SllBegin(sll);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	
	SllForEach(iter1, iter2, AddNum, &num1);
	check = 5;
	
	
	while(!SllIterIsEqual(iter1, iter2))
	{
		if ((check) != *(int*)SllGetData(iter1))
		{
			printf(RED "for each FAILED1\n\n" RESET_COLOR);
			SllDestroy(sll);
			return;
		}
		iter1 = SllGetNext(iter1);
		++check;
	}
	
	
	printf(GREEN "for each PASSED\n\n" RESET_COLOR);
	SllDestroy(sll);
}


/*-----------------------------------------------------------*/
/************************* FLIP TEST *************************/
/*-----------------------------------------------------------*/

void FlipTest(void)
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = 0;
	sll_iter_t iter_begin = SllBegin(sll);
	sll_iter_t iter_destroy = 0;
	sll_iter_t iter_destroy2 = 0;
	int check = 9;
	
	printf("started " CYAN "FLIP" RESET_COLOR " test:\n");
	
	iter = SllInsertBefore(SllBegin(sll), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);	
	iter = SllInsertBefore(iter, &num8);
	iter = SllInsertBefore(iter, &num9);
	iter = SllBegin(sll);
	
	iter = Flip(iter);
	free(sll);
	
	while(!SllIterIsEqual(iter, iter_begin))
	{
		if ((check) != *(int*)SllGetData(iter))
		{
			printf(RED "flip FAILED\n\n" RESET_COLOR);
			return;
		}
		iter_destroy = iter;
		iter = SllGetNext(iter);
		free(iter_destroy);
		--check;
	}
	
	printf(GREEN "flip PASSED\n\n" RESET_COLOR);
	iter_destroy = iter;
	free(iter_destroy);
}


/*--------------------------------------------------------------*/
/************************* HAS LOOP TEST*************************/
/*--------------------------------------------------------------*/

void LoopTest(void)
{
	sll_t* sll1 = SllCreate();
	sll_t* sll2 = SllCreate();
	sll_iter_t iter = 0;
	sll_iter_t iter_next = 0;
	sll_iter_t iter_dummy = 0;
	int has_loop = 0;
	
	printf("started " CYAN "LOOP" RESET_COLOR " test:\n");
	
	iter = SllInsertBefore(SllBegin(sll1), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);	
	iter = SllInsertBefore(iter, &num8);
	iter = SllInsertBefore(iter, &num9);
	iter = SllBegin(sll1);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	
	iter_dummy = SllGetNext(iter);
	
	iter_next = SllBegin(sll1);
	iter_next = SllGetNext(iter_next);
	iter_next = SllGetNext(iter_next);
	iter_next = SllGetNext(iter_next);
	iter_next = SllGetNext(iter_next);

	SllSetAddr(iter, iter_next);
	
	iter = SllBegin(sll1);
	
	has_loop = HasLoop(iter);
	
	if (!has_loop)
	{
		printf(RED "has loop FAILED1\n\n" RESET_COLOR);
		SllDestroy(sll1);
		SllDestroy(sll2);
		return;
	}
	
	iter = SllBegin(sll1);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	iter = SllGetNext(iter);
	
	SllSetAddr(iter, iter_dummy);
	
	SllDestroy(sll1);
	
	iter = SllInsertBefore(SllBegin(sll2), &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);	
	iter = SllInsertBefore(iter, &num8);
	iter = SllInsertBefore(iter, &num9);
	
	iter = SllBegin(sll2);
	
	has_loop = HasLoop(iter);
	
	if (has_loop)
	{
		printf(RED "has loop FAILED2\n\n" RESET_COLOR);
		SllDestroy(sll1);
		SllDestroy(sll2);
		return;
	}
	
	printf(GREEN "loop PASSED\n\n" RESET_COLOR);
	
	SllDestroy(sll2);
}


/*------------------------------------------------------------------------*/
/************************* FIND INTERSECTION TEST *************************/
/*------------------------------------------------------------------------*/

void IntersectionTest(void)
{
	sll_t* sll1 = SllCreate();
	sll_t* sll2 = SllCreate();
	sll_iter_t iter1 = 0;
	sll_iter_t iter2 = 0;
	sll_iter_t iter_test = 0;
	
	printf("started " CYAN "FIND INTERSECTION" RESET_COLOR " test:\n");
	
	iter1 = SllBegin(sll1);
	iter2 = SllBegin(sll2);
	
	iter1 = SllInsertBefore(SllBegin(sll1), &num1);
	iter1 = SllInsertBefore(iter1, &num2);
	iter1 = SllInsertBefore(iter1, &num3);
	iter1 = SllInsertBefore(iter1, &num4);
	iter1 = SllInsertBefore(iter1, &num5);
	iter1 = SllInsertBefore(iter1, &num6);
	iter1 = SllInsertBefore(iter1, &num7);	
	iter1 = SllInsertBefore(iter1, &num8);
	iter1 = SllInsertBefore(iter1, &num9);
	
	iter1 = SllBegin(sll1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	
	iter2 = SllInsertBefore(SllBegin(sll2), &num1);
	iter2 = SllInsertBefore(iter2, &num2);
	iter2 = SllInsertBefore(iter2, &num3);
	SllSetAddr(iter2, iter1);
	
	iter_test = FindIntersection(iter1, iter2);
	
	if (6 != *(int*)SllGetData(iter_test))
	{
		printf(RED "find intersection FAILED1\n\n" RESET_COLOR);
		SllDestroy(sll1);
		SllDestroy(sll2);
		return;
	}
	
	iter_test = FindIntersection(iter2, iter1);
	
	if (6 != *(int*)SllGetData(iter_test))
	{
		printf(RED "find intersection FAILED2\n\n" RESET_COLOR);
		SllDestroy(sll1);
		SllDestroy(sll2);
		return;
	}
	
	printf(GREEN "find intersection PASSED\n\n" RESET_COLOR);
	
	SllDestroy(sll1);
	SllDestroy(sll2);
}


/*------------------------------------------------------*/
/************************* MAIN *************************/
/*------------------------------------------------------*/

int main()
{
	printf("\n");
	
	BeginTest();
	EndTest();
	IsEqualTest();
	NextTest();
	InsertTest();
	RemoveTest();
	IsEmptyTest();
	LengthTest();
	GetDataTest();
	SetDataTest();
	FindTest();
	FlipTest();
	LoopTest();
	IntersectionTest();
	ForEachTest();
	
	return 0;
}
