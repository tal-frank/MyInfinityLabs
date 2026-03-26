/**********************
* Bit Array
* Author: Tal Frank
* Reviewer: Maor Gorbman
* Last update: 24/03/2026
**********************/

#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert */

#include "../include/bit_array.h"

#define CHAR_0_ALIGN (48)
#define WORD_SIZE (CHAR_BIT * sizeof(bitarray_t))


/*********************************** STATIC LUTS ***********************************/

static unsigned long left_mask_lut[6] = {0x5555555555555555, 0x3333333333333333, 
				  0x0F0F0F0F0F0F0F0F, 0x00FF00FF00FF00FF, 
				  0x0000FFFF0000FFFF, 0x00000000FFFFFFFF};
static unsigned long right_mask_lut[6] = {0xAAAAAAAAAAAAAAAA, 0xCCCCCCCCCCCCCCCC, 
				   0xF0F0F0F0F0F0F0F0, 0xFF00FF00FF00FF00, 
				   0xFFFF0000FFFF0000, 0xFFFFFFFF00000000};

static int bit_cnt_on_lut[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

static int bit_cnt_off_lut[16] = {4, 3, 3, 2, 3, 2, 2, 1, 3, 2, 2, 1, 2, 1, 1, 0};


/*********************************** STATIC FUNCTION DECLARATIONS ***********************************/

static char* ReverseString (char* str);


/*********************************** STATIC FUNCTIONS ***********************************/

static char* ReverseString (char* str)
{
	size_t i = 0;
	char* rev_str = NULL;
	size_t len = strlen(str);
		
	rev_str = (str + len - 1);	
	for (i = 0; i < len / 2; ++i)
	{
		char temp = *rev_str;
		*rev_str = *str;
		*str = temp;
		++str; --rev_str;
	}
	
	return rev_str;
}


/*********************************** BIT ARRAY SET FUNCTIONS ***********************************/

bitarray_t BitarraySetBitOn(bitarray_t bitarray, size_t index)
{	
	size_t set_bit_on = 1;

	assert(index < WORD_SIZE);

	return bitarray | (set_bit_on << index);
}


bitarray_t BitarraySetBitOff(bitarray_t bitarray, size_t index)
{
	size_t set_bit_off = 1;
	
	assert(index < WORD_SIZE);
	
	return bitarray & ~(set_bit_off << index);
}


bitarray_t BitarrayResetAll(bitarray_t bitarray)
{
	size_t reset_all = 0;
	return bitarray & reset_all;
}


bitarray_t BitarraySetAll(bitarray_t bitarray)
{
	size_t set_all = ~0;
	return (bitarray | set_all);
}


bitarray_t BitarrayFlipBit(bitarray_t bitarray, size_t index)
{
	size_t set_bit_on = 1;
	
	assert(index < WORD_SIZE);
	
	return bitarray ^ (set_bit_on << index);
}


/*********************************** BIT ARRAY GET FUNCTIONS ***********************************/

int BitarrayGetBit(bitarray_t bitarray, size_t index)
{	
	size_t set_bit_on = 1;
	
	assert(index < WORD_SIZE);

	return !!(bitarray & (set_bit_on << index));
}


/*********************************** BIT ARRAY ROTATE FUNCTIONS ***********************************/

bitarray_t BitarrayRotL(bitarray_t bitarray, size_t amount)
{	
	size_t rotation_mask = bitarray >> ((CHAR_BIT * sizeof(bitarray_t)) - amount);	
	
	assert(amount <= WORD_SIZE);
	
	return (bitarray << amount) | (rotation_mask);
}


bitarray_t BitarrayRotR(bitarray_t bitarray, size_t amount)
{	
	size_t rotation_mask = bitarray << ((CHAR_BIT * sizeof(bitarray_t)) - amount);
	
	assert(amount <= WORD_SIZE);
	
	return (bitarray >> amount | (rotation_mask));
}


bitarray_t BitarrayMirrorBitsHC(bitarray_t bitarray)
{
	bitarray = ((bitarray & 0x5555555555555555) << 1) | ((bitarray & 0xAAAAAAAAAAAAAAAA) >> 1);
	bitarray = ((bitarray & 0x3333333333333333) << 2) | ((bitarray & 0xCCCCCCCCCCCCCCCC) >> 2);
	bitarray = ((bitarray & 0x0F0F0F0F0F0F0F0F) << 4) | ((bitarray & 0xF0F0F0F0F0F0F0F0) >> 4);
	bitarray = ((bitarray & 0x00FF00FF00FF00FF) << 8) | ((bitarray & 0xFF00FF00FF00FF00) >> 8);
	bitarray = ((bitarray & 0x0000FFFF0000FFFF) << 16) | ((bitarray & 0xFFFF0000FFFF0000) >> 16);
	bitarray = ((bitarray & 0x00000000FFFFFFFF) << 32) | ((bitarray & 0xFFFFFFFF00000000) >> 32);
	
	return bitarray;
}


bitarray_t BitarrayMirrorBits(bitarray_t bitarray)
{
	size_t i = 0;
	size_t j = 0;
		
	for (i = 1, j = 0; i < CHAR_BIT * sizeof(bitarray_t); i <<= 1, ++j)
	{	
		bitarray = ((bitarray & left_mask_lut[j]) << i) | ((bitarray & right_mask_lut[j]) >> i);
	}
	
	return bitarray;
}


/*********************************** BIT ARRAY COUNT FUNCTIONS ***********************************/

size_t BitarrayCountOn2(bitarray_t bitarray)
{
	size_t cnt_on = 0;
	while (0 != bitarray)
	{
		bitarray = bitarray & (bitarray -1);
		++cnt_on;
	}
	return cnt_on;
}


size_t BitarrayCountOff2(bitarray_t bitarray)
{
	size_t cnt_on = 0;
	while (0 != bitarray)
	{
		bitarray = bitarray & (bitarray -1);
		++cnt_on;
	}
	return (CHAR_BIT * sizeof(bitarray_t)) - cnt_on;
}


size_t BitarrayCountOn(bitarray_t bitarray)
{
	size_t cnt_on = 0;
	
	while (bitarray != 0)
	{
		cnt_on += bit_cnt_on_lut[bitarray & 0x0F];
		bitarray >>= (CHAR_BIT / 2);
	}
	return cnt_on;
}


size_t BitarrayCountOff(bitarray_t bitarray)
{
	size_t cnt_off = 0;
	size_t word_runner = WORD_SIZE;
	
	while (word_runner > 0)
	{
		cnt_off += bit_cnt_off_lut[bitarray & 0x0F];
		bitarray >>= (CHAR_BIT / 2);
		word_runner -= (CHAR_BIT / 2);
	}
	return cnt_off;
}

/*********************************** BIT ARRAY TO STRING & PRINT ***********************************/

char* BitarrayToString(bitarray_t bitarray, char* dest)
{
	size_t i = 0;
	size_t mask = 0x1;
	
	assert(NULL != dest);
	
	for(i = 0; i < CHAR_BIT * sizeof(size_t); ++i)
	{
		dest[i] = (char)((bitarray & mask) + CHAR_0_ALIGN);
		bitarray >>= 1;
	}
	
	dest[CHAR_BIT * sizeof(size_t)] = '\0';
	ReverseString(dest);
	printf("%s\n", dest);
	return dest;
}



