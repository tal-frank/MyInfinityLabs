
/**********************
 * ws6_files
 * Author: Tal Frank
 * Reviewer: Name
**********************/

#include <stdio.h>
#include "bitwise.h"




int main()
{	
	unsigned int arr3bit[5] = {7, 10, 14, 32, 31};
	unsigned int x;
	unsigned int y;
	unsigned int z;
	long pow;
	int is_pow;
	int is_pow_noloop;
	int add1;
	unsigned char mirrored;
	unsigned char mirrored_noloop;
	unsigned Snd_Sixth;
	int is_sec_sexth;
	int is_sec_or_sexth;
	unsigned char replace_5_3;
	unsigned char divide_16;
	unsigned int cnt_set_bit;
	unsigned int cnt_set_bit_noloop;
	float num_in_bits;
	int* var1;
	int* var2;
	int* var1V2;
	int* var2V2;
	int a;
	int b;
	int aV2;
	int bV2;
	
	x = 7;
	y = 7;
	z = 32;
	a = 208;
	b = 105;
	aV2 = 208;
	bV2 = 105;
	add1 = 3984;
	mirrored = 203;
	mirrored_noloop = 203;
	Snd_Sixth = 10;
	replace_5_3 = 36;
	divide_16 = 76;
	cnt_set_bit = 97378;
	cnt_set_bit_noloop = 97378;
	num_in_bits = 3;
	var1 = &a;
	var2 = &b;
	var1V2 = &aV2;
	var2V2 = &bV2;
	
	
	SwapVarsV2(var1V2, var2V2);
	SwapVars(var1, var2);
	FloatAnalysis(num_in_bits);
	cnt_set_bit_noloop = CountSetBits(cnt_set_bit_noloop);
	cnt_set_bit = CountSetBitsLoop(cnt_set_bit);
	divide_16 = MaxDivisedBy16(divide_16);
	replace_5_3 = SwapThirdAndFifthBits(replace_5_3);	
	is_sec_sexth = IsSecondAndSixthBitOn(Snd_Sixth);
	is_sec_or_sexth = IsSecondOrSixthBitOn(Snd_Sixth);
	mirrored = ByteMirrorLoop(mirrored);
	mirrored_noloop = ByteMirror(mirrored_noloop);
	PrintNumsWith3BitsOn(arr3bit, 5);
	pow = Pow2(x, y);
	is_pow = IsPowOf2Loop(z);
	is_pow_noloop = IsPowOf2(z);
	add1 = Add1(add1);
	
	printf("swap V2 : var1 = %d  ,  var2 = %d\n", *var1V2, *var2V2);
	printf("swap V1 : var1 = %d  ,  var2 = %d\n", *var1, *var2);
	printf("num of set bits no loop : %d\n", cnt_set_bit_noloop);
	printf("num of set bits : %d\n", cnt_set_bit);
	printf("closest divided by sixteen : %d\n", divide_16);
	printf("swap third and sixth %d\n", replace_5_3);
	printf("second and sixth are : %d\n" , is_sec_sexth);
	printf("second or sixth are : %d\n" , is_sec_or_sexth);
	printf("mirrored = %d\n" , mirrored);
	printf("mirrored no loop = %d\n" , mirrored_noloop);
	printf("add1 = %d\n" , add1);
	printf("pow = %ld\n" , pow);
	printf("is pow of 2 ? %d\n" , is_pow);
	printf("is pow of 2 no loop ? %d\n" , is_pow_noloop);
	
	return 0;
}






