#ifndef __C_HASH_TABLE_H__
#define __C_HASH_TABLE_H__

#include <stddef.h> /* size_t */

typedef struct Hash_table hash_t;

/********************************* HashCreate ********************************
* 		
* Description: Creates a hash table in a specific size, that responds to a given by the 
*              user hash function, and uses a given by the user compare function. The 
*              compare function and hash function must respond the same way to a given key.
*
*   Arguments: table_size - The size of the table to be built.
*               hash_func - A function given by the user that determines where in the 
*                           table a certain key is sent. The function must be consistant
*                           and always send a certian to the same place.
*                cmp_func - A function that compares between two keys.
*              
*      Return: A pointer to a hash table at success, NULL at failure.
*
*  Complexity: Time: O(1) Space: O(n)
*		
*		
******************************************************************************/
hash_t* HashCreate(size_t table_size, size_t (*hash_func)(const void* key), int (*cmp_func)(const void* key1, const void* key2));

/********************************* HashDestroy ********************************
* 		
* Description: Destroys a hash table.
*
*   Arguments: hash - A valid pointer to a hash table to destroy.
*
*      Return: None.
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
void HashDestroy(hash_t* hash);

/********************************* HashInsert ********************************
* 
* Description: Inserts a new element to the hash table.
*
*   Arguments: hash - A valid pointer to a hash table to insert an element to.
*
*      Return: 0 at success, 1 at failure.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
int HashInsert(hash_t* hash, void* data, const void* key);

/********************************* HashRemove ********************************
* 		
* Description: Removes an element from the hash table.
*
*   Arguments: hash - A valid pointer to a hash table to remove an element from.
*               key - A pointer to a key to search and remove from the table.
*
*      Return: None.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
void HashRemove(hash_t* hash, const void* key);

/********************************* HashFind ********************************
* 		
* Description: Finds an element in the hash using a given key. 
*
*   Arguments: hash - A valid pointer to a hash table to search an element in.
*               key - A pointer to a key to search in the table.
*
*      Return: The element's value at success, NULL at failure.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
void* HashFind(hash_t* hash, const void* key);

/********************************* HashIsEmpty ********************************
* 		
* Description: Checks if a hash table is empty. 
*
*   Arguments: hash - A valid pointer to a hash table to check if empty.
*
*      Return: 1 if empty, 0 if not. 
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
int HashIsEmpty(const hash_t* hash);

/********************************* HashCount ********************************
* 		
* Description: Counts the number of elements currently in the hash table.
*
*   Arguments: hash - A valid pointer to a hash table to count elements in.
*
*      Return: Number of elements in the hash table.
*
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/
size_t HashCount(const hash_t* hash);

/********************************* HashForEach ********************************
* 		
* Description: Activates an operation on every element in the table.
*              The operation must not change the value of the key paired
*              with the element.
*
*   Arguments:     hash - A valid pointer to a hash table to operate on.
*              act_func - An action function to operate on each element in
*                         the hash table.
*
*      Return: 0 on success, 1 on failiure.
*
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/
int HashForEach(hash_t* hash, int(*act_func)(void* data, void* param), void* param);


#endif /* End of __C_HASH_TABLE_H__ */

