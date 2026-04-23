/**********************
* circular_buffer
* Author: Tal Frank
* Reviewer: Roman Polugrudov
* Last update: 13/04/2026
**********************/

#include <stdio.h> /* NULL */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/circular_buffer.h"

#define BYTE_SIZE (sizeof(char))

struct circular_buffer
{
    size_t read; 
    size_t size;
    size_t capacity;
    char buffer[1];
};

static void CpyByte(char* dest, const char* src)
{
	*dest = *src;
}


cbuff_t* CBuffCreate(size_t capacity)
{
	cbuff_t* cbuff = (cbuff_t*)malloc(sizeof(cbuff_t) + capacity);
	
	assert(0 != capacity);
	
	if (NULL == cbuff)
	{
		return NULL;
	}
	
	cbuff->capacity = capacity;
	cbuff->size = 0;
	cbuff->read = 0;
	
	return cbuff;
}

void CBuffDestroy(cbuff_t* cbuff)
{
	assert(NULL != cbuff);

	free(cbuff);
	cbuff = NULL;
}


size_t CBuffSize(const cbuff_t* cbuff)
{
	assert(NULL != cbuff);	
	
	return cbuff->capacity;
}


int CBuffIsEmpty(const cbuff_t* cbuff)
{
	assert(NULL != cbuff);

	return (0 == cbuff->size);
}


size_t CBuffFreeSpaceLeft(const cbuff_t* cbuff)
{
	assert(NULL != cbuff);

	return cbuff->capacity - cbuff->size;
}


ssize_t CBuffRead(cbuff_t* cbuff, void* dest, size_t n_bytes)
{
	size_t i = 0;
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	for (i = 0; n_bytes > i && 0 != cbuff->size; ++i)
	{
		CpyByte(dest, &cbuff->buffer[cbuff->read]);
		dest = (char*)dest + BYTE_SIZE;
		
		cbuff->read = ((cbuff->read + BYTE_SIZE) % cbuff->capacity);
		cbuff->size -= BYTE_SIZE;
	}	
	return i;
}


ssize_t CBuffWrite(cbuff_t* cbuff, const void* src, size_t n_bytes)
{
	size_t i = 0;
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	for (i = 0; n_bytes > i && cbuff->size < cbuff->capacity; ++i)
	{
		CpyByte(&cbuff->buffer[(cbuff->read + cbuff->size) % cbuff->capacity], src);
		src = (char*)src + BYTE_SIZE;
		
		cbuff->size += BYTE_SIZE;
	}
	return i;
}





