/**********************
* heap
* Author: Tal Frank
* Reviewer: Or Zellner
* Last update: 25/06/2026
**********************/

#include <stdlib.h> /* malloc , free */
#include <assert.h>

#include "heap.h"
#include "dynamic_vector.h"

#define WORD_SIZE (sizeof(size_t))
#define ROOT (0)
#define THREE_ELEMENTS (3)

enum
{
    FAILURE = -1,
    SUCCESS
};

struct Heap
{
    dvector_t* dvector;
    int (*cmp_func)(const void* key1, const void* key2);
};

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static void SwapElements(void** element1, void** element2);
static void HeapifyDown(heap_t* heap, size_t index);
static void HeapifyUp(heap_t* heap, size_t index);
static size_t GetLeftChild(size_t index);
static size_t GetRightChild(size_t index);
static size_t GetParent(size_t index);
static int compare_nodes(heap_t* heap, size_t index1, size_t index2);

/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

heap_t* HeapCreate(int (*cmp_func)(const void* key1, const void* key2))
{
    size_t initial_capacity = THREE_ELEMENTS;
    heap_t* heap = NULL;

    assert(NULL != cmp_func);

    heap = (heap_t*)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->dvector = DvectorCreate(initial_capacity, WORD_SIZE);
    if (NULL == heap->dvector)
    {
        free(heap);
        heap = NULL;
        return NULL;
    }
    
    heap->cmp_func = cmp_func;
    return heap;
}

void HeapDestroy(heap_t* heap)
{
    assert(NULL != heap);

    DvectorDestroy(heap->dvector);
    heap->dvector = NULL;
    
    heap->cmp_func = NULL;
    free(heap);
    heap = NULL;
}

/*-------------------------------------------------------------------*/
/************************* PUSH & POP & PEEK *************************/
/*-------------------------------------------------------------------*/

int HeapPush(heap_t* heap, void* data)
{
    size_t index = 0;

    assert(NULL != heap);
    
    if (FAILURE == DvectorPush(heap->dvector, &data))
    {
        return FAILURE;
    }
    
    index = DvectorSize(heap->dvector) - 1;
    if (0 == index)
    {
        return SUCCESS;
    }

    HeapifyUp(heap, index);

    return SUCCESS;
}


void HeapPop(heap_t* heap)
{
    assert(NULL != heap);

    HeapifyDown(heap, ROOT);
}

void* HeapPeek(const heap_t* heap)
{
    assert(NULL != heap);

    return *(void**)DvectorGetAccessToElement(heap->dvector, 0);
}

/*-----------------------------------------------------------------*/
/************************* IS EMPTY & SIZE *************************/
/*-----------------------------------------------------------------*/

int HeapIsEmpty(const heap_t* heap)
{
    assert(NULL != heap);

    return (0 == DvectorSize(heap->dvector));
}


size_t HeapSize(const heap_t* heap)
{
    assert(NULL != heap);

    return DvectorSize(heap->dvector);
}

/*----------------------------------------------------------------*/
/************************* REMOVE & CLEAR *************************/
/*----------------------------------------------------------------*/

void* HeapRemove(heap_t* heap,
               int (*IsMatch)(const void* data, const void* param),
               const void* param)
{
    size_t is_match = 0;
    size_t i = 0;
    size_t to_remove_index = 0;
    size_t num_of_elements = 0;
    void* data = NULL;
    
    assert(NULL != heap);
    assert(NULL != IsMatch);

    num_of_elements = DvectorSize(heap->dvector);
    for (i = 0; !is_match && i < num_of_elements; ++i)
    {
        is_match = IsMatch(*(void**)DvectorGetAccessToElement(heap->dvector, i), param);
        to_remove_index = i;
    }
    if (!is_match)
    {
        return NULL;
    }
    data = *(void**)DvectorGetAccessToElement(heap->dvector, to_remove_index);
    HeapifyDown(heap, to_remove_index);

    return data;
}

void HeapClear(heap_t *heap)
{
    assert(NULL != heap);

    while (0 != DvectorSize(heap->dvector))
    {
        DvectorSafePop(heap->dvector);
    }
}

/*---------------------------------------------------------------------------*/
/************************* HEAPIFY UP & HEAPIFY DOWN *************************/
/*---------------------------------------------------------------------------*/

static void HeapifyUp(heap_t* heap, size_t index)
{
    size_t parent_index = GetParent(index);
    
    assert(NULL != heap);

    while ((0 != index) && (0 > compare_nodes(heap, index, parent_index)))
    {
        SwapElements(DvectorGetAccessToElement(heap->dvector, index),
                     DvectorGetAccessToElement(heap->dvector, parent_index));
        
        index = parent_index;
        parent_index = GetParent(index);
    }
}

static void HeapifyDown(heap_t* heap, size_t index)
{
    size_t left_child = GetLeftChild(index);
    size_t right_child = GetRightChild(index);
    size_t child_to_swap = 0;
    size_t size = 0;

    assert(NULL != heap);

    SwapElements(DvectorGetAccessToElement(heap->dvector, index),
                 DvectorGetAccessToElement(heap->dvector, DvectorSize(heap->dvector) - 1));
    DvectorSafePop(heap->dvector);
    size = DvectorSize(heap->dvector);

    while(left_child < size)
    {
        if (right_child < size)
        {

            child_to_swap = 0 > compare_nodes(heap, left_child, right_child)
                                ? left_child : right_child;
            
            if (0 < compare_nodes(heap, index, child_to_swap))
            {
                SwapElements(DvectorGetAccessToElement(heap->dvector, index),
                             DvectorGetAccessToElement(heap->dvector, child_to_swap));
            }                                    
        }

        else
        {
            if (0 < compare_nodes(heap, index, left_child))
            {
                child_to_swap = left_child;
                SwapElements(DvectorGetAccessToElement(heap->dvector, index),
                             DvectorGetAccessToElement(heap->dvector, child_to_swap));
            }
            return;
        }
     
        index = child_to_swap;
        left_child = GetLeftChild(index);
        right_child = GetRightChild(index);
    }
}

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static void SwapElements(void** element1, void** element2)
{
    void* temp = 0;
    
    temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

static size_t GetLeftChild(size_t index)
{
    return (index * 2 + 1);
}

static size_t GetRightChild(size_t index)
{
    return (index * 2 + 2);
}

static size_t GetParent(size_t index)
{
    return ((index - 1) / 2);
}

static int compare_nodes(heap_t* heap, size_t index1, size_t index2)
{
    return heap->cmp_func(*(void**)DvectorGetAccessToElement(heap->dvector, index1),
                          *(void**)DvectorGetAccessToElement(heap->dvector, index2));
}