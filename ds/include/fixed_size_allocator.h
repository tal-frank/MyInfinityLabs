#ifndef __FIXED_SIZE_ALLOCATOTR_H__
#define __FIXED_SIZE_ALLOCATOTR_H__

typedef struct Fixed_memory_allocator_type fsa_t;



size_t FSASuggestSize(size_t block_size, size_t num_blocks);

fsa_t* FSAInit(void* mp, size_t pool_size, size_t block_size);

void* FSAAlloc(fsa_t* mp);

void FSAFree(fsa_t* mp, void* block);

size_t FSACountFree(const fsa_t* mp);


#endif /* __FIXED_SIZE_ALLOCATOTR_H__ */
