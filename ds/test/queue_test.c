#include <stdio.h> /* printf */
#include <stddef.h>

#include "../include/queue.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

static int element_arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};


void EnqueueTest(void)
{
	size_t i = 0;
	queue_t* queue = QueueCreate();
	
	printf("started " CYAN "ENQUEUE" RESET_COLOR " test:\n");
	
	for(i = 0; 8 > i; ++i)
	{
		QueueEnqueue(queue, &element_arr[i]);
		if ((i + 1) != QueueSize(queue) || 
		    element_arr[0] != *(int*)QueuePeek(queue))
		{
			printf(RED "enqueue FAILED%ld\n\n" RESET_COLOR, i);
			return;
		}
	}
	
	printf(GREEN "enqueue PASSED\n\n" RESET_COLOR);
	QueueDestroy(queue);
}


void DequeueTest(void)
{
	size_t i = 0;
	queue_t* queue = QueueCreate();
	
	printf("started " CYAN "DEQUEUE" RESET_COLOR " test:\n");
	
	for(i = 0; 8 > i; ++i)
	{
		QueueEnqueue(queue, &element_arr[i]);
	}
	
	for(i = 0; 7 > i; ++i)
	{
		QueueDequeue(queue);
		if ((7 - i) != QueueSize(queue) || 
		    element_arr[i + 1] != *(int*)QueuePeek(queue))
		{
			printf(RED "dequeue FAILED%ld\n\n" RESET_COLOR, i);
			return;
		}
	}
	QueueDequeue(queue);
	if (0 != QueueSize(queue))
	{
		printf(RED "dequeue  last FAILED\n\n" RESET_COLOR);
	}
	
	printf(GREEN "dequeue PASSED\n\n" RESET_COLOR);
	QueueDestroy(queue);
}


void QIsEmptyTest(void)
{
	queue_t* queue = QueueCreate();

	printf("started " CYAN "IS EMPTY" RESET_COLOR " test:\n");

	if (!QueueIsEmpty(queue))
	{
		printf(RED "is empty FAILED1\n\n" RESET_COLOR);
		return;
	}
	
	QueueEnqueue(queue, &element_arr[0]);
	
	if (QueueIsEmpty(queue))
	{
		printf(RED "is empty FAILED2\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "is empty PASSED\n\n" RESET_COLOR);
	QueueDestroy(queue);
}


void SizeTest(void)
{
	queue_t* queue = QueueCreate();
	size_t size = 0;
	printf("started " CYAN "SIZE" RESET_COLOR " test:\n");
	
	size = QueueSize(queue);
	if (0 != size)
	{
		printf(RED "size FAILED1\n\n" RESET_COLOR);
		return;
	}
	
	QueueEnqueue(queue, &element_arr[0]);
	size = QueueSize(queue);
	if (1 != size)
	{
		printf(RED "size FAILED2\n\n" RESET_COLOR);
		return;
	}
	
	QueueEnqueue(queue, &element_arr[1]);
	QueueEnqueue(queue, &element_arr[1]);
	size = QueueSize(queue);
	if (3 != size)
	{
		printf(RED "size FAILED3\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "size PASSED\n\n" RESET_COLOR);
	QueueDestroy(queue);
}


void AppendTest(void)
{
	queue_t* dest_queue = QueueCreate();
	queue_t* src_queue = QueueCreate();
	size_t i = 0;
	
	printf("started " CYAN "APPEND" RESET_COLOR " test:\n");
	
	for(i = 0; 3 > i; ++i)
	{
		QueueEnqueue(dest_queue, &element_arr[i]);
	}
	
	if (3 != QueueSize(dest_queue) || 0 != QueueSize(src_queue))
	{
		printf(RED "append FAILED\n\n" RESET_COLOR);
		return;
	}
	
	for(i = 3; 8 > i; ++i)
	{
		QueueEnqueue(src_queue, &element_arr[i]);
	}
	
	QueueAppend(dest_queue, src_queue);
	
	
	if (8 != QueueSize(dest_queue) || 0 != QueueSize(src_queue))
	{
		printf(RED "append FAILED\n\n" RESET_COLOR);
		return;
	}

	printf(GREEN "append PASSED\n\n" RESET_COLOR);
	QueueDestroy(dest_queue);
	QueueDestroy(src_queue);
}


int main()
{
	printf("\n");

	QIsEmptyTest();
	SizeTest();
	EnqueueTest();
	DequeueTest();
	AppendTest();
	
	return 0;
}
