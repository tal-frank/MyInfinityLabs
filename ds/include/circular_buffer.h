#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__


/********************************************************* Standard libraries */
#include <stddef.h> /* size_t */
#include <sys/types.h>  /* ssize_t */


/******************************************************************** Structs */
typedef struct circular_buffer cbuff_t;


/************************************************************* Main functions */

/*****************************************************************************
 * 		
 * Description: Creates a circular Cbuffer with the capacity specified in the argument in bytes.
 *		
 *   Arguments: capacity - Amount of bytes allowed to store in the buffer.
 *		
 *      Return: A pointer to the cbuffer. Return NULL at failure.
 *		
 *  Complexity: Time: O(1) Space: O(n)
 *		
 *		
 ******************************************************************************/

cbuff_t* CBuffCreate(size_t capacity);

/*****************************************************************************
 * 		
 * Description: Gets a pointer to a cbuffer and destroys it.
 *		        
 *   Arguments: cbuff - A pointer to a cbuffer to destroy.
 *		
 *      Return: None.
 *		
 *  Complexity: Time: O(1) Space: O(1)
 *		
 *		
 ******************************************************************************/

void CBuffDestroy(cbuff_t* cbuff);

/*****************************************************************************
 * 		
 * Description: Copies n bytes to a specified buffer from the cbuffer. 
 *		when the buffer is empty stops copying.
 *		        
 *   Arguments: cbuff   - A pointer to the cbuff to copy from.
 *		dest    - A pointer to a buffer to copy to.
 *		n_bytes - Number of bytes to copy. 
 *		
 *      Return: Number of bytes actually copied.
 *		
 *  Complexity: Time: O(n) Space: O(1)
 *		
 *		
 ******************************************************************************/

ssize_t CBuffRead(cbuff_t* cbuff, void* dest, size_t n_bytes);

/*****************************************************************************
 * 		
 * Description: Copies n bytes to the cbuffer from a specified buffer. 
 *		when the buffer is full stops copying.
 *		        
 *   Arguments: cbuff   - A pointer to the cbuff to copy to.
 *		src     - A pointer to a buffer to copy from.
 *		n_bytes - Number of bytes to copy.
 *		
 *      Return: Number of bytes actually copied.
 *		
 *  Complexity: Time: O(n) Space: O(1)
 *		
 *		
 ******************************************************************************/

ssize_t CBuffWrite(cbuff_t* cbuff, const void* src, size_t n_bytes); 

/*****************************************************************************
 * 		
 * Description: Gets a pointer to a buffer and returns it's capacity.
 *		        
 *   Arguments: cbuff - A pointer to a buffer to get it's capacity.
 *		
 *      Return: The capacity of the buffer.
 *		
 *  Complexity: Time: O(1) Space: O(1)
 *		
 *		
 ******************************************************************************/ 

size_t CBuffSize(const cbuff_t* cbuff);

/*****************************************************************************
 * 		
 * Description: Gets a pointer to a buffer and check if it is empty.
 *		        
 *   Arguments: cbuff - A pointer to a buffer to check if empty.
 *		
 *      Return: 1 if empty, 0 otherwise.
 *		
 *  Complexity: Time: O() Space: O()
 *		
 *		
 ******************************************************************************/

int CBuffIsEmpty(const cbuff_t* cbuff);

/*****************************************************************************
 * 		
 * Description: Gets the amount of free space in bytes at the buffer.
 *		        
 *   Arguments: cbuff - A pointer to a buffer to check the amount of free space in.
 *		
 *      Return: Amount of free space in bytes at the buffer.
 *		
 *  Complexity: Time: O(1) Space: O(1)
 *		
 *		
 ******************************************************************************/

size_t CBuffFreeSpaceLeft(const cbuff_t* cbuff);





#endif /*************************************** End of  __CIRCULAR_BUFFER_H__ */
