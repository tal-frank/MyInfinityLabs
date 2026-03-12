#include <stdio.h> 

int CountCouples(char num)
{
	int i = 0;
	int cnt_couples = 0;
	for (i = 0; i < 6; ++i)
	{
		if ((3 << i) == (num & (3 << i)))
		{
			++cnt_couples;
		}
	}
	return cnt_couples;
}

void SwapNums1(int* num1, int* num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

void SwapNums2(int* num1, int* num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}

void SwapNums3(int* num1, int* num2)
{
	*num1 = (*num1 << 16) + *num2;
	*num2 = *num1 >> 16;
	*num1 = *num1 & 0x0000FFFF;
}

int NumSetBits(long num)
{
	int set_bit_cnt = 0;
	while (0 != num)
	{
		num = num & (num - 1);
		++set_bit_cnt;
	}
	return set_bit_cnt;
}

int main()
{
	int coupled_bits = 0;
	int set_bits = 0;
	int num1 = 8;
	int num2 = 13;
	char num3 = 27;
	long num4 = 15;
	
	coupled_bits = CountCouples(num3);
	SwapNums1(&num1, &num2);
	set_bits = NumSetBits(num4);
	
	printf("nunmber of coupled bit in %d is : %d\n", num3, coupled_bits);
	printf("num1 is : %d\nnum2 is : %d\n", num1, num2);
	printf("number of set bits in %ld is : %d\n" , num4, set_bits);
	
	return 0;
}




