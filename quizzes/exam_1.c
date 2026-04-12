
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

static int nibble_on_bits[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};


/*--------------------------------------------------------------------------------------------*/
/******************************************** EXAM ********************************************/
/*--------------------------------------------------------------------------------------------*/

int FlipDigitsInNum(int num)
{
	int neg_flag = 1;
	int rev_num = 0;
	
	while (0 != num)
	{
		rev_num *= 10;
		rev_num += num % 10;
		num /= 10;
	}
	return rev_num * neg_flag;
}


unsigned char MirrorByte(char byte)
{
	unsigned char mirrored_byte = ((byte & 0x01) << 7) |
				      ((byte & 0x02) << 5) |
				      ((byte & 0x04) << 3) |
				      ((byte & 0x08) << 1) |
				      ((byte & 0x10) >> 1) |
				      ((byte & 0x20) >> 3) |
				      ((byte & 0x40) >> 5) |
				      ((byte & 0x80) >> 7);
	return mirrored_byte;
}


int FlipBit(int val, unsigned int n)
{
	int mask = 0x01;
	return val ^ (mask << n);
}


int CountOnBits(char byte)
{
	int cnt = 0;
	int nibble = 0;
	
	while (0 != byte)
	{
		nibble = byte & 0x0F;
		cnt += nibble_on_bits[nibble];
		byte >>= 4;
	}
	return cnt;
}


char RotateLeft(char byte, unsigned int nbits)
{
	assert(8 > nbits);	
	
	return (byte << nbits) | (byte >> (8 - nbits));
}


void SwapPointers(int** p1, int** p2)
{
	int* temp = *p1;
	
	assert(NULL != p1);
	assert(NULL != p2);
	
	*p1 = *p2;
	*p2 = temp;
}


size_t StrLen(const char* str)
{
	char* str_runner = (char*)str;
	
	assert(NULL != str);

	while ('\0' != *str_runner)
	{
		++str_runner;
	}
	
	return str_runner - str;
}


int StrCmp(const char* str1, const char*str2)
{
	assert(NULL != str1);
	assert(NULL != str2);
	
	while ('\0' != *str1 && *str1 == *str2)
	{
		++str1; ++str2;
	}
	return (*str1 - *str2);
}


char* StrCpy(char* dest, const char* src)
{
	char* dest_runner = dest;	
	
	assert(NULL != src);
	
	while ('\0' != *src)
	{
		*dest_runner = *src;
		++dest_runner; ++ src;
	}
	
	*dest_runner = '\0';
	return dest;
}


char* StrCat(char* dest, const char* src)
{
	size_t i = 0;
	size_t dest_len = 0;
	char* dest_runner = dest;
	
	assert(NULL != src);
	
	dest_len = StrLen(dest);
	
	for (i = 0; i < dest_len; ++i)
	{
		++dest_runner;
	}
	
	StrCpy(dest_runner, src);
	return dest;
}


unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long i = 0;
	unsigned long prev = 1;
	unsigned long cur = 1;
	unsigned long fib = 0;
	
	if (1 >= n)
	{
		return 1;
	}
	
	for (i = 1; n > i; ++i)
	{
		fib = cur + prev;
		prev = cur;
		cur = fib;
	}
	return fib;
}


char ConvertIntToChar(int num)
{
	char digit = (char)(num + 48);
	return digit;	
}


char* ReverseString(char* str)
{
	int i = 0;
	char* rev_str = NULL;
	char temp = 0;
	int len = strlen(str);
	
	rev_str = (str + len -1);
	
	for (i = 0; i < (len / 2); ++i)
	{
		temp = *rev_str;
		*rev_str = *str;
		*str = temp;
		++str; --rev_str;
	}
	return rev_str;
}


char* Itoa(int num, char* dest)
{
	char* dest_runner = dest;
	int is_neg = 0;
	if (0 > num)
	{
		is_neg = 1;
		num = -num;
	}
	
	if (0 == num)
	{
		*dest_runner = '0';
		++dest_runner;
		*dest_runner = '\0';
		return dest;
	}
	
	while (0 != num)
	{
		*dest_runner = ConvertIntToChar(num % 10);
		num /= 10;
		++dest_runner;
	}
	
	if (is_neg)
	{
		*dest_runner = '-';
		++dest_runner;
	}
	
	*dest_runner = '\0';
	ReverseString(dest);
	return dest;
}


unsigned int MulByEight(unsigned int num)
{
	return num << 3;
}


void foo1()
{
	char *s1 = "hello";
	char s2[] = "hello";
/*	char *s3 = s1;
*/	
	printf("16. functions output is: %lu, %lu, %lu, %lu\n", sizeof(s1), sizeof(s2), strlen(s1), strlen(s2));
/*	
	s3[0] = 'H';
	printf("%s\n", s3);
*/
}


