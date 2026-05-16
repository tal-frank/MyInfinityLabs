/**********************
* fixed size allocator
* Author: Tal Frank
* Reviewer: Or Zelner
* Last update: 12/05/2026
**********************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fixed_size_allocator.h"

#define WORD_SIZE (sizeof(size_t)) 
#define FIRST ((sizeof(fsa_t)) / WORD_SIZE)
#define LAST (0)

struct Fixed_memory_allocator_type
{
    size_t offset_to_next_free;
};

/*------------------------------------------------------------------------------------------------*/
/********************************** STATIC FUNCTION DECLARATIONS **********************************/
/*------------------------------------------------------------------------------------------------*/

static void AlignBlockSize(size_t* block_size);


/*--------------------------------------------------------------------------------*/
/********************************** SUGGEST SIZE **********************************/
/*--------------------------------------------------------------------------------*/

size_t FSASuggestSize(size_t block_size, size_t num_blocks)
{
	AlignBlockSize(&block_size);
	
	return (block_size * num_blocks) + sizeof(fsa_t);
}

/*-----------------------------------------------------------------------------*/
/********************************** INIT SIZE **********************************/
/*-----------------------------------------------------------------------------*/

fsa_t* FSAInit(void* mp, size_t pool_size, size_t block_size)
{
	fsa_t* fsa = NULL;
	size_t* mem_pool = (size_t*)mp;
	size_t offset = sizeof(fsa_t) / WORD_SIZE;
	size_t jump = 0;
	
	assert(NULL != mp);
	
	fsa = (fsa_t*)mem_pool;
	if (WORD_SIZE * offset > pool_size)
	{
		fsa->offset_to_next_free = LAST;
		return fsa;
	}
	fsa->offset_to_next_free = offset;
	
	AlignBlockSize(&block_size);
	jump = block_size / WORD_SIZE;
	while ((WORD_SIZE * (offset + jump)) < pool_size)
	{
		mem_pool[offset] = offset + jump;
		offset += jump;
	}
	mem_pool[offset] = LAST;
	
	return fsa;
}

/*-------------------------------------------------------------------------------------*/
/********************************** ALLOCATION & FREE **********************************/
/*-------------------------------------------------------------------------------------*/

void* FSAAlloc(fsa_t* mp)
{
	size_t next_free = mp->offset_to_next_free;
	
	assert(NULL != mp);
	
	if (LAST == mp->offset_to_next_free)
	{
		return NULL;
	}
	mp->offset_to_next_free = *((size_t*)(mp) + mp->offset_to_next_free);
	
	return mp + next_free;
}


void FSAFree(fsa_t* mp, void* block)
{
	fsa_t* free_block = (fsa_t*)block;
	size_t old_offset = 0;
	
	assert(NULL != mp);
	
	old_offset = mp->offset_to_next_free;
	
	if (NULL == block)
	{
		return;
	}
	
	mp->offset_to_next_free = (size_t)(free_block - mp);
	free_block->offset_to_next_free = old_offset;
}

/*-------------------------------------------------------------------------*/
/********************************** COUNT **********************************/
/*-------------------------------------------------------------------------*/

size_t FSACountFree(const fsa_t* mp)
{
	size_t count = 0;
	size_t free_block_runner = mp->offset_to_next_free;
	
	assert(NULL != mp);
	
	while(LAST != free_block_runner)
	{
		free_block_runner = *((size_t*)(mp) + free_block_runner);
		++count;
	}
	
	return count;
}

/*--------------------------------------------------------------------------*/
/********************************** STATIC **********************************/
/*--------------------------------------------------------------------------*/

static void AlignBlockSize(size_t* block_size)
{
	*block_size = (0 == *block_size % WORD_SIZE) ? *block_size : WORD_SIZE * (1 + *block_size / WORD_SIZE);
}


