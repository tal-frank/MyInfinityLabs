# include "exp.h"

int main()
{
	int i;
	int new_num;
	int a = 8;
	int b = 2;
	int* ptr_a = &a;
	int* ptr_b = &b;
	double pow = 0;
	
	HelloWorld();
	printf("\n");
	printf("\n");
	
	for (i = -10; i < 11; ++i)
	{
		pow = PowTen(i);
		printf("%f", pow);
		printf("\n");
	}
	
	new_num = FlipDigits(135790);
	printf("%d" , new_num);
	printf("\n");
	
	printf("\n\n");
	printf("a = %d , b = %d \n" , a, b);
	SwapVars(ptr_a, ptr_b);
	printf("a = %d , b = %d \n" , a, b);
	
}
