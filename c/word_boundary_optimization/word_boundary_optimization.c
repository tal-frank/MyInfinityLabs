/**********************
 * Word Boundary Optimization
 * Author: Tal Frank
 * Reviewer: Or Zelner
 * Last update: 16/03/2026
**********************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "word_boundary_optimization.h"


/****************************** MACROS ******************************/

#define WORD_SIZE (sizeof(size_t))
#define BYTE_SIZE (sizeof(char))


/****************************** FUNCTION DECLARATIONS ******************************/

static void CpyByte(char* dest, const char* src, size_t* n);
static void CpyWord(size_t* dest, const size_t* src, size_t* n);
static void InsertCharByte(char* dest, const char ch, size_t* n);
static void InsertCharWord(size_t* dest, const char ch, size_t* n);
static void* CopyBackWards(void* dest, const void* src, size_t n);


/****************************** STATIC FUNCTIONS ******************************/

static void CpyByte(char* dest, const char* src, size_t* n)
{
	*dest = *src;
	*n -= BYTE_SIZE;
}


static void CpyWord(size_t* dest, const size_t* src, size_t* n)
{
	*dest = *src;
	*n -= WORD_SIZE;
}


static void InsertCharByte(char* dest, const char ch, size_t* n)
{
	*dest = ch;
	*n -= BYTE_SIZE;
}


static void InsertCharWord(size_t* dest, const char ch, size_t* n)
{
	size_t i;
	size_t full_ch = 0;

	for (i = 0; i < WORD_SIZE; ++i)
	{
		full_ch = (full_ch << 8) + ch;
	}

	*dest = full_ch;
	*n -= WORD_SIZE;
}


static void* CopyBackWards(void* dest, const void* src, size_t n)
{	
	void* real_dest = dest;
	
	dest = (char*)dest + n;
	src = (char*)src + n;
	
	while (n > 0 && ((size_t)dest % WORD_SIZE))
	{
		dest = (char*)dest - BYTE_SIZE; 
		src = (char*)src - BYTE_SIZE;
		CpyByte(dest, src, &n);
	}
	
	while (n >= WORD_SIZE)
	{
		dest = (char*)dest - WORD_SIZE;
		src = (char*)src - WORD_SIZE;
		CpyWord(dest, src, &n);
	}
	
	while (n > 0)
	{
		dest = (char*)dest - BYTE_SIZE; 
		src = (char*)src - BYTE_SIZE;
		CpyByte(dest, src, &n);
	}
	
	return real_dest;
}


/****************************** MEM COPY ******************************/

void* MemCpy(void* dest, const void* src, size_t n)
{	
	void* real_dest = dest;

	assert(dest);
	assert(src);

	while (n > 0 && ((size_t)dest % WORD_SIZE))
	{
		CpyByte(dest, src, &n);
		dest = (char*)dest + BYTE_SIZE; 
		src = (char*)src + BYTE_SIZE;
	}
	
	while (n >= WORD_SIZE)
	{
		CpyWord(dest, src, &n);
		dest = (char*)dest + WORD_SIZE;
		src = (char*)src + WORD_SIZE;
	}
	
	while (n > 0)
	{
		CpyByte(dest, src, &n);
		dest = (char*)dest + BYTE_SIZE; 
		src = (char*)src + BYTE_SIZE;
	}
	
	return real_dest;
}


/****************************** MEM SET ******************************/

void* MemSet(void* s, int c, size_t n)
{
	void* real_dest = s;

	assert(s);

	while (n > 0 && ((size_t)s % WORD_SIZE))
	{
		InsertCharByte(s, c, &n);
		s = (char*)s + BYTE_SIZE; 
	}
	
	while (n >= WORD_SIZE)
	{
		InsertCharWord(s, c, &n);
		s = (char*)s + WORD_SIZE;
	}
	
	while (n > 0)
	{
		InsertCharByte(s, c, &n);
		s = (char*)s + BYTE_SIZE; 
	}
	
	return real_dest;
}


/****************************** MEM MOVE ******************************/

void* MemMove(void* dest, const void* src, size_t n)
{
	assert(dest);
	assert(src);
	
	if (((size_t)src - (size_t)dest) > n)
	{
		return CopyBackWards(dest, src, n);
	}
	
	return MemCpy(dest, src, n);
}


