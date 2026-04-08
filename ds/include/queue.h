
#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>

/******************************************************************** Structs */
typedef struct Queue queue_t;

/************************************************************* Main functions */
/*******************************************************************************
* Description: Allocates space for a queue and returns a pointer to it. 
*		        
*   Arguments: None.
*		        
*      Return: A pointer to the new Queue. NULL when unsuccessful.
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
queue_t* QueueCreate(void); 

/*******************************************************************************
* Description: Frees the Queue.
*		        
*   Arguments: queue - A queue to destroy.
*		        
*      Return: None.
*		        
*  Complexity: time: O(n) space: O(1)
*		        
*		        
******************************************************************************/

void QueueDestroy(queue_t* queue);

/*******************************************************************************
* Description: Inserts an element to the end of the queue.
*		        
*   Arguments: queue   - A queue to insert the element to.
*	       element - An element to add to the queue.
*		        
*      Return: 0 for success, none 0 for failure.
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
/* insert to tail of queue */
int QueueEnqueue(queue_t* queue, const void* element);
/*******************************************************************************
* Description: Removes the first element in the queue.
*		        
*   Arguments: queue - A queue to remove the element from.
*		        
*      Return: None.
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
/* remove from head of queue */
void QueueDequeue(queue_t* queue);
/*******************************************************************************
* Description: Gets the data of the first element in the queue.
*		        
*   Arguments: queue - A queue to get the first element from.
*		        
*      Return: Returns the data of the first element.
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
/* show the element in head */
void* QueuePeek(const queue_t* queue);
/*******************************************************************************
* Description: Checks if the queue is empty.
*		        
*   Arguments: queue - A queue to check if empty.
*		        
*      Return: 0 if empty, none zero otherwise.
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
int QueueIsEmpty(const queue_t* queue);
/*******************************************************************************
* Description: Gets a queue and calculates the number of elements in it.
*
*   Arguments: queue - A queue to find its length.
*		        
*      Return: The size of the queue.
*		        
*  Complexity: time: O(n) space: O(1)
*		        
*		        
******************************************************************************/
size_t QueueSize(const queue_t* queue);
/*******************************************************************************
* Description: 
*		        
*   Arguments: 
*		        
*      Return: 
*		        
*  Complexity: time: O(1) space: O(1)
*		        
*		        
******************************************************************************/
/* append one queue to another */
void QueueAppend(queue_t* dest, queue_t* src);
/*********************************************************
-  leaves src as empty queue
-  need to add a function in Sll to append linked lists
**********************************************************/

#endif /************************************************* End of  __QUEUE_H__ */
