/**********************
* fixed size allocator
* Author: Tal Frank
* Reviewer: Or Zelner
* Last update: 12/05/2026
**********************/

#include <stddef.h> /* size_t */

#include "fixed_size_allocator.h"

#define WORD_SIZE (sizeof(size_t)) 
#define FIRST (sizeof(fsa_t) / WORD_SIZE)
#define LAST (0)

struct Fixed_memory_allocator_type
{
    size_t offset;
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
	while(0 != block_size % WORD_SIZE)
	{
		++block_size;
	}
	
	return (block_size * num_blocks) + sizeof(fsa_t);
}

/*-----------------------------------------------------------------------------*/
/********************************** INIT SIZE **********************************/
/*-----------------------------------------------------------------------------*/

fsa_t* FSAInit(void* mp, size_t pool_size, size_t block_size)
{
	fsa_t* fsa = {0};
	size_t* mem_pool = mp;
	size_t offset = sizeof(fsa_t) / WORD_SIZE;
	
	fsa = (fsa_t*)mem_pool;
	fsa->offset = FIRST;
	
	AlignBlockSize(&block_size);
	while ((WORD_SIZE * offset) < pool_size)
	{
		mem_pool[offset] = offset + block_size / WORD_SIZE;
		offset += block_size / WORD_SIZE;
	}
	mem_pool[offset] = LAST;
	
	return fsa;
}

/*-------------------------------------------------------------------------------------*/
/********************************** ALLOCATION & FREE **********************************/
/*-------------------------------------------------------------------------------------*/

void* FSAAlloc(fsa_t* mp)
{
	size_t old_offset = mp->offset;
	
	mp->offset = *((size_t*)(mp) + mp->offset);
	if (LAST == mp->offset)
	{
		return NULL;
	}
	
	return mp + old_offset;
}

void FSAFree(fsa_t* mp, void* block)
{
	
	fsa_t* free_block = (fsa_t*)block;
	size_t old_offset = mp->offset;
	
	mp->offset = (size_t)(free_block - mp);
	free_block->offset = old_offset;
}

/*-------------------------------------------------------------------------*/
/********************************** COUNT **********************************/
/*-------------------------------------------------------------------------*/

size_t FSACountFree(const fsa_t* mp)
{
	size_t count = 0;
	size_t free_block_runner = mp->offset;
	
	while(LAST != free_block_runner)
	{
		free_block_runner = *((size_t*)(mp) + free_block_runner);
		++count;
	}
	
	return count - 1;
}

/*--------------------------------------------------------------------------*/
/********************************** STATIC **********************************/
/*--------------------------------------------------------------------------*/

static void AlignBlockSize(size_t* block_size)
{
	while(0 != *block_size % WORD_SIZE)
	{
		++(*block_size);
	}
}


