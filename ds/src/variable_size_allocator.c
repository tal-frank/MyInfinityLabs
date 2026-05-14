
#include <stddef.h> /* size_t */

#include "variable_size_allocator.h"

#define WORD_SIZE (sizeof(size_t))
#define BYTE_SIZE (sizeof(char))
#define END (0)

struct Variable_size_allocator_t
{
	size_t offset;
};

static void GetAlignSegmentSize(size_t* n_bytes);
static void AlignPool(void* pool);
static size_t IsAllocated(vsa_t* vsa);
static size_t GetOffset(vsa_t* vsa);
static size_t SetAllocation(vsa_t* vsa);
static void SetOffset(vsa_t* vsa, size_t n_bytes);
static void FragBreak(vsa_t* vsa);

vsa_t* VSAInit(void* pool, size_t p_size)
{
	vsa_t pool_start = {0};
	vsa_t pool_end = {0};
	vsa_t* pool_t = (vsa_t*)pool;
	
	pool_start.offset = p_size / WORD_SIZE;
	pool_end.offset = END;
	
	AlignPool(&pool_t);
	pool_t[0] = pool_start;
	pool_t[p_size - WORD_SIZE] = pool_end;
	
	return pool_t;
}

void* VSAAlloc(vsa_t* vsa, size_t n_bytes)
{
	int allocated = 0;
	size_t full_size_seg = (n_bytes + WORD_SIZE) / WORD_SIZE;
	
	GetAlignSegmentSize(&n_bytes);
	while(!allocated && END != GetOffset(vsa))
	{
		while(!IsAllocated(vsa) && GetOffset(vsa) < full_size_seg + 1)
		{
			FragBreak(vsa); /** build function **/
		}
		
		if (!IsAllocated(vsa) && GetOffset(vsa) >= full_size_seg + 1)
		{
			full_size_seg = GetOffset(vsa) == full_size_seg + 1 ? 
					full_size_seg + WORD_SIZE : full_size_seg;
			SetOffset(vsa, full_size_seg);
			SetAllocation(vsa);
			return vsa;
		}
		vsa += full_size_seg;
	}
	if (END == vsa->offset)
	{
		return NULL;
	}
	return vsa;
}


void VSAFree(void* segment)
{
	vsa_t* seg = (vsa_t*)segment;
	--seg;
	SetAllocation(seg);
	
}

size_t LargestChunkFree(vsa_t* vsa);


static void FragBreak(vsa_t* vsa)
{
	vsa_t* vsa_runner = vsa + vsa->offset;
	while (!IsAllocated(vsa))
	{
		SetOffset(vsa, vsa_runner->offset);
		vsa_runner = vsa;
		vsa_runner += vsa_runner->offset;
	}
}


static void GetAlignSegmentSize(size_t* n_bytes)
{
	while(0 != (*n_bytes % WORD_SIZE))
	{
		 ++*n_bytes;
	}
}

static void AlignPool(void* pool)
{
	while(0 != (size_t)pool % WORD_SIZE)
	{
		pool = (char*)pool + BYTE_SIZE;
	}
}

static size_t GetOffset(vsa_t* vsa)
{
	return vsa->offset >> 1;
}

static void SetOffset(vsa_t* vsa, size_t offset)
{
	vsa->offset = offset;
	vsa->offset <<= 1;
}

static size_t IsAllocated(vsa_t* vsa)
{
	return !(vsa->offset & 0x01);
}

static size_t SetAllocation(vsa_t* vsa)
{
	return vsa->offset ^ 0x01;
}



