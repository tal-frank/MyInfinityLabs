#ifndef __HEAP_H__
#define __HEAP_H__

/********************************************************* Standard libraries */

#include <stddef.h>

/******************************************************************* Typedefs */

typedef struct Heap heap_t;

/************************************************************** API functions */

/****************************************************************** HeapCreate *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
heap_t* HeapCreate(int (*cmp_func)(const void* key1, const void* key2));

/***************************************************************** HeapDestroy *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
void HeapDestroy(heap_t* heap);

/******************************************************************** HeapPush *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
int HeapPush(heap_t* heap, void* data);

/********************************************************************* HeapPop *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
void HeapPop(heap_t* heap);

/******************************************************************** HeapPeek *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
void* HeapPeek(const heap_t* heap);

/***************************************************************** HeapIsEmpty *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
int HeapIsEmpty(const heap_t* heap);

/******************************************************************** HeapSize *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
size_t HeapSize(const heap_t* heap);

/****************************************************************** HeapRemove *
 * 		
 * Description: 
 *		
 *   Arguments: 
 *		
 *      Return: 
 *		
 *  Complexity: Time: O() Space: O()
 *		
 ******************************************************************************/
void* HeapRemove(heap_t* heap,
               int (*IsMatch)(void* data, void* param),
               void* param);


#endif/**************************************************** End of __HEAP_H__ */