#ifndef __SINGLE_LINKED_LIST_H__
#define __SINGLE_LINKED_LIST_H__

#include <stddef.h> /* size_t */

/*********************************************** typedef's */
typedef struct Single_linked_list sll_t;
typedef struct Node* sll_iter_t;

/**
* Description:	Declares a single_linked_list struct and initialize it.
* 
* Arguments:	none.   
* 
* Return:	Pointer to a new sll.
*   
* Complexity: 	O(1)
*/

sll_t* SllCreate(void);

/**
* Description:	Frees the list and all the elements in it.
* 
* Arguments: 	sll - A list to free.
* 
* Return:  	none.
*   
* Complexity: 	O(n)
*/

void SllDestroy(sll_t* sll);

/**
* Description: 	Returns the first element of the list.
* 
* Arguments: 	sll - Singly_linked_list struct pointer to get its beginning.
* 
* Return: 	Returns the first element of the list. if the list is empty returns an element pointing to itself.
*   
* Complexity: 	O(1)
*/

sll_iter_t SllBegin(const sll_t* sll);

/**
* Description: 	Returns the last element of the list.
* 
* Arguments: 	sll - Singly_linked_list struct pointer to get its end.
* 
* Return: 	Returns the last element of the list. if the list is empty returns an element pointing to itself.
*   
* Complexity: 	O(1)
*/

sll_iter_t SllEnd(const sll_t* sll);

/**
* Description:	Gets the next element in the list.
* 
* Arguments:	iter - An iterator that points to the current data.
* 
* Return:     	The next element in the list.
*   
* Complexity: 	O(1)    
*/

sll_iter_t SllGetNext(sll_iter_t iter);

/**
* Description: 	Gets an element and removes it from the list. 
* 
* Arguments:	iter - An iterator that points to the element that should be removed.
* 
* Return: 	Returns the element that shows after the removed one.
*   
* Complexity: 	O(1)
*/

sll_iter_t SllRemove(sll_iter_t iter);

/**
* Description: 	Gets an element and inserts it before the one pointed by the iterator.
* 
* Arguments:	where - An iterator to insert the new data before it.
*		data  - New data to insert to the list.
* 
* Return: 	Returns the same iterator it got to insert the data before it.
*   
* Complexity: 	O(1)
*/

sll_iter_t SllInsertBefore(sll_iter_t where, const void* data);

/**
* Description:	iterates on the elements of the list and counts them.
* 
* Arguments:	sll - A linked list to count its elements.
* 
* Return:      The number of elements int the list.
*   
* Complexity:   O(n)
*/

size_t SllGetLength(const sll_t* sll);

/**
* Description: 	Checks if two iterators are equal.
* 
* Arguments:	iter1 & iter2 - Check if those two iterators are equal.
* 
* Return:      	1 if the iterators are equal, o otherwise.
*   
* Complexity:	O(1)
*/

int SllIterIsEqual(sll_iter_t iter1, sll_iter_t iter2);

/**
* Description:	Gets data and a range of iterators and search one by one if one of then has the data.
* 		The comperation is done via fuction pointer that the function recieves from the user.
*		The compare  function should return 1 if equal and 0 if not.
* 
* Arguments:	from          - The iterator to start the search from.
*		to            - The iterator to finish the search in. Doesn't check the last.
*		is_match_func - A comparison function pointer that recievs the data and a parameter
*				to compare it with.
*		param         - The parameter to search in the list. 
*
* Return: 	if found returns the iterator which the data found in. if not found returns the "to" iterator.
*   
* Complexity:
*/

sll_iter_t SllFind(sll_iter_t from, sll_iter_t to, int (*is_match_func)(void* data, void* param), void* param);

/**
* Description: 	Get an iterator and return the data it points on.
* 
* Arguments: 	iter - An iterator to get the data from.
* 
* Return: 	The data stored in the list at the place the pointer points on. Returns the to iter when failed to find.
*   
* Complexity: 	O(1)
*/

void* SllGetData(sll_iter_t iter);

/**
* Description: 	Get an iterator and sets the data in the place it points on.
* 
* Arguments: 	iter - An element to set the data into.
* 		data - a data to store in the element.
*
* Return:	none.
*   
* Complexity:	O(1)
*/

void SllSetData(sll_iter_t iter, const void* data);

/**
* Description: 	Checks if the list given to it is empty.
* 
* Arguments: 	sll - A list to check if empty.
* 
* Return: 	1 if empty, 0 otherwise.
*   
* Complexity:   O(1);  
*/

int IsEmpty(const sll_t* sll);

/**
* Description: Activates a chosen by the user operation on a range of the  list one by
* 	       one from 
* 
* Arguments:      
* 
* Return:      
*   
* Complexity:     
*/

sll_iter_t SllForEach(sll_iter_t from, sll_iter_t to, int (*action_func)(void* data, void* param), void* param); 


sll_iter_t Flip(sll_iter_t head);
int HasLoop(const sll_iter_t head);
void SllSetAddr(sll_iter_t iter, sll_iter_t iter_next);
sll_iter_t FindIntersection(sll_iter_t head1, sll_iter_t head2);


#endif /* END of __SINGLE_LINKED_LIST_H__ */

