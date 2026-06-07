#include <stdio.h> /* printf */

#include "priority_queue.h"

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

typedef struct building
{
	size_t height;
	size_t space;
}build_t;

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

int cmp_func(const void* num1, const void* num2)
{
	return *(int*)num1 - *(int*)num2;
}

void EraseTest()
{
	pq_t* pq = PQCreate(BuildingHeightComp);
	build_t build1 = {4, 7};
	build_t build2 = {5, 2};
	build_t build3 = {7, 3};
	build_t build4 = {1, 5};
	build_t build5 = {2, 6};
	build_t build6 = {5, 6};
	build_t build7 = {3, 8};
	build_t build8 = {8, 4};
	
	PQEnqueue(pq, &build1);
	PQEnqueue(pq, &build2);
	PQEnqueue(pq, &build3);
	PQEnqueue(pq, &build4);
	PQEnqueue(pq, &build5);
	PQEnqueue(pq, &build6);
	PQEnqueue(pq, &build7);
	PQEnqueue(pq, &build8);
	
	PQErase(pq, BuildingSpaceComp, &build6);
	printf(CYAN "ERASE" RESET_COLOR " TEST\n");
	if (7 != PQSize(pq))
	{
		printf("did not erase \n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	PQDequeue(pq);
	if (2 == *(int*)PQPeek(pq))
	{
		printf("did not erase the right element \n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("erased the right element\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQDestroy(pq);
}

void Test(void)
{
	pq_t* pq = PQCreate(cmp_func);
	printf(CYAN "IS EMPTY" RESET_COLOR " TEST\n");
	if (!PQIsEmpty(pq))
	{
		printf("not empty after create.\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("empty after create\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQEnqueue(pq, &num4);
	PQEnqueue(pq, &num2);
	PQEnqueue(pq, &num7);
	printf(CYAN "ENQUEUE/IS EMPTY" RESET_COLOR " TEST\n");
	if (PQIsEmpty(pq))
	{
		printf("empty after enqueues\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("not empty after enqueues\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	printf(CYAN "ENQUEUE/LENGTH" RESET_COLOR " TEST\n");
	if (3 != PQSize(pq))
	{
		printf("missing enqueues/size is wrong\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("right length after enqueue\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQEnqueue(pq, &num4);
	PQEnqueue(pq, &num1);
	
	printf(CYAN "DEQUEUE" RESET_COLOR " TEST\n");
	if (1 != *(int*)PQDequeue(pq) ||
	    2 != *(int*)PQDequeue(pq) ||
	    4 != *(int*)PQDequeue(pq) ||
	    4 != *(int*)PQDequeue(pq))
	{
		printf("wrong values at enqueue\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("right values at enqueue.\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	printf(CYAN "DEQUEUE/LENGTH" RESET_COLOR " TEST\n");
	if (1 != PQSize(pq))
	{
		printf("missing dequeues/size is wrong\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("has right length after dequeue\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQDequeue(pq);
	PQEnqueue(pq, &num2);
	PQEnqueue(pq, &num6);
	PQEnqueue(pq, &num5);
	PQEnqueue(pq, &num3);
	PQEnqueue(pq, &num9);
	PQEnqueue(pq, &num8);
	printf(CYAN "PEEK" RESET_COLOR " TEST\n");
	if (2 != *(int*)PQPeek(pq))
	{
		printf("peek returns wrong value\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("peek returns right value\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQClear(pq);
	printf(CYAN "CLEAR" RESET_COLOR " TEST\n");
	if (!PQIsEmpty(pq))
	{
		printf("not empty after clear\n");
		printf(RED "---FAILED---\n\n" RESET_COLOR);
		PQDestroy(pq);
		return;
	}
	printf("empty after clear\n");
	printf(GREEN "---PASSED---\n\n" RESET_COLOR);
	
	PQDestroy(pq);
}

int main ()
{
	printf("\n");
	Test();
	EraseTest();
		
	return 0;
}
