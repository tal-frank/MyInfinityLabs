
#include <stdio.h>

#include "../ds/include/singly_linked_list.h"

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

sll_iter_t NthElementFromEnd(sll_t* sll, int n)
{
	sll_iter_t front = SllBegin(sll);
	sll_iter_t back = SllBegin(sll);
	sll_iter_t end = SllEnd(sll);
	
	while (n > 0)
	{
		front = SllGetNext(front);
		--n;
	}
	while(!SllIterIsEqual(front, end))
	{
		front = SllGetNext(front);
		back = SllGetNext(back);
	}
	return back;
}


int main()
{
	sll_t* sll = SllCreate();
	sll_iter_t iter = SllBegin(sll);
	
	iter = SllInsertBefore(iter, &num1);
	iter = SllInsertBefore(iter, &num2);
	iter = SllInsertBefore(iter, &num3);
	iter = SllInsertBefore(iter, &num4);
	iter = SllInsertBefore(iter, &num5);
	iter = SllInsertBefore(iter, &num6);
	iter = SllInsertBefore(iter, &num7);
	iter = SllInsertBefore(iter, &num8);
	iter = SllInsertBefore(iter, &num9);
	iter = SllInsertBefore(iter, &num10);
	
	iter = NthElementFromEnd(sll, 6);
	
	printf("the 6th element from the end is: %d\n", *(int*)SllGetData(iter));
	
	return 0;
}


