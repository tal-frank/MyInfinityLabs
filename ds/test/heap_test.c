#include <stdio.h>
#include <stddef.h>

#include "dynamic_vector.h"
#include "heap.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

struct Heap
{
    dvector_t* dvector;
    int (*cmp_func)(const void* key1, const void* key2);
};

static int num1 = 1;
static int num2 = 2;
static int num3 = 3;
static int num4 = 4;
static int num5 = 5;
static int num6 = 6;
static int num7 = 7;
static int num8 = 8;
static int num9 = 9;
static int num10 = 10;

static void PrintSpaces(size_t num)
{
      size_t i = 0;

      for (i = 0 ; i < num ; ++i)
      {
            printf(" ");
      }
}

static void PrintHeap(heap_t* heap)
{
    size_t size = 0;
    size_t total_levels = 0;
    size_t current_level = 0;
    size_t i = 0;
    size_t nodes_on_level = 1;
    size_t printed_on_level = 0;
    size_t temp_size = 0;
    size_t leading_spaces = 0;
    size_t between_spaces = 0;
    int p_data = 0;

    size = DvectorSize(heap->dvector);
    if (0 == size)
    {
        printf("The heap is empty, my lord.\n");
        return;
    }

    /* 1. Calculate total number of levels using bitwise right shift */
    temp_size = size;
    while (temp_size > 0)
    {
        ++total_levels;
        temp_size >>= 1; 
    }

    printf("Your Heap, my lord:\n\n");

    /* 2. Print the tree level by level */
    for (i = 0; i < size; ++i)
    {
        /* If at the start of a new level, print the leading spaces */
        if (printed_on_level == 0)
        {
            leading_spaces = (1 << (total_levels - current_level)) - 2;
            PrintSpaces(leading_spaces);
        }

        /* Get and print the current element */
        p_data = **(int**)DvectorGetAccessToElement(heap->dvector, i);
        printf("%2d", p_data);
        
        ++printed_on_level;

        /* If the level isn't finished, print between-node spacing */
        if (printed_on_level < nodes_on_level && (i + 1) < size)
        {
            between_spaces = (1 << (total_levels - current_level + 1)) - 2;
            PrintSpaces(between_spaces);
        }

        /* If we've reached the end of the current level, move to the next row */
        if (printed_on_level == nodes_on_level)
        {
            printf("\n\n"); 
            ++current_level;
            nodes_on_level <<= 1; 
            printed_on_level = 0;
        }
    }
    
    /* Final newline safety check if the last level wasn't completely filled */
    if (printed_on_level != 0)
    {
        printf("\n\n");
    }
}

int CmpFunc(const void* num1, const void* num2)
{
    int number1 = *(int*)num1;
    int number2 = *(int*)num2;

    return number1 - number2;
}

int IsMatch(const void* num1, const void* num2)
{
    int number1 = *(int*)num1;
    int number2 = *(int*)num2;

    return number1 == number2;
}

void IsEmptyTest(void)
{
    heap_t* heap = HeapCreate(CmpFunc);

    printf(CYAN "IS EMPTY TEST\n" RESET_COLOR);
    if (!HeapIsEmpty(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
		printf("get not empty although is empty\n\n");
		HeapDestroy(heap);
		return;
    }
    printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty is working\n\n");

    HeapPush(heap, &num1);

    if (HeapIsEmpty(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
		printf("get empty although is not empty\n\n");
		HeapDestroy(heap);
		return;
    }
    printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty is working\n\n");

    HeapDestroy(heap);
}

void InsertPopTest(void)
{
    heap_t* heap = HeapCreate(CmpFunc);
    int i = 0;

    printf(CYAN "INSERT AND POP TEST\n" RESET_COLOR);

    HeapPush(heap, &num3);
    HeapPush(heap, &num1);
    HeapPush(heap, &num8);
    HeapPush(heap, &num6);
    HeapPush(heap, &num2);
    HeapPush(heap, &num10);
    HeapPush(heap, &num4);
    HeapPush(heap, &num5);
    HeapPush(heap, &num7);
    HeapPush(heap, &num9);
    PrintHeap(heap);
    
    for (i = 1; i < 11; ++i)
    {
        if(i != *(int*)HeapPeek(heap))
        {
            printf(RED "---FAIL---\n" RESET_COLOR);
		    printf("insert/empty does not work correctly\n");
            printf("expected : %d\nactual :%d\n\n", i, *(int*)HeapPeek(heap));
            HeapDestroy(heap);
            return;
        }
        HeapPop(heap);
    }
    
    printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("insert and pop are working\n\n");

    HeapDestroy(heap);
}

void SizeRemoveTest(void)
{
    heap_t* heap = HeapCreate(CmpFunc);
    int removed_element = 0;

    printf(CYAN "SIZE TEST\n" RESET_COLOR);

    if (0 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 0\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    HeapPush(heap, &num3);
    if (1 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 1\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    HeapPush(heap, &num1);
    if (2 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 2\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    HeapPush(heap, &num8);
    if (3 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 3\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    HeapPush(heap, &num6);
    if (4 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 4\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    HeapPush(heap, &num2);
    if (5 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("size does not work correctly\n");
        printf("expected : 5\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }
    printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("size is working\n\n");

    printf(CYAN "REMOVE TEST\n" RESET_COLOR);
    
    removed_element = *(int*)HeapRemove(heap, IsMatch, &num6);
    
    if (4 != HeapSize(heap))
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("remove does not work correctly\n");
        printf("size expected : 4\nactual :%ld\n\n", HeapSize(heap));
        HeapDestroy(heap);
        return;
    }

    if (6 != removed_element)
    {
        printf(RED "---FAIL---\n" RESET_COLOR);
        printf("remove does not work correctly\n");
        printf("element expected : 6\nactual :%d\n\n", removed_element);
        HeapDestroy(heap);
        return;
    }

    printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("size is working\n\n");

    HeapDestroy(heap);
}

int main()
{
    printf("\n");

    IsEmptyTest();
    InsertPopTest();
    SizeRemoveTest();

    printf("\n");
    return 0;
}