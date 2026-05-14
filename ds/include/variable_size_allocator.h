#ifndef __VARIABLE_SIZE_ALLOCATOR_H__
#define __VARIABLE_SIZE_ALLOCATOR_H__

typedef struct Variable_size_allocator_t vsa_t;

vsa_t* VSAInit(void* pool, size_t p_size);

void* VSAAlloc(vsa_t* vsa, size_t n_bytes);

void VSAFree(void* block);

size_t LargestChunkFree(vsa_t* vsa);


#endif /* __VARIABLE_SIZE_ALLOCATOR_H__ */
