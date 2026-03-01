/**********************
 * ws6_files
 * Author: Tal Frank
 * Reviewer: Name
**********************/

#include <string.h>

long Pow2(unsigned int x, unsigned int y)
{
	long pow;
	pow = x << y;
	return pow;
}

int IsPowOf2Loop(unsigned int n)
{
	unsigned int i;
	int cnt = 0;
	for (i = 0; i < 8 * sizeof(unsigned int); ++i)
	{
		if (n & 1)
		{
			++cnt;
		}
		n = n >> 1;
	}
	if (1 == cnt)
	{
		return 1;
	}
	return 0;
}


int IsPowOf2(unsigned int n)
{
	unsigned int fst_round;
	unsigned int sec_round;
	unsigned int thrd_round;
	unsigned int frth_round;
	unsigned int fifth_round;
	unsigned int a0;
	unsigned int a1;
	
	fst_round = 0x55555555;
	sec_round = 0x33333333;
	thrd_round = 0x0F0F0F0F;
	frth_round = 0x00FF00FF;
	fifth_round = 0x0000FFFF;
	
	a0 = fst_round & n;
	a1 = fst_round & n >> 1;
	n = a0 + a1;
	
	a0 = sec_round & n;
	a1 = sec_round & n >> 2;
	n = a0 + a1;
	
	a0 = thrd_round & n;
	a1 = thrd_round & n >> 4;
	n = a0 + a1;
	
	a0 = frth_round & n;
	a1 = frth_round & n >> 8;
	n = a0 + a1;
	
	a0 = fifth_round & n;
	a1 = fifth_round & n >> 16;
	n = a0 + a1;
	
	if (1 == n)
	{
		return 1;
	}
	return 0;

}


int Add1(int n)
{
	size_t i;
	int tmp;
	int add;
	
	tmp = n;
	add = 1;
	
	for (i = 0; i < 8 * sizeof(int); ++i)
	{
		if (tmp & 1)
		{
			n = n ^ add;
		}
		else
		{
			n = n | add;
			return n;
			break;
		}
		tmp = tmp >> 1;
		add = add << 1;
	}
	return n;
}

unsigned char Add1Char(unsigned char n)
{
	size_t i;
	unsigned char tmp;
	unsigned char add;
	
	tmp = n;
	add = 1;
	
	for (i = 0; i < 8 * sizeof(unsigned char); ++i)
	{
		if (tmp & 1)
		{
			n = n ^ add;
		}
		else
		{
			n = n | add;
			return n;
			break;
		}
		tmp = tmp >> 1;
		add = add << 1;
	}
	return n;
}


void PrintNumsWith3BitsOn(unsigned int* arr, size_t size)
{
	size_t i;
	size_t j;
	int cnt;
	unsigned int check = 1;
	
	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < 8 * sizeof(unsigned int); ++j)
		{
			if (arr[i] & check)
			{
				++cnt;
			}
			check = check << 1;
		}
		if (3 == cnt)
		{
			printf("arr[%lu]%d\n" , i, arr[i]);
		}
		cnt = 0;
		check = 1;
	}
}



unsigned char ByteMirrorLoop(unsigned char byte)
{
	int i;	
	unsigned char start;
	unsigned char end;
	unsigned char mirrored = 0;
	
	start = 0x01;
	end = 0x80;
	
	for (i = 0; i < 8; ++i)
	{
		if (byte & end)
		{
			mirrored = mirrored | start;
		}
		start = start << 1;
		end = end >> 1;
	}	
	return mirrored;
}

unsigned char ByteMirror(unsigned char byte)
{
	unsigned char mirrored;
	mirrored = ((byte & 0x01) << 7)
		 | ((byte & 0x02) << 5)
		 | ((byte & 0x04) << 3)
		 | ((byte & 0x08) << 1)
		 | ((byte & 0x10) >> 1)
		 | ((byte & 0x20) >> 3)
		 | ((byte & 0x40) >> 5)
		 | ((byte & 0x80) >> 7);
	
	return mirrored;
}



int IsSecondAndSixthBitOn(unsigned char byte)
{
	int sec;
	int sixth;
	
	sec = 1 << 1;
	sixth = 1 << 5;
	
	return (byte & sec) && (byte & sixth);
}


int IsSecondOrSixthBitOn(unsigned char byte)
{
	int sec;
	int sixth;
	
	sec = 1 << 1;
	sixth = 1 << 5;
	
	return (byte & sec) || (byte & sixth);
}



unsigned char SwapThirdAndFifthBits(unsigned char byte)
{
	unsigned char swap3_5;
	swap3_5 = (byte & 0x01)
		 | (byte & 0x02)
		 | ((byte & 0x04) << 2)
		 | (byte & 0x08)
		 | ((byte & 0x10) >> 2)
		 | (byte & 0x20)
		 | (byte & 0x40)
		 | (byte & 0x80);
	
	return swap3_5;
}



unsigned int MaxDivisedBy16(unsigned char byte)
{
	unsigned char fourth_bit;
	unsigned char divide_16;
	
	fourth_bit = 1 << 3;
	divide_16 = 15;
	
	if (byte & fourth_bit)
	{
		byte = byte | divide_16;
		byte = Add1Char(byte);
	}
	else
	{
		byte = byte & ~divide_16;
	}
	return byte;
}


void SwapVars(int* a, int* b)
{
	*a = *a << 16;	
	*b = *b | *a;
	*a = *b | *a;
	*a = *a & 0x0000FFFF;
	*b = *b >> 16;
}



void SwapVarsV2(int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


/*
void SwapVarsV3(int* a, int* b);
*/


unsigned int CountSetBitsLoop(unsigned int byte)
{
	size_t i;
	unsigned int cnt;
	unsigned int check = 1;
	
	cnt = 0;
	
	for (i = 0; i < 8 * sizeof(unsigned int); ++i)
	{
		if (byte & check)
		{
			++cnt;
		}
		check = check << 1;
	}
	return cnt;
}


unsigned int CountSetBits(unsigned int num)
{
	unsigned int fst_round;
	unsigned int sec_round;
	unsigned int thrd_round;
	unsigned int frth_round;
	unsigned int fifth_round;
	unsigned int a0;
	unsigned int a1;
	
	fst_round = 0x55555555;
	sec_round = 0x33333333;
	thrd_round = 0x0F0F0F0F;
	frth_round = 0x00FF00FF;
	fifth_round = 0x0000FFFF;
	
	a0 = fst_round & num;
	a1 = fst_round & num >> 1;
	num = a0 + a1;
	
	a0 = sec_round & num;
	a1 = sec_round & num >> 2;
	num = a0 + a1;
	
	a0 = thrd_round & num;
	a1 = thrd_round & num >> 4;
	num = a0 + a1;
	
	a0 = frth_round & num;
	a1 = frth_round & num >> 8;
	num = a0 + a1;
	
	a0 = fifth_round & num;
	a1 = fifth_round & num >> 16;
	num = a0 + a1;
	
	return num;
}

void FloatAnalysis(float num)
{
	size_t i;
	size_t bit;
	int print_float;
	int* print_float_ptr;
	float* num_ptr;
	
	print_float_ptr = &print_float;
	num_ptr = &num;
	
	memcpy(print_float_ptr, num_ptr, 4);
	
	for (i = 0; i < 8 * sizeof(int); ++i)
	{
		bit = (8 * sizeof(int) - 1 -i);
		printf("%d", ((print_float) >> bit) & 1);
	}
	printf("\n");
}











