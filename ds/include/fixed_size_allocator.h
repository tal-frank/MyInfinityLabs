#ifndef __FIXED_SIZE_ALLOCATOTR_H__
#define __FIXED_SIZE_ALLOCATOTR_H__

typedef struct Fixed_memory_allocator_type fsa_t;


/*****************************************************************
* 		
* Description: Get requiered size of data and return the amount of 
*	       allocated space required for the FSA to handle this data.
*		        
*   Arguments: block_size - required block size in bytes.
*	       num_blocks - required number of blocks.
*		
*      Return: required amount of space for the FSA to handle the data.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

size_t FSASuggestSize(size_t block_size, size_t num_blocks);

/*****************************************************************
* 		
* Description: Gets an allocated container and initializes number of 
* 	       aligned blocks as the container recieved can hold.
*	       best to use the FSASuggestSize function to get optimized
*	       space for the data.
*		        
*   Arguments: mp        - A valid allocated container to handle the data in.
*	       pool_size - The size of the container in bytes.
*		
*      Return: A pointer to the FSA initialized.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

fsa_t* FSAInit(void* mp, size_t pool_size, size_t block_size);

/*****************************************************************
* 		
* Description: Returns the next available block in the container.
*		        
*   Arguments: mp - A valid allocated container to get the next free block in.
*		
*      Return: The next available block in the container.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void* FSAAlloc(fsa_t* mp);

/*****************************************************************
* 		
* Description: Frees a block in the container. can get NULL as an argument.
*		        
*   Arguments: mp    - A valid allocated container to free a block in.
*	       block - A block in the container to free.
*		
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void FSAFree(fsa_t* mp, void* block);

/*****************************************************************
* 		
* Description: Returns the number of free blocks in the container.
*		        
*   Arguments: mp - A valid allocated container to get number of free block in.
*		
*      Return: The number of free blocks in the container.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

size_t FSACountFree(const fsa_t* mp);


#endif /* __FIXED_SIZE_ALLOCATOTR_H__ */
