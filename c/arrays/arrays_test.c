#include "arrays.h"



int main(int argc, char* argv[], const char* envp[])
{	
	int dest[3];
	int rows = 3, cols = 4;
	int matrix[][4] = {{1,2,3,4},
			   {5,6,7,8},
			   {3,4,5,6}};
			   
	TwoD((int*)matrix, dest ,rows, cols);
	
	
	if (dest[0] == 10)
	{
		printf("PASSED1! dest[0] = %d\n", dest[0]);
	}
	else 
	{
		printf("FAILED1! dest[0] = %d\n", dest[0]);
	}
	if (dest[1] == 26)
	{
		printf("PASSED2! dest[0] = %d\n", dest[1]);
	}
	else 
	{
		printf("FAILED2! dest[0] = %d\n", dest[1]);
	}
	if (dest[2] == 18)
	{
		printf("PASSED3! dest[0] = %d\n", dest[2]);
	}
	else 
	{
		printf("FAILED3! dest[0] = %d\n", dest[2]);
	}
	
	
	if (Jusephus(0, 2) == instantJuseph(2))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(2), Jusephus(2, 0));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(2), Jusephus(2, 0));
	}
	
	if (Jusephus(0, 3) == instantJuseph(3))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(3), Jusephus(0, 3));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(3), Jusephus(0, 3));
	}
	
	if (Jusephus(0, 4) == instantJuseph(4))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(4), Jusephus(0, 4));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(4), Jusephus(0, 4));
	}
	
	if (Jusephus(0, 5) == instantJuseph(5))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(5), Jusephus(0, 5));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(5), Jusephus(0, 5));
	}
	
	if (Jusephus(0, 6) == instantJuseph(6))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(6), Jusephus(0, 6));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(6), Jusephus(0, 6));
	}
	
	if (Jusephus(0, 7) == instantJuseph(7))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(7), Jusephus(0, 7));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(7), Jusephus(0, 7));
	}
	if (Jusephus(0, 8) == instantJuseph(8))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(8), Jusephus(0, 8));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(8), Jusephus(0, 8));
	}
	
	if (Jusephus(0, 9) == instantJuseph(9))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(9), Jusephus(0, 9));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(9), Jusephus(0, 9));
	}
	
	if (Jusephus(0, 10) == instantJuseph(10))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(10), Jusephus(0, 10));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(10), Jusephus(0, 10));
	}
	
	if (Jusephus(0, 11) == instantJuseph(11))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(11), Jusephus(0, 11));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(11), Jusephus(0, 11));
	}
	
	if (Jusephus(0, 12) == instantJuseph(12))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(12), Jusephus(0, 12));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(12), Jusephus(0, 12));
	}
	
	if (Jusephus(0, 3478) == instantJuseph(3478))
	{
		printf("expected: %lu\nactual: %lu\nPASSED\n" , instantJuseph(3478), Jusephus(0, 3478));
	}
	else
	{
		printf("expected: %lu\nactual: %lu\nFAILED\n" , instantJuseph(3478), Jusephus(0, 3478));
	}
	
	PrintEnv(envp);
	
	
}
