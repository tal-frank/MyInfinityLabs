#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/doubly_linked_list.h"

typedef struct Dll_Node dnode_t;

struct Dll_Iterator
{
	dnode_t* dnode;
};

struct Doubly_linked_list
{
	dnode_t* head;
	dnode_t* tail;
};

struct Dll_Node
{
	dnode_t* next;
	dnode_t* prev;
	void* data;
};


static dnode_t* IterToNode(dll_iter_t iter)
{
	return iter->dnode;
}


static dll_iter_t NodeToIter(dnode_t* dnode)
{
	dll_iter_t iter = 0;
	iter->dnode = dnode;
	return iter;
}


dll_t* DllCreate(void)
{
	dll_t* dll = (dll_t*)malloc(sizeof(dll_t));
	dnode_t* dummy = (dnode_t*)malloc(sizeof(dnode_t));
	if (NULL == dll)
	{
		return NULL;
	}
	if (NULL == dummy)
	{
		free(dll);
		return NULL;
	}
	
	dummy->prev = NULL;
	dummy->next = NULL;
	dummy->data = dll;
	dll->head = dummy;
	dll->tail = dummy;
	
	return dll;
}

dll_iter_t DllBegin(const dll_t* dll)
{
	assert(NULL != dll);
	
	return NodeToIter(dll->head);
}


dll_iter_t DllEnd(const dll_t* dll)
{
	assert(NULL != dll);
	
	return NodeToIter(dll->tail);
}


size_t DllCount(const dll_t* dll)
{
	return 1UL;
}



int main()
{
	return 0;
}

