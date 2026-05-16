#ifndef __VARIABLE_SIZE_ALLOCATOR_H__
#define __VARIABLE_SIZE_ALLOCATOR_H__

typedef struct Variable_size_allocator_t vsa_t;

/****************************************************************************
* 		
* Description: Initialize a VSA and return a pointer to its beginning.
*		        
*   Arguments:   pool - A valid previosly allocated container to use the vsa in.
*	       p_size - The size of the desired vsa. shouldn't be larger then
*			pool size.
*		
*      Return: A pointer to the vsa initialized.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

vsa_t* VSAInit(void* pool, size_t p_size);

/****************************************************************************
* 		
* Description: Allocates a space in the  pool large enough to contain n_bytes bytes.
*		        
*   Arguments:     vsa - A valid pointer to the vsa desired to allocate space in. 
*	       n_bytes - Number of bytes needed to be allocated.
*		
*      Return: A pointer to the allocated space in the vsa.
*		
*  Complexity: Time: O(n) Space: O(1)
*		
*		
******************************************************************************/

void* VSAAlloc(vsa_t* vsa, size_t n_bytes);

/****************************************************************************
* 		
* Description: Frees a chosen allocated space in the vsa. The space chosen must be allocated
*	       , alligned and in the exaced place got from the VSAAlloc function.
*		        
*   Arguments: segment - A valid pointer to space to free.
*		
*      Return: None.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

void VSAFree(void* segment);

/****************************************************************************
* 		
* Description: Finds the largest countinous segment availabe (not allocated) in the vsa.
*		        
*   Arguments: vsa - A valid pointer to the vsa desired to find free space in.
*		
*      Return: Largest countinous segment availabe (not allocated) in the vsa.
*		
*  Complexity: Time: O(1) Space: O(1)
*		
*		
******************************************************************************/

size_t VSALargestChunkFree(vsa_t* vsa);


#endif /* __VARIABLE_SIZE_ALLOCATOR_H__ */
