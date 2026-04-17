
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/sorted_list.h"
#include "../include/doubly_linked_list.h"

struct Sorted_list sorted_list
{
	dll_t* dll;
	int (*cmp_func)(const void* param1, const void* param2);
};

sorted_list_t* SortedListCreate(int (*cmp_func)(const void* param1, const void* param2))
{
	sorted_list_t* sorted_list = (sorted_list_t*)malloc(sizeof(sorted_list));
	if (NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->dll = DllCreate();
	if (NULL == sorted_list->dll)
	{
		free(sorted_list)
		return NULL;
	}
	
	sorted_list->cmp_func = cmp_func;
	
	return sorted_list; 
}


void SortedListDestroy(sorted_list_t* sl)
{
	DllDestroy(si->dll);
	free(sl);
}


sorted_list_iter_t SortedListBegin(const sorted_list_t* sl);
{
	assert(NULL != sl);	
	
	return DllBegin(sl->dll);
}


sorted_list_iter_t SortedListEnd(const sorted_list_t* sl);
{
	assert(NULL != sl);	
	
	return DllEnd(sl->dll);
}


int SortedListIsEmpty(const sorted_list_t* sorted_list);
{
	assert(NULL != sorted_list);
	
	return DllIsEmpty(sorted_list->dll);
}


sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

void* SortedListGetData(sorted_list_iter_t iter);

void* SortedListPopBack(sorted_list_t* sl);

void* SortedListPopFront(sorted_list_t* sl);

int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter1);

sorted_list_iter_t SortedListInsert(sorted_list_t* sl, const void* data);

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

size_t SortedListSize(const sorted_list_t* sorted_list);

sorted_list_iter_t SortedListFind(const sorted_list_t* sl,
                                sorted_list_iter_t from,
                                sorted_list_iter_t to,
                                const void* param);
          
void SortedListMerge(sorted_list_t* dest, sorted_list_t* src);

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*is_match_func)(const void* param1, const void* param2)
                                    const void* param);

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*action func)(void* data, void* param)
                                    void* param);
                                    

int main()
{
	return 0;
}

