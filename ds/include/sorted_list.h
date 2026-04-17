#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

typedef struct Sorted_list sorted_list_t;
typedef struct SortedListIter sorted_list_iter_t;

struct SortedListIter
{
	dll_iter_t inner_iter;
	#ifndef NDEBUG
	    	sorted_list_t* list;
	#endif /*NDEBUG*/				
};
/*****************************************************************
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
sorted_list_t* SortedListCreate(int (*cmp_func)(const void* param1, const void* param2));

void SortedListDestroy(sorted_list_t* sl);

sorted_list_iter_t SortedListInsert(sorted_list_t* sl, const void* data);

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

sorted_list_iter_t SortedListFind(const sorted_list_t* sl,
                                sorted_list_iter_t from,
                                sorted_list_iter_t to,
                                const void* param);

/*
taking out all from src and putting in dest
*/           
void SortedListMerge(sorted_list_t* dest, sorted_list_t* src);

sorted_list_iter_t SortedListBegin(const sorted_list_t* sl);

sorted_list_iter_t SortedListEnd(const sorted_list_t* sl);

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*is_match_func)(const void* param1, const void* param2)
                                    const void* param);

/*return the data of the removed iterator*/
void* SortedListPopBack(sorted_list_t* sl);

/*return the data of the removed iterator*/
void* SortedListPopFront(sorted_list_t* sl);

int SortedListIsIterEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter1);

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

void* SortedListGetData(sorted_list_iter_t iter);

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from,
                                    sorted_list_iter_t to,
                                    int (*action func)(void* data, void* param)
                                    void* param);
                                    
int SortedListIsEmpty(const sorted_list_t* sorted_list);

size_t SortedListSize(const sorted_list_t* sorted_list);


#endif 

