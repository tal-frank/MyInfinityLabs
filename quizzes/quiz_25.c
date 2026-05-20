#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "../ds/src/singly_linked_list.c"
#include "singly_linked_list.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

#define HAS_LOOP (1)

size_t SllGetLength2(const sll_t* sll)
{
	size_t cnt = 0;
	node_t* cnt_iter = SllBegin(sll);
	
	assert(NULL != sll);
	
	while(NULL != cnt_iter)
	{
		cnt_iter = SllGetNext(cnt_iter);
		++cnt;
	}
	return cnt;
}

int HasLoop2(const sll_t* sll)
{
	sll_iter_t slow = 0;
	sll_iter_t fast = 0;
	
	assert(NULL != sll);
	assert(NULL != SllGetNext(SllBegin(sll)));
	
	slow = SllBegin(sll);
	fast = SllGetNext(slow);
	do
	{
		
		if (NULL == fast || NULL == SllGetNext(fast))
		{
			return !HAS_LOOP;
		}
		slow = SllGetNext(slow);
		fast = SllGetNext(SllGetNext(fast));
	} while (!SllIterIsEqual(slow, fast));
	return HAS_LOOP;
}

void OpenLoop(sll_t* sll)
{
	sll_iter_t slow = 0;
	sll_iter_t fast = 0;
	sll_iter_t prev = 0;
	
	assert(NULL != sll);
	assert(NULL != SllGetNext(SllBegin(sll)));
	
	if (!HasLoop2(sll))
	{
		return;
	}
	
	slow = SllBegin(sll);
	fast = SllBegin(sll);
	do 
	{
		slow = SllGetNext(slow);
		fast = SllGetNext(SllGetNext(fast));
	} while (!SllIterIsEqual(slow, fast));
	slow = SllBegin(sll);
	while (!SllIterIsEqual(slow, fast))
	{
		prev = fast;
		slow = SllGetNext(slow);
		fast = SllGetNext(fast);
	}
	SllSetAddr(prev, NULL);
}


void OpenLoop2(const sll_t* sll)
{
	sll_iter_t slow = 0;
	sll_iter_t fast = 0;
	size_t cnt = 0;
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != sll);
	assert(NULL != SllGetNext(SllBegin(sll)));
	
	slow = SllBegin(sll);
	fast = SllGetNext(slow);
	do
	{	
		if (NULL == fast || NULL == SllGetNext(fast))
		{
			return;
		}
		slow = SllGetNext(slow);
		fast = SllGetNext(SllGetNext(fast));
		++cnt;
	} while (!SllIterIsEqual(slow, fast));

	slow = SllBegin(sll);
	fast = SllGetNext(slow);
	
	for (i = 0; i < cnt; ++i)
	{
		slow = SllGetNext(slow);
		fast = SllGetNext(slow);
		for (j = 0; j < 2 * cnt; ++j)
		{
			if (SllIterIsEqual(fast->next, slow->next))
			{
				SllSetAddr(fast, NULL);
				return;
			}
			fast = SllGetNext(fast);
		}
	}	
}

int main()
{
	sll_t* sll1 = SllCreate();
	sll_t* sll2 = SllCreate();
	sll_iter_t iter1 = 0;
	sll_iter_t iter2 = 0;
	void* data = (void*)1;
	
	printf("\n");
	
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	SllInsertBefore(SllBegin(sll1), data);
	
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	SllInsertBefore(SllBegin(sll2), data);
	
	iter1 = SllBegin(sll1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	iter1 = SllGetNext(iter1);
	
	iter2 = SllBegin(sll1);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	iter2 = SllGetNext(iter2);
	SllSetAddr(iter1, iter2);
	
	
	if (!HasLoop2(sll1))
	{
		printf(RED "---FAILURE---\n" RESET_COLOR);
		printf("didnt find the loop\n\n");
	}
	else
	{
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		printf("found the loop\n\n");
	}
	
	if (HasLoop2(sll2))
	{
		printf(RED "---FAILURE---\n" RESET_COLOR);
		printf("found a loop when there is none\n\n");
	}
	else
	{	
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		printf("didnt find a loop when there is none\n\n");
	}
	
	OpenLoop2(sll1);
	
	if (HasLoop2(sll1))
	{
		printf(RED "---FAILURE---\n" RESET_COLOR);
		printf("didn't open the loop\n\n");
	}
	else
	{
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		printf("opened the loop\n\n");
	}
	
	if (9 != SllGetLength2(sll1))
	{
		printf(RED "---FAILURE---\n" RESET_COLOR);
		printf("count is : %ld\n", SllGetLength2(sll1));
		printf("didn't open the loop in the right place\n\n");
	}
	else
	{
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		printf("opened the loop in the right place\n\n");
	}
	
	SllDestroy(sll1);
	SllDestroy(sll2);
	return 0;
}


