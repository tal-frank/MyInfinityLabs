#include <stdlib.h> /* malloc , free */
#include <assert.h>

#include "heap.h"
#include "dynamic_vector.h"

#define WORD_SIZE (sizeof(size_t))
#define ROOT (0)

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

static void SwapElements(size_t* element1, size_t* element2);
static void HeapifyDown(heap_t* heap, size_t index);
static void HeapifyUp(heap_t* heap, size_t index);

heap_t* HeapCreate(int (*cmp_func)(const void* key1, const void* key2))
{
    size_t initial_capacity = 3;
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
    DvectorDestroy(heap->dvector);
    heap->dvector = NULL;
    
    free(heap);
    heap = NULL;
}

int HeapPush(heap_t* heap, void* data)
{
    size_t index = 0;

    assert(NULL != heap);
    
    if (FAILURE == DvectorPush(heap->dvector, data))
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

    return DvectorGetAccessToElement(heap->dvector, 0);
}


int HeapIsEmpty(const heap_t* heap)
{
    assert(NULL != heap);

    return 0 == DvectorSize(heap->dvector);
}


size_t HeapSize(const heap_t* heap)
{
    assert(NULL != heap);

    return DvectorSize(heap->dvector);
}


void* HeapRemove(heap_t* heap,
               int (*IsMatch)(const void* data, const void* param),
               void* param)
    {
        size_t is_match = 0;
        size_t i = 0;
        size_t to_remove_index = 0;
        size_t num_of_elements = DvectorSize(heap->dvector);
        void* data = NULL;
        
        for (i = 0; !is_match && i < num_of_elements; ++i)
        {
            is_match = IsMatch(DvectorGetAccessToElement(heap->dvector, i), param);
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

static void HeapifyUp(heap_t* heap, size_t index)
{
    size_t parent_index = (index - 1) / 2;
    
    while (0 != index &&
           0 > heap->cmp_func(DvectorGetAccessToElement(heap->dvector, index),
                              DvectorGetAccessToElement(heap->dvector, parent_index)))
    {
        SwapElements((size_t*)DvectorGetAccessToElement(heap->dvector, index),
                     (size_t*)DvectorGetAccessToElement(heap->dvector, parent_index));
        
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

static void HeapifyDown(heap_t* heap, size_t index)
{
    size_t left_child = index * 2 + 1;
    size_t right_child = index * 2 + 2;
    size_t child_to_swap = 0;
    size_t size = 0;
    SwapElements((size_t*)DvectorGetAccessToElement(heap->dvector, index),
                 (size_t*)DvectorGetAccessToElement(heap->dvector, DvectorSize(heap->dvector) - 1));
    DvectorPop(heap->dvector);
    size = DvectorSize(heap->dvector);

    while(left_child < size)
    {
        if (right_child < size)
        {
            child_to_swap = 0 > heap->cmp_func(DvectorGetAccessToElement(heap->dvector, 
                                                                         left_child),
                                               DvectorGetAccessToElement(heap->dvector, 
                                                                         right_child))
                                ? left_child : right_child;
        }

        else
        {
            if (0 < heap->cmp_func(DvectorGetAccessToElement(heap->dvector, index),
                                   DvectorGetAccessToElement(heap->dvector, left_child)))
            {

                child_to_swap = left_child;
                SwapElements((size_t*)DvectorGetAccessToElement(heap->dvector, index),
                             (size_t*)DvectorGetAccessToElement(heap->dvector, child_to_swap));
            }
            return;
        }

        SwapElements((size_t*)DvectorGetAccessToElement(heap->dvector, index),
                     (size_t*)DvectorGetAccessToElement(heap->dvector, child_to_swap));
        
        index = child_to_swap;
        left_child = index * 2 + 1;
        right_child = index * 2 + 2;
    }
}

static void SwapElements(size_t* element1, size_t* element2)
{
    size_t temp = 0;
    
    temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}