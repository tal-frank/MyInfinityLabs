#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__


typedef struct Doubly_linked_list dll_t;
typedef struct Dll_Node* dll_iter_t;


/**************************************************************** DllCreate *
* 		
* Description: Initializes a doubly linkes list.
*
*   Arguments: None.
*		
*      Return: A pointer to a doubly liked list. NULL if failure occurs.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
dll_t* DllCreate(void);

/**************************************************************** DllDestroy *
* 		
* Description: Destroys a doubly linked list.
*		        
*   Arguments: dll - A doubly liked list pointer to destroy.
*		
*      Return: None.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

void DllDestroy(dll_t* dll);

/**************************************************************** DllBegin *
* 		
* Description: Returns the first element of the list. 
*
*   Arguments: dll - A doubly liked list pointer to get it's first element.
*		
*      Return: The first valid element on the list.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllBegin(const dll_t* dll);

/**************************************************************** DllEnd *
* 		
* Description: Returns the last element of the list. The returned element is not valid.
*		        
*   Arguments: dll - A doubly liked list pointer to get it's last element.
*		
*      Return: Last element of the list.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllEnd(const dll_t* dll);

/**************************************************************** DllInsert *
* 		
* Description: Inserts an element with "data" to the list before the "where". 
*		        
*   Arguments: dll   - The dll to insert the data to.
*	       where - An iterator to insert the data before it.
*	       data  - The data that the new node will hold.
*		
*      Return: The iterator inserted. If failes returns the last.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllInsert(dll_t* dll, dll_iter_t where, const void* data);/* return the current on success and the end at fail */

/**************************************************************** DllRemove *
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

dll_iter_t DllRemove(dll_iter_t iter);/* return next iter */

/**************************************************************** DllCount *
* 		
* Description: Counts the number of elements in the list.
*		        
*   Arguments: dll - A pointer to a list to count the elements in.
*		
*      Return: Number of elements in the list.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

size_t DllCount(const dll_t* dll);

/**************************************************************** DllGetData *
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

void* DllGetData(dll_iter_t iter);

/**************************************************************** DllIsEmpty *
* 		
* Description: Finds out if a list is empty.
*		        
*   Arguments: dll - A pointer to a list to check if empty.
*		
*      Return: 1 if empty, 0 otherwise.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int DllIsEmpty(const dll_t* dll);

/**************************************************************** DllGetNext *
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

dll_iter_t DllGetNext(dll_iter_t iter);

/**************************************************************** DllGetPrev *
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

dll_iter_t DllGetPrev(dll_iter_t iter);

/**************************************************************** DllIsIterEqual *
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

int DllIsIterEqual(dll_iter_t iter1, dll_iter_t iter2);

/**************************************************************** DllFind *
* 		
* Description: Finds the first element the comp_func finds in the list between "from" 
*	       (inclusive) and "to"(exclusive).
*		        
*   Arguments: from      - The element to start looking from (inclusive).
*	       to        - The element to stop looking at (exclusive).
*	       comp_func - A function pointer to compare between the elements.
*	       param     - The parameter to search in the list.
*	
*      Return: an iterator to the element it found. The "to" iterator when failure occurs.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllFind(dll_iter_t from, dll_iter_t to, int (*comp_func)(const void* data, const void* param), const void* param);

/**************************************************************** DllForEach *
* 		
* Description: Activates a chosen by the user operation on a range of the list one by
* 	       one in a specified range from (inclusive) ... to (exclusive).
*		        
*   Arguments: from   - An iterator to start the action on (inclusive).
*	       to     - An iterator to stop the action on (exclusive).
*	       action - A function pointer to the action the user want to activate.
*			 The function should recieve the iterator data and a parameter to act with.
*	       param  - A parameter to insert to the function.
*		
*      Return: The to iterator if succeeded, and the last iterator tried to act on when failure occurs.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllForEach(dll_iter_t from, dll_iter_t to, int (*action_func)(void* data, void* param), void* param);

/**************************************************************** DllMultiFind *
* 		
* Description: Gets a list and finds out if there are occurances of a specific 
*	       parameter. if found, searches for another occurance until there are 
*	       none left. every occurance found is copied into "dest_dll".
*		        
*   Arguments: from     - An iterator to start the search on (inclusive).
*	       to       - An iterator to stop the search on (exclusive).
*	       IsMatch  - A function pointer to compare between the elements.
*	       param    - The parameter to search in the list.
*	       dest_dll - A new list to insert the occurances into.
*		
*      Return: number of occurances of param in the list. -1 when failure occurs.
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

/* returns a pointer to a new dll with all the values found */
int DllMultiFind(dll_iter_t from, dll_iter_t to,
                        int (*IsMatch)(const void* list_data, const void* param),
                        const void* param,
                        dll_t* dest_dll);
                        
/**************************************************************** DLLSplice *
* 		
* Description: Removes a portion of successive elements from one list, and concatinate
*	       to another place in the list or a place in another list. if the place 
*	       to insert is between the "from" and "to" arguments, undefined.
*		        
*   Arguments: where - An iterator to the place to insert the portion of nodes.
*	       from  - An iterator to the first node in the list to transfer (inclusive).
*	       to    - An iterator to the last node in the list to transfer (exclusive).
*
*      Return: The "where" iterator.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

/* take the nodes from "from" up to "to" not included and isert the m before where  */
dll_iter_t DllSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);

/**************************************************************** DllPushFront *
* 		
* Description: add an element to the beginning list.
*		        
*   Arguments: dll - A list to add an element to.
*		
*      Return: The first element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

/* insert before the head */
dll_iter_t DllPushFront(dll_t* dll, const void* data);

/**************************************************************** DllPushBack *
* 		
* Description: add an element to the end list.
*		        
*   Arguments: dll - A list to add an element to.
*		
*      Return: The last element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

/* insert before end */
dll_iter_t DllPushBack(dll_t* dll, const void* data);

/**************************************************************** DllPopFront *
* 		
* Description: removes the first element from the list.
*		        
*   Arguments: dll - A list to remove an element from.
*		
*      Return: The first element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllPopFront(dll_t* dll);

/**************************************************************** DLlPopBacke *
* 		
* Description: removes the last element from the list.
*		        
*   Arguments: dll - A list to remove an element from.
*		
*      Return: The last element.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

dll_iter_t DllPopBack(dll_t* dll);


#endif /** End of __DOUBLY_LINKED_LIST_H__ */