void foo2()
{
	size_t array[] = {0, 1, 2, 3, 4, 5};
	size_t val = 3;
	printf("17. functions output is: %lu\n", val[array]);
}


/*------------------------------------------------------------------------------------------------------*/
/******************************************** TEST FUNCTIONS ********************************************/
/*------------------------------------------------------------------------------------------------------*/

void FlipDigitsTest(void)
{
	int num1 = 3322;
	int num2 = 5;
	int num3 = 202;
	int num4 = -200;
	int num5 = -19;
	int num6 = 63;
	int num7 = 12;
	int num8 = 0;
	
	printf("started " CYAN "FLIP DIGIT" RESET_COLOR " test\n");
	
	if (2233 != FlipDigitsInNum(num1) || 
	       5 != FlipDigitsInNum(num2) || 
	     202 != FlipDigitsInNum(num3) ||
	      -2 != FlipDigitsInNum(num4) ||
	     -91 != FlipDigitsInNum(num5) ||
	      36 != FlipDigitsInNum(num6) ||
	      21 != FlipDigitsInNum(num7) ||
	       0 != FlipDigitsInNum(num8))
	{
		printf(RED "flip number digits FAILED\n\n" RESET_COLOR);
		return;
	}

	printf(GREEN "flip number digits PASSED\n\n" RESET_COLOR);
}


