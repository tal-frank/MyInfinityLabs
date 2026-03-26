#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h>


typedef size_t bitarray_t;

/*
* Description:    sets on the bit at the index place. 
* 
* Arguments:      bitarray   - Bitarray to modify.
*                 index      - Index to turn on.
* 
* Return:         bitarray after modification.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/
bitarray_t BitarraySetBitOn(bitarray_t bitarray, size_t index); /* set */

/*
* Description:    sets off the bit at the index place. 
* 
* Arguments:      bitarray   - Bitarray to modify.
*                 index      - Index to turn off.
* 
* Return:         bitarray after modification.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

bitarray_t BitarraySetBitOff(bitarray_t bitarray, size_t index); /* set */

/*
* Description:    flips the bit at the index place. 
* 
* Arguments:      bitarray   - Bitarray to modify.
*                 index      - Index to flip its value.
* 
* Return:         bitarray after modification.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/


bitarray_t BitarrayFlipBit(bitarray_t bitarray, size_t index); /* flip */

/*
* Description:    gets the state of the bit at the index place. 
* 
* Arguments:      bitarray   - Bitarray to modify.
*                 index      - Index to get the value from.
* 
* Return:         Value of the bit at the index.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

int BitarrayGetBit(bitarray_t bitarray, size_t index); /* get */

/*
* Description:    counts the number of set on the bits in the bitarray. 
* 
* Arguments:      bitarray   - Bitarray to count the set on bits.
* 
* Return:         Number of set on bits.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/


size_t BitarrayCountOn(bitarray_t bitarray); /* count on */

/*
* Description:    counts the number of set off the bits in the bitarray. 
* 
* Arguments:      bitarray   - Bitarray to count the set off bits.
* 
* Return:         Number of set off bits.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

size_t BitarrayCountOff(bitarray_t bitarray); /* count off */

/*
* Description:    counts the number of set on the bits in the bitarray. 
* 
* Arguments:      bitarray   - Bitarray to count the set on bits.
* 
* Return:         Number of set off bits.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

size_t BitarrayCountOnLut(bitarray_t bitarray); /* count on */

/*
* Description:    counts the number of set off the bits in the bitarray. 
* 
* Arguments:      bitarray   - Bitarray to count the set off bits.
* 
* Return:         Number of set off bits.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

size_t BitarrayCountOffLut(bitarray_t bitarray); /* count off */

/*
* Description:    makes a string of the array and prints it.
* 
* Arguments:      bitarray - Bitarray to turn to a string.
*		  dest     - A destination char pointer with enough space to contain the string.
* 
* Return:         Pointer to the beginning of the string.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

char* BitarrayToString(bitarray_t bitarray, char* dest);

/*
* Description:    reverse the order of the bits. least segnificat to most segnificant and so on. 
* 
* Arguments:      bitarray - A bitarray to mirror
* 
* Return:         mirrored bitarray.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

bitarray_t BitarrayMirrorBits(bitarray_t bitarray);

/*
* Description:    rotate the the bits of the array by index steps to the left/right. 
		  if a bit is overlaps it gets back to the start/end cyclicly.
* 
* Arguments:      bitarray - Bitarray to rotate.
*		  amount   - Number of rotations to execute.
* 
* Return:         Rotated bitarray.
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

bitarray_t BitarrayRotL(bitarray_t bitarray, size_t amount);
bitarray_t BitarrayRotR(bitarray_t bitarray, size_t amount);

/*
* Description:    sets on/off all the bits in the bitarray. 
* 
* Arguments:      bitarray - Bit array to set all on/off.
* 
* Return:         Turned on/off bitarray
* 
* Complexity:     time:   O(1)
*                 space:  O(1)
*/

bitarray_t BitarrayResetAll(bitarray_t bitarray);
bitarray_t BitarraySetAll(bitarray_t bitarray);


#endif /* End of __BITMAP_H__ */
