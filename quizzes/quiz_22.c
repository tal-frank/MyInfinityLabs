#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

typedef struct Queue
{
	stack_ty* stack1;
	stack_ty* stack2;
}queue_ty;

queue_ty* QueueCreate(size_t capacity)
{
    /* ### Make improvements to the code below as needed ### */

	queue_ty* queue = (queue_ty*)malloc(sizeof(queue_ty));
	if (queue == NULL)
		return NULL;

	queue->stack1 = StackCreate(capacity);
	if (NULL == queue->stack1)
	{
		free(queue);
		queue = NULL;
		return NULL;
	}
	queue->stack2 = StackCreate(capacity);
	if (NULL == queue->stack2)
	{
		free(queue);
		queue = NULL;
		free(queue->stack1);
		queue->stack1 = NULL;
		return NULL;
	}
	return queue;
}

void QueueEnqueue(queue_ty* queue, int data)
{
	assert(NULL != queue);
	StackPop(queue->stack1);
}

int QueueDequeue(queue_ty* queue)
{
	int first_in = 0;
	assert(NULL != queue);
	while(0 != StackSize(queue->stack1))
	{
		StackPush(queue->stack2, StackPeek(queue->stack1));
		StackPop(queue->stack1);
	}
    
	first_in = StackPeek(queue->stack2);
	StackPop(queue->stack2);
    
	while(0 != StackSize(queue->stack2))
	{
		StackPush(queue->stack1, StackPeek(queue->stack2));
		StackPop(queue->stack1);
	}
	return first_in;
}


int main()
{
	queue_ty* queue = QueueCreate(20);
	
	
	return 0;
}
