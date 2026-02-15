#include <stdio.h>

void HelloWorld()
{
	int i;
	int hello_world[]= {0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22} ;
	for (i = 0; i < 14; i++)
	{
		printf("%c", hello_world[i]);
	}
	printf("\n");
}

double PowTen(int n)
{
	int i;
	double sum = 1;
	double pow = 10;
	if (n<0)
	{
		n = -n;
		pow = 1/pow;
	}
	for (i = 0; i < n; ++i)
	{
		sum = sum * pow;
	}
	return sum;
	
}
	

int FlipDigits(int num)
{
	int newnum = 0;
	if (num < 0)
	{
		num = -num;
	}
	while (num != 0) 
	{
		newnum = newnum * 10;
		newnum = newnum + num % 10;
		num = num  / 10;	
	}
	printf("\n");
	
	return newnum;
}
	
	
void SwapVars(int* var1, int* var2)
{
	*var1 = *var1 + *var2;
	*var2 = *var1 - *var2;
	*var1 = *var1 - *var2;	
	
}
	
	
	
	
	
	
	
	
	
	


