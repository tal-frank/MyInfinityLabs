#ifndef __PQ_H__
#define __PQ_H__

#include "heap.h"

typedef struct priority_queue pq_t;
 
/*****************************************************************
* 		
* Description: Creates a priority queue.
*
*   Arguments: CmpFunc - A compare function provided by the user to sort the queue.
*		
*      Return: Returns a pointer to a priority queue.
*		
*  Complexity: Time: O(1), Space: O(1)
*		
*		
******************************************************************************/

pq_t* PQCreate(int (*CmpFunc)(const void* data, const void* param));

/*****************************************************************
* 		
* Description: Destroys a priority queue.
*
*   Arguments: pq - A valid pointer to a priority queue.
*		
*      Return: None.
*		
*  Complexity: O(n), Space: O(1)
*		
*		
******************************************************************************/

void PQDestroy(pq_t* pq);

/*****************************************************************
* 		
* Description: Inserts an element with "data" to the queue at the first place
*	       the new data inserted is equal or bigger from the data of the 	
*	       element. 
*
*   Arguments: pq   - A valid pointer to a priority queue to insert the data to.
*	       data - The data that the new element will hold.
*		
*      Return: None.
*		
*  Complexity: O(n), Space: O(1)
*		
*		
******************************************************************************/

int PQEnqueue(pq_t* pq, void* data); 

/*****************************************************************
* 		
* Description: Removes and fetches the data of the element with the highes priority.
*
*   Arguments: pq - A valid pointer to a priority queue to operate on.
*		
*      Return: 0 for seccess, none zero otherwise.
*		
*  Complexity: O(1), Space: O(1)
*		
*		
******************************************************************************/

void* PQDequeue(pq_t* pq);

/*****************************************************************
* 		
* Description: Fetches the data of the element with the highest priority in the queue.
*
*   Arguments: pq - A valid pointer to a priority queue to get it's data.
*		
*      Return: Data of the element with the highest priority in the queue.
*		
*  Complexity: O(1), Space: O(1)
*		
*		
******************************************************************************/

void* PQPeek(const pq_t* pq);

/*****************************************************************
* 		
* Description: Checks if the queue is empty
*
*   Arguments: pq - A valid pointer to a priority queue to check if empty.
*		
*      Return: 1 if empty, 0 otherwise.
*		
*  Complexity: O(1), Space: O(1)
*		
*		
******************************************************************************/

int PQIsEmpty(const pq_t* pq);

/*****************************************************************
* 		
* Description: Gets the length of the queue.
*
*   Arguments: pq - A valid pointer to a priority queue to check ts length.
*		
*      Return: Length of the queue.
*		
*  Complexity: O(n), Space: O(1)
*		
*		
******************************************************************************/

size_t PQSize(const pq_t* pq);

/*****************************************************************
* 		
* Description: Erases all elements from the queue.
*
*   Arguments: pq - A valid pointer to a priority queue to clear.
*		
*      Return: None.
*		
*  Complexity: O(n), Space: O(1)
*		
*		
******************************************************************************/

void PQClear(pq_t* pq);

/*****************************************************************
* 		
* Description: Erases the first apearance of element from top priority to lowest,
*	       which its data equals to param by IsMatch function, provided by the user.
*
*   Arguments: IsMatch - A match function provided by the user to find the element to erase.
*		
*      Return: Data of the erased element if element found, NULL if not found.
*		
*  Complexity: O(n), Space: O(1)
*		
*		
******************************************************************************/

void* PQErase(pq_t* pq, int (*IsMatch)(const void* data, const void* param),const void* param);

#endif
