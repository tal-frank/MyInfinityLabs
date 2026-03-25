#include <stdlib.h>
#include <stdio.h>

#include "../include/bit_array.h"

int main()
{
	int i = 0;
	int check_bit = 0;
	size_t cnt = 0;
	bitarray_t bitarray = 0;
	char* str = (char*)malloc(8 * sizeof(size_t) + 1);
	if (NULL == str)
	{
		printf("can't allocate memory\n");
		return 0;
	}
	
	for (i = 0; i < 63; i += 2)
	{
		bitarray = BitarraySetBitOn(bitarray, i);
		BitarrayToString(bitarray, str);
	}

	bitarray = BitarraySetAll(bitarray);
	BitarrayToString(bitarray, str);
	
	for (i = 0; i < 63; i += 3)
	{	
		bitarray = BitarraySetBitOff(bitarray, i);
		BitarrayToString(bitarray, str);
	}
	
	bitarray = BitarrayResetAll(bitarray);
	
	printf("set on the 40th bit\n");
	bitarray = BitarraySetBitOn(bitarray, 40);
	BitarrayToString(bitarray, str);
	
	printf("set on the 8th bit\n");
	bitarray = BitarraySetBitOn(bitarray, 8);
	BitarrayToString(bitarray, str);
	
	printf("check if the 8th bit is set\n");
	check_bit = BitarrayGetBit(bitarray, 8);
	printf("8th bit is : %d\n" , check_bit);
	
	printf("check if the 45th bit is set\n");
	check_bit = BitarrayGetBit(bitarray, 45);
	printf("45th bit is : %d\n" , check_bit);
	
	printf("set on the 10th bit\n");
	bitarray = BitarraySetBitOn(bitarray, 10);
	BitarrayToString(bitarray, str);
	
	printf("set on the 6th bit\n");
	bitarray = BitarraySetBitOn(bitarray, 6);
	BitarrayToString(bitarray, str);
	
	printf("mirrored array\n");
	bitarray = BitarrayMirrorBits(bitarray);
	BitarrayToString(bitarray, str);
	
	printf("number of set on bits is:\n");
	cnt = BitarrayCountOn(bitarray);
	printf("%ld\n", cnt);
	
	printf("number of set off bits is:\n");
	cnt = BitarrayCountOff(bitarray);
	printf("%ld\n", cnt);
	
	printf("flip the 13th bit\n");
	bitarray = BitarrayFlipBit(bitarray, 13);
	BitarrayToString(bitarray, str);
	
	printf("flip the 6th bit\n");
	bitarray = BitarrayFlipBit(bitarray, 6);
	BitarrayToString(bitarray, str);
	
	printf("flip the 38th bit\n");
	bitarray = BitarrayFlipBit(bitarray, 38);
	BitarrayToString(bitarray, str);
	
	printf("rotate 47 to the left\n");
	bitarray = BitarrayRotL(bitarray, 47);
	BitarrayToString(bitarray, str);
	
	printf("rotate 47 to the right\n");
	bitarray = BitarrayRotR(bitarray, 47);
	BitarrayToString(bitarray, str);
	
	printf("set all bits on\n");
	bitarray = BitarraySetAll(bitarray);
	BitarrayToString(bitarray, str);
	
	printf("number of set on bits is:\n");
	cnt = BitarrayCountOn(bitarray);
	printf("%ld\n", cnt);
	
	printf("number of set off bits is:\n");
	cnt = BitarrayCountOff(bitarray);
	printf("%ld\n", cnt);
	
	printf("set all bits off\n");
	bitarray = BitarrayResetAll(bitarray);
	BitarrayToString(bitarray, str);
	
	printf("number of set on bits is:\n");
	cnt = BitarrayCountOn(bitarray);
	printf("%ld\n", cnt);
	
	printf("number of set off bits is:\n");
	cnt = BitarrayCountOff(bitarray);
	printf("%ld\n", cnt);
	
	free(str);
	return 0;
}