void MirrorTest(void)
{
	unsigned char byte1 = 0xF0;
	unsigned char byte2 = 0xAA;
	unsigned char byte3 = 0x10;
	unsigned char byte4 = 0x02;
	unsigned char byte5 = 0x18;
	unsigned char byte6 = 0x00;
	unsigned char byte7 = 0xFF;
	unsigned char byte8 = 0xB7;
	
	printf("started " CYAN "MIRROR" RESET_COLOR " test\n");
	
	if (0x0F != MirrorByte(byte1) || 
	    0x55 != MirrorByte(byte2) || 
	    0x08 != MirrorByte(byte3) ||
	    0x40 != MirrorByte(byte4) ||
	    0x18 != MirrorByte(byte5) ||
	    0x00 != MirrorByte(byte6) ||
	    0xFF != MirrorByte(byte7) ||
	    0xED != MirrorByte(byte8))
	{
		printf(RED "mirror FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "mirror PASSED\n\n" RESET_COLOR);

}


void FlipBitTest(void)
{
	int byte1 = 0xF0;
	int byte2 = 0xAA;
	int byte3 = 0x10;
	int byte4 = 0x02;
	int byte5 = 0x18;
	int byte6 = 0x00;
	int byte7 = 0xFF;
	int byte8 = 0xB7;
	
	printf("started " CYAN "FLIP BIT" RESET_COLOR " test\n");
	
	if (0xD0 != FlipBit(byte1, 5) || 
	    0xA2 != FlipBit(byte2, 3) || 
	    0x12 != FlipBit(byte3, 1) ||
	    0x06 != FlipBit(byte4, 2) ||
	    0x08 != FlipBit(byte5, 4) ||
	    0x80 != FlipBit(byte6, 7) ||
	    0x7F != FlipBit(byte7, 7) ||
	    0xB6 != FlipBit(byte8, 0))
	{
		printf(RED "flip bit FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "flip bit PASSED\n\n" RESET_COLOR);
}


void CntBitsTest(void)
{
	unsigned char byte1 = 0xF0;
	unsigned char byte2 = 0xAA;
	unsigned char byte3 = 0x10;
	unsigned char byte4 = 0x02;
	unsigned char byte5 = 0x18;
	unsigned char byte6 = 0x00;
	unsigned char byte7 = 0xFF;
	unsigned char byte8 = 0xB7;
	
	printf("started " CYAN "COUNT ON BITS" RESET_COLOR " test\n");
	
	if (4 != CountOnBits(byte1) || 
	    4 != CountOnBits(byte2) || 
	    1 != CountOnBits(byte3) ||
	    1 != CountOnBits(byte4) ||
	    2 != CountOnBits(byte5) ||
	    0 != CountOnBits(byte6) ||
	    8 != CountOnBits(byte7) ||
	    6 != CountOnBits(byte8))
	{
		printf(RED "count on bits FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "count on bits PASSED\n\n" RESET_COLOR);
}


void RotateTest(void)
{
	unsigned char byte1 = 0xF0;
	unsigned char byte2 = 0xAA;
	unsigned char byte3 = 0x10;
	unsigned char byte4 = 0x02;
	unsigned char byte5 = 0x18;
	unsigned char byte6 = 0x00;
	unsigned char byte7 = 0xFF;
	unsigned char byte8 = 0xB7;
	
	printf("started " CYAN "ROTATE" RESET_COLOR " test\n");
	
	if (0x1E != RotateLeft(byte1, 5) || 
	    0x55 != RotateLeft(byte2, 3) || 
	    0x20 != RotateLeft(byte3, 1) ||
	    0x08 != RotateLeft(byte4, 2) ||
	    0x81 != RotateLeft(byte5, 4) ||
	    0x00 != RotateLeft(byte6, 7) ||
	    0xFF != RotateLeft(byte7, 7) ||
	    0xB7 != RotateLeft(byte8, 0))
	{
		printf(RED "rotate FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "rotate PASSED\n\n" RESET_COLOR);
}


void SwapPointersTest(void)
{
	int num1 = 1;
	int num2 = 2;
	int* p1 = &num1;
	int* p2 = &num2;
	
	printf("started " CYAN "SWAP POINTERS" RESET_COLOR " test\n");
	
	SwapPointers(&p1, &p2);
	
	if (1 != num1 || 2 != num2 || 2 != *p1 || 1 != *p2)
	{
		printf(RED "swap pointers FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "swap pointers PASSED\n\n" RESET_COLOR);
}


void StrLenTest(void)
{
	char* str1 = "3rvf322";
	char* str2 = "5sgwbr";
	char* str3 = "";
	char* str4 = "-sv20adv0";
	char* str5 = "-1kjdoin  jsd p9";
	char* str6 = "6 sdij skdkjs d jPOj po3";
	char* str7 = "12#$^#%@&@ ek42 6264@^@";
	char* str8 = "0";
	
	printf("started " CYAN "STRLEN" RESET_COLOR " test\n");
	
	if (StrLen(str1) != strlen(str1) ||
	    StrLen(str2) != strlen(str2) ||
	    StrLen(str3) != strlen(str3) ||
	    StrLen(str4) != strlen(str4) ||
	    StrLen(str5) != strlen(str5) ||
	    StrLen(str6) != strlen(str6) ||
	    StrLen(str7) != strlen(str7) ||
	    StrLen(str8) != strlen(str8))
	{
	    	printf(RED "StrLen FAILED\n\n" RESET_COLOR);
		return;
	}
	printf(GREEN "StrLen PASSED\n\n" RESET_COLOR);
}


void StrCmpTest(void)
{
	char* str1 = "-sv20adv0pfna;fklma;sfm";
	char* str2 = "5sgwbr";
	char* str3 = "";
	char* str4 = "sv20adv0";
	char* str5 = "-1kjdoin  jsd p9";
	char* str6 = "6 sdij skdkjs d jPOj po3";
	char* str7 = "-sv20adv0pfna;fklma;sfm";
	char* str8 = "";
	
	printf("started " CYAN "STRCMP" RESET_COLOR " test\n");
	
	if ((0 == StrCmp(str4, str8)) != (0 == strcmp(str4, str8)) ||
	    (0 >  StrCmp(str2, str4)) != (0 >  strcmp(str2, str4)) ||
	    (0 >  StrCmp(str3, str5)) != (0 >  strcmp(str3, str5)) ||
	    (0 == StrCmp(str3, str8)) != (0 == strcmp(str3, str8)) ||
	    (0 <  StrCmp(str6, str3)) != (0 < strcmp(str6, str3)) ||
	    (0 == StrCmp(str7, str1)) != (0 == strcmp(str7, str1)) ||
	    (0 <  StrCmp(str7, str5)) != (0 <  strcmp(str7, str5)) ||
	    (0 <  StrCmp(str7, str4)) != (0 <  strcmp(str7, str4)))
	{
	    	printf(RED "StrCmp FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "StrCmp PASSED\n\n" RESET_COLOR);
}


void StrCpyTest(void)
{
	char* buffer = (char*)malloc(10);
	char* str1 = "sv20adv0";
	char* str2 = "5sgwbr";
	char* str3 = "";
	
	printf("started " CYAN "STRCPY" RESET_COLOR " test\n");
	
	StrCpy(buffer, str1);
	if (strcmp(str1, buffer))
	{
		printf(RED "StrCpy FAILED1\n\n" RESET_COLOR);
		return;
	}
	
	StrCpy(buffer, str2);
	if (strcmp(str2, buffer))
	{
		printf(RED "StrCpy FAILED2\n\n" RESET_COLOR);
		return;
	}
	
	StrCpy(buffer, str3);
	if (strcmp(str3, buffer))
	{
		printf(RED "StrCpy FAILED3\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "StrCpy PASSED\n\n" RESET_COLOR);
	free(buffer);
}


void StrCatTest(void)
{
	char* buffer = (char*)malloc(20);
	char* str1 = "sv20adv0";
	char* str2 = "5sgwbr";
	char* str3 = "sv20adv05sgwbr";
	
	*buffer = '\0';
	
	printf("started " CYAN "STRCAT" RESET_COLOR " test\n");
	
	buffer = StrCat(buffer, str1);
	buffer = StrCat(buffer, str2);
	if (strcmp(str3, buffer))
	{
		printf(RED "StrCat FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "StrCat PASSED\n\n" RESET_COLOR);
	free(buffer);
}


void FibonacciTest(void)
{
	printf("started " CYAN "FIBONACCI" RESET_COLOR " test\n");
	
	if (1  != GetNFibonacciElement(0) || 
	    1  != GetNFibonacciElement(1) || 
	    2  != GetNFibonacciElement(2) ||
	    3  != GetNFibonacciElement(3) ||
	    5  != GetNFibonacciElement(4) ||
	    8  != GetNFibonacciElement(5) ||
	    13 != GetNFibonacciElement(6) ||
	    21 != GetNFibonacciElement(7))
	{
		printf(RED "fibonacci FAILED\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "fibonacci PASSED\n\n" RESET_COLOR);
}


void ItoaTest(void)
{
	int num1 = 3322;
	int num2 = 5;
	int num3 = 202;
	int num4 = -200;
	int num5 = -19;
	int num6 = 63;
	int num7 = 12;
	int num8 = 0;
		
	char* char_num1 = "3322";
	char* char_num2 = "5";
	char* char_num3 = "202";
	char* char_num4 = "-200";
	char* char_num5 = "-19";
	char* char_num6 = "63";
	char* char_num7 = "12";
	char* char_num8 = "0";
	
	char* buffer = (char*)malloc(10);

	printf("started " CYAN "ITOA" RESET_COLOR " test\n");
	
	Itoa(num1, buffer);
	if (strcmp(char_num1, buffer))
	{
		printf(RED "itoa FAILED1\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num2, buffer);
	if (strcmp(char_num2, buffer))
	{
		printf(RED "itoa FAILED2\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num3, buffer);
	if (strcmp(char_num3, buffer))
	{
		printf(RED "itoa FAILED3\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num4, buffer);
	if (strcmp(char_num4, buffer))
	{
		printf(RED "itoa FAILED4\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num5, buffer);
	if (strcmp(char_num5, buffer))
	{
		printf(RED "itoa FAILED5\n\n" RESET_COLOR);
		return;
	}
	Itoa(num6, buffer);
	if (strcmp(char_num6, buffer))
	{
		printf(RED "itoa FAILED6\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num7, buffer);
	if (strcmp(char_num7, buffer))
	{
		printf(RED "itoa FAILED7\n\n" RESET_COLOR);
		return;
	}
	
	Itoa(num8, buffer);
	if (strcmp(char_num8, buffer))
	{
		printf(RED "itoa FAILED8\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "itoa PASSED\n\n" RESET_COLOR);
	free(buffer);
}


void MulBy8Test(void)
{
	unsigned int num1 = 3322;
	unsigned int num2 = 5;
	unsigned int num3 = 202;
	unsigned int num4 = 200;
	unsigned int num5 = 19;
	unsigned int num6 = 63;
	unsigned int num7 = 12;
	unsigned int num8 = 0;
	
	printf("started " CYAN "MULTIPLY BY 8" RESET_COLOR " test\n");
	
	if ((3322 * 8) != MulByEight(num1) || 
	       (5 * 8)!= MulByEight(num2) || 
	     (202 * 8) != MulByEight(num3) ||
	      (200 * 8) != MulByEight(num4) ||
	     (19 * 8) != MulByEight(num5) ||
	      (63 * 8) != MulByEight(num6) ||
	      (12 * 8) != MulByEight(num7) ||
	       (0 * 8) != MulByEight(num8))
	{
		printf(RED "multiply by 8 FAILED\n\n" RESET_COLOR);
		return;
	}

	printf(GREEN "multiply by 8 PASSED\n\n" RESET_COLOR);
}


/*--------------------------------------------------------------------------------------------*/
/******************************************** MAIN ********************************************/
/*--------------------------------------------------------------------------------------------*/


int main()
{	
	union
	{
		char array[7];
		int i;
		short s;
	}jack;
	
	printf("\n");	
	
	FlipDigitsTest();
	MirrorTest();
	FlipBitTest();
	CntBitsTest();
	RotateTest();
	SwapPointersTest();
	StrLenTest();
	StrCmpTest();
	StrCpyTest();
	StrCatTest();
	FibonacciTest();
	ItoaTest();
	MulBy8Test();
	foo1();
	foo2();
	
	printf("23. size of Jack is : %ld\n", sizeof(jack));
	
	return 0;
}




