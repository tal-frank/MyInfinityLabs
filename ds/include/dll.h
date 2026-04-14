#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__


typedef Doubly_linked_list dll_t;
typedef Dll_Iterator dll_iter_t;


/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/
dll_t* DllCreate( void);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

void DllDestroy(dll_t* dll);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllBegin(const dll_t* dll;

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllEnd(const dll_t* dll;

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllInsert(dll_t* dll, dll_iter_t iter, const void* data);/* return the current on success and the end at fail */

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllRemove(dll_t* dll, dll_iter_t iter);/* return next iter */

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

size_t DllCount(const dll_t* dll);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

void* DllGetData(dll_iter_t iter);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

int DllIsEmpty(const dll_t* dll);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllGetNext(dll_iter_t iter);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllGetPrev(dll_iter_t iter);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

int DllIsIterEqual(dll_iter_t iter1, dll_iter_t iter2);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllFind(dll_iter_t from, dll_iter_t to, int (*comp_func)(const void* data, const void* param), void* param);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllForEach(dll_iter_t from, dll_iter_t to, int (*action_func)(void* data, void* param), void* param);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

/* returns a pointer to a new dll with all the values found */
dll_iter_t DllMultiFind(dll_iter_t from, dll_iter_t to,
                        int (*IsMatch)(const void* list_data, const void* param),
                        const void* param,
                        dll_t* dest_dll); - O(n), O(n)
                        
                        /**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

/* take the nodes from "from" up to "to" not included and isert the m before where  */
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

/* insert before the head */
dll_iter_t DllPushFront(dll_t* dll, void* data);

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

/* insert before end */
dll_iter_t DllPushBack(dll_t* dll, void* data); - O(1), O(1)

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DllPopFront(dll_t* dll); - O(1), O(1)

/**************************************************************** DllCreate *
* 		
* Description: 
*		        
*   Arguments: 
*		
*      Return: 
*		
*  Complexity: Time: O() Space: O()
*		
*		
******************************************************************************/

dll_iter_t DLlPopBack(dll_t* dll); - O(1), O(1)


#endif /** End of __DOUBLY_LINKED_LIST_H__ */
