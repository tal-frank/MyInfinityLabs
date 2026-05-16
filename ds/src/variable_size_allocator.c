/**********************
* Variable size allocator
* Author: Tal Frank
* Reviewer: Almog Nimni
* Last update: 15/05/2026
**********************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "variable_size_allocator.h"

#define WORD_SIZE (sizeof(size_t))
#define HEADER_SIZE (sizeof(vsa_t))
#define BYTE_SIZE (sizeof(char))
#define END (0)
#define DEFRAG_SUCCESS (1)
#define DEAD_BEEF (0xDEADBEEF)

/*----------------------------------------------------------------*/
/************************* STRUCTS & ENUMS*************************/
/*----------------------------------------------------------------*/

struct Variable_size_allocator_t
{
#ifndef NDEBUG
	size_t deadbeef;
#endif	
	size_t offset;	
};

enum
{
	NOT_ALLOCATED = 0,
	ALLOCATED
};


/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLERATIONS *************************/
/*-------------------------------------------------------------------------------*/

#ifndef NDEBUG
static void SetDeadBeef(vsa_t* vsa);
#endif
static void UpdateNextHeader(vsa_t* vsa, size_t full_size_seg);
static void GetAlignSegmentSize(size_t* n_bytes);
static void AlignPool(void* pool, size_t* p_size);
static size_t IsAllocated(vsa_t* vsa);
static size_t GetOffset(vsa_t* vsa);
static void SetToAllocated(vsa_t* vsa);
static void SetToFree(vsa_t* vsa);
static void SetOffset(vsa_t* vsa, size_t n_bytes);
static int DeFrag(vsa_t* vsa);

/*------------------------------------------------------*/
/************************* INIT *************************/
/*------------------------------------------------------*/

vsa_t* VSAInit(void* pool, size_t p_size)
{
	vsa_t pool_start = {0};
	vsa_t pool_end = {0};
	vsa_t* vsa = (vsa_t*)pool;
	vsa_t* vsa_end = NULL;
	
	AlignPool(vsa, &p_size);

	pool_start.offset = (((p_size - (HEADER_SIZE)) / WORD_SIZE) << 1);
	pool_end.offset = END;
	SetToAllocated(&pool_end);

#ifndef NDEBUG
	pool_start.deadbeef = DEAD_BEEF;
	pool_end.deadbeef = DEAD_BEEF;
#endif		
	
	*vsa = pool_start;
	vsa_end = (vsa_t*)((size_t*)vsa + (p_size - HEADER_SIZE) / WORD_SIZE);
	*vsa_end = pool_end;
		
	return vsa;
}

/*-------------------------------------------------------*/
/************************* ALLOC *************************/
/*-------------------------------------------------------*/

void* VSAAlloc(vsa_t* vsa, size_t n_bytes)
{
	size_t full_size_seg = 0;
	vsa_t* vsa_runner = vsa;
	
	GetAlignSegmentSize(&n_bytes);
	full_size_seg = (n_bytes + HEADER_SIZE) / WORD_SIZE;
	while(END != GetOffset(vsa_runner))
	{
		if (!IsAllocated(vsa_runner))
		{
			while(GetOffset(vsa_runner) < full_size_seg
			   && DEFRAG_SUCCESS == DeFrag(vsa_runner));
			
			if (GetOffset(vsa_runner) >= full_size_seg)
			{
				full_size_seg = GetOffset(vsa_runner) == full_size_seg + 1 ? 
						full_size_seg + 1 : full_size_seg;
				UpdateNextHeader(vsa_runner, full_size_seg);
				SetOffset(vsa_runner, full_size_seg);
				SetToAllocated(vsa_runner);
			
				#ifndef NDEBUG
					SetDeadBeef(vsa_runner);
				#endif			
				
				return vsa_runner + WORD_SIZE / WORD_SIZE;
			}	
		}
		vsa_runner = (vsa_t*)((size_t*)vsa_runner + GetOffset(vsa_runner));
	}
	
	return NULL;
}

/*------------------------------------------------------*/
/************************* FREE *************************/
/*------------------------------------------------------*/

void VSAFree(void* segment)
{
	vsa_t* seg = (vsa_t*)segment - 1;
	
	assert(IsAllocated(seg));	
#ifndef NDEBUG
	assert (DEAD_BEEF == seg->deadbeef);
#endif
	
	SetToFree(seg);
}

/*--------------------------------------------------------------------*/
/************************* LARGEST CHUNK FREE *************************/
/*--------------------------------------------------------------------*/

size_t VSALargestChunkFree(vsa_t* vsa)
{
	size_t largest_chunck = 0;
	while(END != GetOffset(vsa))
	{
		while(DEFRAG_SUCCESS == DeFrag(vsa));
		
		if (!IsAllocated(vsa))
		{
			largest_chunck = (largest_chunck < GetOffset(vsa)) ?
					  GetOffset(vsa) : largest_chunck;
		}
		vsa = (vsa_t*)((size_t*)vsa + GetOffset(vsa));
	}
	return WORD_SIZE * largest_chunck;
}

/*-----------------------------------------------------------------*/
/************************* STATIC FUNCTION *************************/
/*-----------------------------------------------------------------*/

static int DeFrag(vsa_t* vsa)
{
	vsa_t* vsa_next = (vsa_t*)((size_t*)vsa + GetOffset(vsa));
	if((END != GetOffset(vsa)) && !IsAllocated(vsa_next) && !IsAllocated(vsa))
	{
		SetOffset(vsa, GetOffset(vsa) + GetOffset(vsa_next));
		return DEFRAG_SUCCESS;
	}
	return !DEFRAG_SUCCESS;
}


static void UpdateNextHeader(vsa_t* vsa, size_t full_size_seg)
{
	vsa_t* vsa_next = NULL;
	if (full_size_seg != GetOffset(vsa))
	{
		vsa_next = (vsa_t*)((size_t*)vsa + full_size_seg);
		vsa_next->offset = 0;
		SetOffset(vsa_next, GetOffset(vsa) - full_size_seg);
		SetToFree(vsa_next);
	#ifndef NDEBUG
		vsa->deadbeef = DEAD_BEEF;
	#endif	
	}
}

static void GetAlignSegmentSize(size_t* n_bytes)
{
	*n_bytes = (0 == (*n_bytes % WORD_SIZE)) ? 
		    *n_bytes : *n_bytes + WORD_SIZE - (*n_bytes % WORD_SIZE);
}

static void AlignPool(void* pool, size_t* p_size)
{
	while(0 != (size_t)pool % WORD_SIZE)
	{
		pool = (char*)pool + BYTE_SIZE;
		--*p_size;
	}
}

static size_t GetOffset(vsa_t* vsa)
{
	return vsa->offset >> 1;
}

static void SetOffset(vsa_t* vsa, size_t offset)
{
	size_t allcoation_flag = IsAllocated(vsa);
	size_t offset_size = (offset << 1);

	vsa->offset = offset_size + allcoation_flag;
}

static size_t IsAllocated(vsa_t* vsa)
{
	return (vsa->offset & ALLOCATED);
}

static void SetToAllocated(vsa_t* vsa)
{
	vsa->offset |= ALLOCATED;
}

static void SetToFree(vsa_t* vsa)
{
	vsa->offset &= ~ALLOCATED;
}

#ifndef NDEBUG
static void SetDeadBeef(vsa_t* vsa)
{
	vsa->deadbeef = DEAD_BEEF;
}
#endif	

