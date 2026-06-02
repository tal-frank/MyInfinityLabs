#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct AVLTree avl_t; 

typedef enum
{
    PREORDER,
    INORDER,
    POSTORDER
} traversal_t;

/********************************* AVLCreate ********************************
	
* Description: Creates a new empty AVL tree.
*
*   Arguments: cmp_func - A user defined copmpare function for the BST to insert 
*			  in right order.
*
*      Return: A pointer to the AVL created.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
avl_t* AVLCreate(int (*cmp_func)(const void* data, const void* tree_data));

/********************************* AVLDestroy ********************************
* 		
* Description: destroys a given AVL;
*
*   Arguments: avl - A valid pointer to a binary search tree to destroy.
*
*      Return: None.
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
void AVLDestroy(avl_t* avl);

/********************************* AVLInsert ********************************
* 		
* Description: Inserts a new element to a given AVL in the right place according
*	       to the compare function given by the user. Inserting an element with
*	       data allready exists in the AVL is undefind. recommanded to use AVLFind
*	       before use BSTInsert. The tree balances itself in every insertion.
*
*   Arguments:  avl - A valid pointer to an AVL tree to insert new element to.
*	       data - A data that the new element will hold.
*
*      Return: 0 in success, none zero otherwise.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/
int AVLInsert(avl_t* avl, void* data);

/********************************* AVLRemove ********************************
* 		
* Description: Removes a given element from the AVL. The tree will balance itself 
*	       after every removal. The function recieves the data of the element
*	       and searches for it, then removes it.
*
*   Arguments:  avl - A valid pointer to an AVL tree to remove an element from.
*	       data - The data of the element to remove.
*
*      Return: None.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/
void AVLRemove(avl_t* avl, const void* data);

/********************************* AVLHeight ********************************
* 		
* Description: Get the height of a given AVL.
*
*   Arguments:  avl - A valid pointer to an AVL tree to get its height.
*
*      Return: Height of the AVL.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
size_t AVLHeight(const avl_t* avl);

/********************************* AVLCount ********************************
* 		
* Description: Counts the number of elements stored in the AVL.
*
*   Arguments: bst - A valid pointer to an AVL tree to count its elements.
*
*      Return: The number of elements stored in the AVL.
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
size_t AVLCount(const avl_t* avl);

/********************************* AVLIsEmpty ********************************
* 		
* Description: check if the AVL is empty.
*
*   Arguments: avl - A valid pointer to an AVL tree to check if empty.
*
*      Return: 1 if empty, 0 if not.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
int AVLIsEmpty(const avl_t* avl); 

/********************************* BSTFind ********************************
* 		
* Description: Finds if an elemet exists in the AVL. if exists returns a pointer with the data of 
*	       the element, else returns NULL.
*
*   Arguments:  avl - A valid pointer to an AVL tree to search in.
*	       data - A data to compare with the elements.
*
*      Return: pointer with the elements data on success, NULL on failure.
*
*  Complexity: Time: O(log(n)) Space: O(1)
*		
*		
******************************************************************************/
void* AVLFind(const avl_t* avl, const void* data);

/********************************* BSTForEach ********************************
* 		
* Description: A function that performs an operation on each element on the range 
* 	       from(inclusive)-to(exclusive) in the AVL. to ensure the order of the AVL the 
*	       operation must not change any order of the elements. otherwise, undefined.
*
*   Arguments:      avl - A valid pointer to an AVL tree to perform the operations on.
*	       act_func - An action function to operate on every element in the AVL.
*		  param - A paramener for the act_func.
*	       traversal_type - set the order in which the operations will be performed. there are three 
*				possible options: PREORDER, INORDER and POSTORDER.
*
*      Return: 0 on success, none 0 otherwise.
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
int AVLForEach(avl_t* avl, 
               int (*act_func)(void* data, void* param),
               void* param,
               traversal_t traversal_type);


/* not done yet */
int AVLMultiFind(const avl_t* avl, const void* data);
void AVLRemoveMultiple(avl_t* avl, const void* data); 
/* not done yet */


#endif /* END of __AVL_H__ */
