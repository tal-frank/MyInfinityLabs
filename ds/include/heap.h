#ifndef __HEAP_H__
#define __HEAP_H__

/********************************************************* Standard libraries */

#include <stddef.h>

#include "dynamic_vector.h"

/******************************************************************* Typedefs */

typedef struct Heap heap_t;

/****************************************************************** HeapCreate *
 *
 * Description: Allocating an empty heap and returning pointer to it
 *
 * Arguments: cmp_func: a compare function that is providing a priority standart
 *           provided by the user. the function should return:
 *           if param1 is less than param2: negative number
 *           if param1 is equal to param2: zero
 *           if param2 is less than  param1: positive number
 *
 * Return: allocated heap, NULL if allocation failed
 *
 *  Complexity: Time: O(1) Space: O(1)
 *
 ******************************************************************************/
heap_t* HeapCreate(int (*cmp_func)(const void* key1, const void* key2));

/***************************************************************** HeapDestroy *
 *
 * Description: freeing an allocated heap.
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: void
 *
 * Complexity: Time: O(n) Space: O(1)
 *
 ******************************************************************************/

void HeapDestroy(heap_t* heap);
/******************************************************************** HeapPush *
 * Description: allocating and inserting a new element that containes `data`
 *              in the correct priority
 *
 * Arguments: heap: pointer to Non NULL heap
 *            data: Non data by reference
 *
 * Return: on success 0, when allocation fail non zero integer.
 *
 * Complexity: Time: O(log(n)) Space: O(1)
 ******************************************************************************/
int HeapPush(heap_t* heap, void* data);

/********************************************************************* HeapPop *
 * Description: removing and freeing the minimum element from a heap,
 *               and returning its data referance
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: returns the data refernce of the removed element
 *
 * Complexity: Time: O(log(n)) Space: O(1)
 ******************************************************************************/
void HeapPop(heap_t* heap);

/******************************************************************** HeapPeek *
 *
 * Description: returning the data referance of the minimum element from a heap.
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: the data referance of the minimum element
 *
 * Complexity: Time: O(1) Space: O(1)
 *
 ******************************************************************************/
void* HeapPeek(const heap_t* heap);

/***************************************************************** HeapIsEmpty *
 *
 * Description: checking if a heap is empty
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: 1 if the heap is empty, 0 otherwise
 *
 * Complexity: Time: O(1) Space: O(1)
 *
 ******************************************************************************/
int HeapIsEmpty(const heap_t* heap);

/******************************************************************** HeapSize *
 *
 * Description: getting the number of elements of a heap
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: returns the number of elements in a heap
 *
 * Complexity: Time: O(1) Space: O(1)
 *
 ******************************************************************************/
size_t HeapSize(const heap_t* heap);

/****************************************************************** HeapRemove *
 *
 * Description: finding the first elenment in a heap that is equal to
 *              `param` by a standard provided by the user in a given range,
 *              and removing it from the heap
 *
 * Arguments: heap: pointer to Non NULL heap
 *            is_match_func : comparison function provided by the user, should return
 *                           1 if the data is equal and 0 otherwise
 *            param: the param we are trying to remove
 *
 * Return: the data of the erased element, if not found it will return NULL
 *
 * Complexity: Time: O(n) Space: O(1)
 *
 ******************************************************************************/
void* HeapRemove(heap_t* heap,
               int (*IsMatch)(const void* data, const void* param),
               void* param);

/**************************************************************** *
 * Description: removing all of the elemnts from a heap
 *
 * Arguments: heap: pointer to Non NULL heap
 *
 * Return: void
 *
 * Complexity: Time: O(n) Space: O(1)
 ******************************************************************************/
void HeapClear(heap_t *heap);

#endif/**************************************************** End of __HEAP_H__ */