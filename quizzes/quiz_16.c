#include <stddef.h>
#include <stdio.h>

int BitwiseAddOne(int num)
{
	size_t mask = 1;
	while(num & mask)
	{
		num ^= mask;
		mask <<=1;
	}
	return num | mask;
}

int BitwiseAddOne2comp(int num)
{
	return -(~num);
}


int main()
{
	int num1 = 1;	
	int num2 = 5;
	int num3 = 28;
	int num4 = 2687;
	int num5 = 99999;
	
	num1 = BitwiseAddOne(num1);
	num2 = BitwiseAddOne(num2);
	num3 = BitwiseAddOne(num3);
	num4 = BitwiseAddOne(num4);
	num5 = BitwiseAddOne(num5);
	
	printf("num1 is now : %d\n", num1);
	printf("num2 is now : %d\n", num2);
	printf("num3 is now : %d\n", num3);
	printf("num4 is now : %d\n", num4);
	printf("num5 is now : %d\n", num5);
	
	num1 = BitwiseAddOne2comp(num1);
	num2 = BitwiseAddOne2comp(num2);
	num3 = BitwiseAddOne2comp(num3);
	num4 = BitwiseAddOne2comp(num4);
	num5 = BitwiseAddOne2comp(num5);
	
	printf("num1 is now : %d\n", num1);
	printf("num2 is now : %d\n", num2);
	printf("num3 is now : %d\n", num3);
	printf("num4 is now : %d\n", num4);
	printf("num5 is now : %d\n", num5);
	
	return 0;
}

