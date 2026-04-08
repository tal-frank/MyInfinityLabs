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
* 		After the operation the iterator is no more valid.
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
* Description:	Iterates on the elements of the list and counts them.
* 		After the operation the iterator is no more valid.
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
*		"from" can not be equal to "to".
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

int SllIsEmpty(const sll_t* sll);

/**
* Description: 	Activates a chosen by the user operation on a range of the list one by
* 	       	one in a specified range from ... to (not include to).
* 
* Arguments:    from   - An iterator to start the action on.
*		to     - An iterator to stop the action on. (not acting on that specific iteratpr).
*		action - A function pointer to the action the user want to activate.
*			 The function should recieve the iterator data and a parameter to act with.
*		param  - A parameter to insert to the function.
* 
* Return:	The to iterator if succeeded, and the last iterator tried to act on when failure occur.
*   
* Complexity: 	O(n)
*/

sll_iter_t SllForEach(sll_iter_t from, sll_iter_t to, int (*action_func)(void* data, void* param), void* param); 

/**
* Description: 	Reverse the order of a chosen list.
* 
* Arguments: 	head - an iterator to the beginning of the list.
* 
* Return: 	The iterator to the new beginning of the list.
*   
* Complexity: 	o(n)
*/

sll_iter_t Flip(sll_iter_t head);

/**
* Description: 	Find out if the list has a loop in it.
* 
* Arguments: 	head - An iterator to the beginning of the list.
* 
* Return: 	1 if a loop found, 0 if not.
*   
* Complexity:	O(n)
*/

int HasLoop(const sll_iter_t head);

/**
* Description: 	Get an iterator and sets the next address in the place it points on.
* 
* Arguments: 	iter      - An element to set the address into.
* 		iter_next - An iterator to store in the next of iter.
*
* Return:	none.
*   
* Complexity:	O(1)
*/

void SllSetAddr(sll_iter_t iter, sll_iter_t iter_next);

/**
* Description: 	Get 2 iterators of lists and find out if they have a common element.
* 
* Arguments: 	head1 - An iterator to the first list beginning.
* 		head2 - An iterator to the second list beginning.
*
* Return:	the common element if found one, the last element of head1 if not.
*   
* Complexity:	O(n)
*/

sll_iter_t FindIntersection(sll_iter_t head1, sll_iter_t head2);

void SllAppend(sll_t* dest, sll_t* src);

size_t SllCount(sll_iter_t from, sll_iter_t to);


#endif /* END of __SINGLE_LINKED_LIST_H__ */

