/**********************
* hash table
* Author: Tal Frank
* Reviewer: Ori Yoseph
* Last update: 14/06/2026
**********************/

#include <stdio.h> /* NULL */
#include <stdlib.h> /* malloc , free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "c_hash_table.h"
#include "doubly_linked_list.h"

#define TRUE (1)
#define FALSE (0)

#define FAILURE (1)
#define SUCCESS (0)

/*---------------------------------------------------------*/
/************************* STRUCTS *************************/
/*---------------------------------------------------------*/

struct Hash_table
{
	size_t table_size;
	size_t (*hash_func)(const void* key);
	int (*cmp_func)(const void* key1, const void* key2);
	dll_t** buckets;
};

typedef struct compare_function_plus_key
{
	void* key;
	hash_t* hash;
}comp_func_plus_key_t;

typedef struct action_function_plus_key
{
	void* param;
	int (*act_func)(void* data, void* param);
}act_func_plus_key_t;

typedef struct Hash_pair
{
	void* key;
	void* value;
}pair_t;

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static int CmpFuncWrapper(const void* data, const void* param);
static int ActFuncWrapper(void* data, void* param);

/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

hash_t* HashCreate(size_t table_size, 
						  size_t (*hash_func)(const void* key), 
						  int (*cmp_func)(const void* key1, const void* key2))
{
	hash_t* hash = (hash_t*)malloc(sizeof(hash_t));
	if (NULL == hash)
	{
		return NULL;
	}

	assert(NULL != hash_func);
	assert(NULL != cmp_func);
	
	hash->buckets = (dll_t**)calloc(table_size, sizeof(dll_t*));
	if (NULL == hash->buckets)
	{
		free(hash);
		hash = NULL;
		return NULL;
	}
	hash->table_size = table_size;
	hash->hash_func = hash_func;
	hash->cmp_func = cmp_func;
	
	return hash;
}

void HashDestroy(hash_t* hash)
{
	size_t i = 0;
	dll_iter_t iter = 0;
	dll_iter_t end = 0;
	
	assert(NULL != hash);

	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->buckets[i])
		{
			iter = DllBegin(hash->buckets[i]);
			end = DllEnd(hash->buckets[i]);
			while (!DllIsIterEqual(iter, end))
			{
				free((pair_t*)DllGetData(iter));
				iter = DllGetNext(iter);
			}
			DllDestroy(hash->buckets[i]);
			hash->buckets[i] = NULL;
		}
	}
	free(hash->buckets);
	hash->buckets = NULL;
	free(hash);
	hash = NULL;
}

/*-----------------------------------------------------------------*/
/************************* INSERT & REMOVE *************************/
/*-----------------------------------------------------------------*/

int HashInsert(hash_t* hash, void* data, const void* key)
{
	size_t index = 0;
	dll_iter_t iter = 0;
	pair_t* pair = (pair_t*)malloc(sizeof(pair_t));
	if (NULL == pair)
	{
		return FAILURE;
	}
	
	assert(NULL != hash);

	index = (hash->hash_func(key) % hash->table_size);
	if (NULL == hash->buckets[index])
	{
		hash->buckets[index] = DllCreate();
		if (NULL == hash->buckets[index])
		{
			free(pair);
			pair = NULL;
			return FAILURE;
		}
	}
	
	iter = DllBegin(hash->buckets[index]);
	
	pair->key = (void*)key;
	pair->value = data;
	if(DllIsIterEqual(DllEnd(hash->buckets[index]),
		DllInsert(hash->buckets[index], iter, pair)))
	{
		free(pair);
		pair = NULL;
		return FAILURE;
	}
	
	return SUCCESS;
}

void HashRemove(hash_t* hash, const void* key)
{
	size_t index = hash->hash_func(key) % hash->table_size;
	dll_iter_t element_to_remove_iter = 0;
	pair_t* pair = NULL;
	comp_func_plus_key_t comp_key = {0};

	assert(NULL != hash);

	if (NULL == hash->buckets[index])
	{
		return;
	}

	comp_key.key = (void*)key;
	comp_key.hash = hash;
	
	element_to_remove_iter = DllFind(DllBegin(hash->buckets[index]), 
					  DllEnd(hash->buckets[index]), 
					  CmpFuncWrapper, 
					  &comp_key);
	if (!DllIsIterEqual(element_to_remove_iter, DllEnd(hash->buckets[index])))
	{
		pair = (pair_t*)DllGetData(element_to_remove_iter);
		free(pair);
		pair = NULL;
		DllRemove(element_to_remove_iter);
	}
}

/*-----------------------------------------------------------------*/
/************************* FIND & FOR EACH *************************/
/*-----------------------------------------------------------------*/

void* HashFind(hash_t* hash, const void* key)
{
	pair_t* element = {0};
	size_t index = hash->hash_func(key) % hash->table_size;
	dll_iter_t element_to_find = 0;
	comp_func_plus_key_t comp_key = {0};
	
	assert(NULL != hash);

	if (NULL == hash->buckets[index])
	{
		return NULL;
	}
	
	comp_key.key = (void*)key;
	comp_key.hash = hash;
	
	element_to_find = DllFind(DllBegin(hash->buckets[index]), 
			  		  DllEnd(hash->buckets[index]), 
			  		  CmpFuncWrapper, 
			  		  &comp_key);
	if (DllIsIterEqual(DllEnd(hash->buckets[index]), element_to_find))
	{
		return NULL;
	}

	element = (pair_t*)DllGetData(element_to_find);
	if (DllIsIterEqual(DllEnd(hash->buckets[index]),
					   DllPushFront(hash->buckets[index], element)))
	{
		return element->value;
	}
	DllRemove(element_to_find);
	return element->value;
}

int HashForEach(hash_t* hash, int(*act_func)(void* data, void* param), void* param)
{
	size_t i = 0;
	dll_iter_t begin = 0;
	dll_iter_t end = 0;
	act_func_plus_key_t act_key = {0};

	assert(NULL != hash);
	assert(NULL != act_func);

	act_key.param = (void*)param;
	act_key.act_func = act_func;

	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->buckets[i])
		{
			begin = DllBegin(hash->buckets[i]);
			end = DllEnd(hash->buckets[i]);
			DllForEach(begin, end, ActFuncWrapper, &act_key);
		}
	}

	return SUCCESS;
}

/*------------------------------------------------------------------*/
/************************* IS EMPTY & COUNT *************************/
/*------------------------------------------------------------------*/

int HashIsEmpty(const hash_t* hash)
{	
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->buckets[i] && !DllIsEmpty(hash->buckets[i]))
		{
			return FALSE;
		}
	}
	return TRUE;
}

size_t HashCount(const hash_t* hash)
{
	size_t cnt = 0;
	size_t i = 0;

	assert(NULL != hash);

	for (i = 0; i < hash->table_size; ++i)
	{
		if (NULL != hash->buckets[i])
		{
			cnt += DllCount(hash->buckets[i]);
		}
	}
	return cnt;
}

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static int CmpFuncWrapper(const void* data, const void* param)
{
	comp_func_plus_key_t* comp_key = (comp_func_plus_key_t*)param;
	pair_t* pair = (pair_t*)data;
	
	return comp_key->hash->cmp_func(pair->key, comp_key->key);
}

static int ActFuncWrapper(void* data, void* param)
{
	act_func_plus_key_t* act_key = (act_func_plus_key_t*)param;
	pair_t* pair = (pair_t*)data;
	
	return act_key->act_func(pair->key, act_key->param);
}
