#include <assert.h>
#include <math.h>
#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

double Sqrt(double num)
{
	double inc = 4;
	double dec = 0.25;
	double num_sqrt = 1;
	
	assert(0 < num);
	
	if (0 == num)
	{
		return 0;
	}
	
	if (1 < num)
	{
		while (num_sqrt * num_sqrt > num + 0.0001 ||
		       num_sqrt * num_sqrt < num - 0.0001)
		{
			if (num_sqrt * num_sqrt < num)
			{
				num_sqrt += inc;
			}
			else
			{
				inc /= 2;
				num_sqrt -= inc;
			}
		}
	}
	else
	{
		while (num_sqrt * num_sqrt > num + 0.0001 ||
		       num_sqrt * num_sqrt < num - 0.0001)
		{
			if (num_sqrt * num_sqrt > num)
			{
				num_sqrt -= dec;
			}
			else
			{
				dec /= 2;
				num_sqrt += dec;
			}
		}
	}
	return num_sqrt;
}


void sqrt_test(double num)
{
	printf("%f:\n", num);
	if (sqrt(num) + 0.0002 > Sqrt(num) &&
	    sqrt(num) - 0.0002 < Sqrt(num))
	{
		printf(GREEN "SUCCESS\n" RESET_COLOR);
		printf("expected: %f\n", sqrt(num));
		printf("ectual  : %f\n\n", Sqrt(num));
		return;
	}
	printf(RED "FAILURE\n" RESET_COLOR);
	printf("expected: %f\n", sqrt(num));
	printf("ectual  : %f\n\n", Sqrt(num));
}

int main()
{
	printf("\n");
	sqrt_test(1);
	sqrt_test(1.02);
	sqrt_test(5);
	sqrt_test(25);
	sqrt_test(28.43);
	sqrt_test(5628);
	sqrt_test(785628);
	sqrt_test(57835628.65);
	sqrt_test(0.98);
	sqrt_test(0.77);
	sqrt_test(0.5);
	sqrt_test(0.3);
	sqrt_test(0.037);
	sqrt_test(0.03);
	sqrt_test(0.025);
	sqrt_test(0.02);
	sqrt_test(0.003);
	
	
	return 0;
}





