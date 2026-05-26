#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stddef.h> /* size_t */ 

typedef struct Binary_search_tree bst_t;
typedef struct Tree_node* bst_iter_t;

/********************************* BSTCreate ********************************
* 		
* Description: Creates a new empty travesal binary search tree.
*
*   Arguments: cmp_func - A user defined copmpare function for the BST to insert 
*			  in right order.
*
*      Return: A pointer to the BST created.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

bst_t* BSTCreate(int (*cmp_func)(void* data, void* param));

/********************************* BSTDestroy ********************************
* 		
* Description: destroys a given BST;
*
*   Arguments: bst - A valid pointer to a binary search tree to destroy.
*
*      Return: None.
*
*  Complexity: Time: O(nlog(n)) Space: O(1)
*		
*		
******************************************************************************/

void BSTDestroy(bst_t* bst);

/********************************* BSTInsert ********************************
* 		
* Description: Inserts a new element to a given BST in the right place according
*	       to the compare function given by the user. Inserting an element with
*	       data allready exists in the BST is undefind. recommanded to use BSTFind
*	       before use BSTInsert. 
*
*   Arguments:  bst - A valid pointer to a binary search tree to insert new element to.
*	       data - A data that the new element will hold.
*
*      Return: The element inserted or iterator to a none valid element when failed.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTInsert(bst_t* bst, void* data);

/********************************* BSTRemove ********************************
* 		
* Description: Removes a given element from the BST.
*
*   Arguments: iter - An iterator to a valid element to remove.
*
*      Return: None.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

void BSTRemove(bst_iter_t iter);

/********************************* BSTEnd ********************************
* 		
* Description: Returns a pointer to a none valid element that represents the end of the BST.
*
*   Arguments: bst - A valid pointer to a binary search tree to get its ending.
*
*      Return: A a pointer to a none valid element that represents the end of the BST.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTEnd(const bst_t* bst);

/********************************* BSTBegin ********************************
* 		
* Description: Returns a pointer to the first (smallest according to cmp_func) element of the BST.
*
*   Arguments: bst - A valid pointer to a binary search tree to get its beginning.
*
*      Return: Apointer to the first (smallest according to cmp_func) element of the BST.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTBegin(const bst_t* bst);

/********************************* BSTNext ********************************
* 		
* Description: Returns an iterator of the next in size element in the BST.
*
*   Arguments: iter - An iterator of the element desired to jump to its next.
*
*      Return: An iterator of the next in size element in the BST.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTNext(bst_iter_t iter);

/********************************* BSTPrev ********************************
* 		
* Description: Returns an iterator of the previous in size element in the BST.
*
*   Arguments: iter - An iterator of the element desired to jump to its previous.
*
*      Return: An iterator of the previous in size element in the BST.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTPrev(bst_iter_t iter);

/********************************* BSTGetData ********************************
* 		
* Description: Fetches the data of the element of the iterator.
*
*   Arguments: iter - An iterator of the element desired to get its data.
*
*      Return: The data of the element of the iterator.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void* BSTGetData(bst_iter_t iter);

/********************************* BSTIsEmpty ********************************
* 		
* Description: check if the BST is empty.
*
*   Arguments: bst - A valid pointer to a binary search tree to check if empty.
*
*      Return: 1 if empty, 0 if not.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

int BSTIsEmpty(const bst_t* bst);

/********************************* BSTCount ********************************
* 		
* Description: Counts the number of elements stored in the BST.
*
*   Arguments: bst - A valid pointer to a binary search tree to count its elements.
*
*      Return: The number of elements stored in the BST.
*
*  Complexity: Time: O(nlog(n)) Space: O(1)
*		
*		
******************************************************************************/

size_t BSTCount(const bst_t* bst);

/********************************* BSTIsIterEqual ********************************
* 		
* Description: Checks if two iterators are the same.
*
*   Arguments: iter1 - an iterator to compare.
*	       iter2 - an iterator to compare.
*
*      Return: 1 if equal, 0 if not.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

int BSTIsIterEqual(bst_iter_t iter1, bst_iter_t iter2);

/********************************* BSTFind ********************************
* 		
* Description: Finds if an elemet in the BST exists. if exists returns an iterator for 
*	       it, else returns an iterator for the end of BST.
*
*   Arguments:   bst - A valid pointer to a binary search tree to search in.
	       param - A data to compare with the elements.
*
*      Return: 
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/

bst_iter_t BSTFind(const bst_t* bst, void* param);

/********************************* BSTForEach ********************************
* 		
* Description: A function that performs an operation on each element on the range 
* 	       from(inclusive)-to(exclusive) in the BST. returns the number of 
*	       successful operations done. to ensure the order of the BST the 
*	       operation must not change any order of the elements. otherwise, undefined.
*
*   Arguments:     from - An iterator to start from (inclusive).
*		     to - An iterator to stop on (exclusive).
*	       act_func - An action function to operate on every element in the range.
*		  param - A paramener for the act_func.
*
*      Return: 
*
*  Complexity: Time: O(nlog(n)) Space: O(1)
*		
*		
******************************************************************************/

int BSTForEach(bst_iter_t from,
               bst_iter_t to,
               int (*act_func)(void* data, void* param),
               void* param);



/******************* FOR WHITEBOX TEST *******************/
bst_iter_t GetBigChildForWhiteboxTest(bst_iter_t iter);
bst_iter_t GetSmallChildForWhiteboxTest(bst_iter_t iter);
/******************* FOR WHITEBOX TEST *******************/


#endif /** End of __BINARY_SEARCH_TREE_H__ */
