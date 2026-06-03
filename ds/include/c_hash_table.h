#ifndef __C_HASH_TABLE_H__
#define __C_HASH_TABLE_H__

#include <stddef.h> /* size_t */

typedef struct Hash_table hash_t;

hash_t* HashCreate(size_t table_size, size_t (*hash_func)(const void* key), int (*cmp_func)(const void* key1, const void* key2));

void HashDestroy(hash_t* hash);

int HashInsert(hash_t* hash, void* data, const void* key);

void HashRemove(hash_t* hash, const void* key);

void* HashFind(hash_t* hash, const void* key);

int HashIsEmpty(const hash_t* hash);

size_t HashCount(const hash_t* hash);

int HashForEach(hash_t* hash, int(*act_func)(void* data, void* param), void* param);


#endif /* End of __C_HASH_TABLE_H__ */

