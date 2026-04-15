#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__


typedef struct Doubly_linked_list dll_t;
typedef struct Dll_Iterator* dll_iter_t;


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
dll_t* DllCreate(void);

/**************************************************************** DllDestroy *
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

/**************************************************************** DllBegin *
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

dll_iter_t DllBegin(const dll_t* dll);

/**************************************************************** DllEnd *
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

dll_iter_t DllEnd(const dll_t* dll);

/**************************************************************** DllInsert *
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

/**************************************************************** DllRemove *
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

/**************************************************************** DllCount *
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

/**************************************************************** DllGetData *
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

/**************************************************************** DllIsEmpty *
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

/**************************************************************** DllGetNext *
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

/**************************************************************** DllGetPrev *
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

/**************************************************************** DllIsIterEqual *
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

/**************************************************************** DllFind *
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

/**************************************************************** DllForEach *
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

/**************************************************************** DllMultiFind *
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
                        dll_t* dest_dll);
                        
/**************************************************************** DLLSplice *
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

/**************************************************************** DllPushFront *
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

/**************************************************************** DllPushBack *
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
dll_iter_t DllPushBack(dll_t* dll, void* data);

/**************************************************************** DllPopFront *
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

dll_iter_t DllPopFront(dll_t* dll);

/**************************************************************** DLlPopBacke *
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

dll_iter_t DLlPopBack(dll_t* dll);


#endif /** End of __DOUBLY_LINKED_LIST_H__ */
