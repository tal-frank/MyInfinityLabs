#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h>

#include "../include/doubly_linked_list.h"

typedef struct sorted_list sorted_list_t;
typedef struct SortedListIter sorted_list_iter_t;

struct SortedListIter
{
	dll_iter_t inner_iter;
	#ifndef NDEBUG
	    	sorted_list_t* list;
	#endif /*NDEBUG*/				
};

/*****************************************************************
* 		
* Description: Initializes a sorted list.
*
*   Arguments: cmo_func - A compare function that compares between elements
*			  by a key that decided by the user.
*		
*      Return: A pointer to a sorted list. NULL if failure occurs.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_t* SortedListCreate(int (*cmp_func)(const void* param1, const void* param2));

/*****************************************************************
* 		
* Description: Destroys a sorted list.
*		        
*   Arguments: dll - A sorted list pointer to destroy.
*		
*      Return: None.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

void SortedListDestroy(sorted_list_t* sl);

/*****************************************************************
* 		
* Description: Inserts an element with "data" to the list at the first place
*	       the new data inserted is equal or bigger from the data of the 	
*	       element. 
*		        
*   Arguments: sl   - A sorted_list pointer to insert the data to.
*	       data - The data that the new node will hold.
*		
*      Return: The iterator inserted. If failes returns the last.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListInsert(sorted_list_t* sl, const void* data);

/*****************************************************************
* 		
* Description: Removes an element from the list.
*		        
*   Arguments: iter - An iterator to remove from the list.
*		
*      Return: The iterator after the one who got removed.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

/*****************************************************************
* 		
* Description: Finds the first element the cmp_func finds in the list between "from" 
*	       (inclusive) and "to"(exclusive). The cmp_func would be the one provided 
*	       by the user while creating the list.
*		        
*   Arguments: sl        - A pointer to a sorted list.
*	       from      - The element to start looking from (inclusive).
*	       to        - The element to stop looking at (exclusive).
*	       param     - The parameter to search in the list.
*	
*      Return: an iterator to the element it found. The "to" iterator when failure occurs.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListFind(const sorted_list_t* sl,
                                  sorted_list_iter_t from,
                                  sorted_list_iter_t to,
                                  const void* param);

/*****************************************************************
* 		
* Description: Takes the elements from the src list and inserts them to the dest list.
*	       At the end of the operation the src list will be empty.
*		        
*   Arguments: dest - A pointer to the destination list where the merged list be stored.
*	       src  - A pointer to the source list to be merged with dest. Remains empty
*		      at the end of the operation.
*		
*      Return: None.
*		
*  Complexity: Time: O(n + m) Space: O(1)
*		
*		
******************************************************************************/
         
void SortedListMerge(sorted_list_t* dest, sorted_list_t* src);

/*****************************************************************
* 		
* Description: Returns the first element of the list. 
*
*   Arguments: dll - A sorted list pointer to get it's first element.
*		
*      Return: The first valid element on the list.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListBegin(const sorted_list_t* sl);

/*****************************************************************
* 		
* Description: Returns the last element of the list. The returned element is not valid.
*		        
*   Arguments: dll - A sorted list pointer to get it's last element.
*		
*      Return: Last element of the list.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListEnd(const sorted_list_t* sl);

/*****************************************************************
* 		
* Description: Finds the first element the is_match_func finds in the list between "from" 
*	       (inclusive) and "to"(exclusive).
*		        
*   Arguments: from          - The element to start looking from (inclusive).
*	       to            - The element to stop looking at (exclusive).
*	       is_match_func - A function pointer to compare between the elements.
*	       param         - The parameter to search in the list.
*	
*      Return: an iterator to the element it found. The "to" iterator when failure occurs.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*is_match_func)(const void* param1, const void* param2),
                                    const void* param);

/*****************************************************************
* 		
* Description: removes the last element from the list.
*		        
*   Arguments: sl - A pointer to a list to remove an element from.
*		
*      Return: The last element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void* SortedListPopBack(sorted_list_t* sl);

/*****************************************************************
* 		
* Description: removes the first element from the list.
*		        
*   Arguments: sl - A pointer to a list to remove an element from.
*		
*      Return: The first element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void* SortedListPopFront(sorted_list_t* sl);

/*****************************************************************
* 		
* Description: Finds out if two iterators are equal.
*		        
*   Arguments: iter1 - An iterator to compare.
*	       iter2 - An iterator to compare.
*		
*      Return: 1 if equal, 0 if not.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

/*****************************************************************
* 		
* Description: Gets the next element on the list.
*		        
*   Arguments: iter - An iterator to get the next of.
*		
*      Return: An iterator to the next element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/*****************************************************************
* 		
* Description: Gets the prev element on the list.
*		        
*   Arguments: iter - An iterator to get the prev of.
*		
*      Return: An iterator to the prev element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/*****************************************************************
* 		
* Description: Get the data stored in a specific node.
*		        
*   Arguments: iter - An iterator to get the data from.
*		
*      Return: The data stored in the node.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void* SortedListGetData(sorted_list_iter_t iter);

/*****************************************************************
* 		
* Description: Activates a chosen by the user operation on a range of the list one by
* 	       one in a specified range from (inclusive) ... to (exclusive).
*	       The operation must act the same on every element. otherwise undefined.
*		        
*   Arguments: from   - An iterator to start the action on (inclusive).
*	       to     - An iterator to stop the action on (exclusive).
*	       action - A function pointer to the action the user want to activate.
*			The function should recieve the iterator data and a 
*			parameter to act with.
*	       param  - A parameter to insert to the function.
*		
*      Return: The "to" iterator if succeeded, and the last iterator tried to act on 
*	       when failure occurs.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from,
                                     sorted_list_iter_t to,
                                     int (*action_func)(void* data, void* param),
                                     void* param);

/*****************************************************************
* 		
* Description: Finds out if a list is empty.
*		        
*   Arguments: sl - A pointer to a list to check if empty.
*		
*      Return: 1 if empty, 0 otherwise.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
                                    
int SortedListIsEmpty(const sorted_list_t* sorted_list);

/*****************************************************************
* 		
* Description: Counts the number of elements in the list.
*		        
*   Arguments: sl - A pointer to a list to count the elements in.
*		
*      Return: Number of elements in the list.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

size_t SortedListSize(const sorted_list_t* sorted_list);

#endif 

