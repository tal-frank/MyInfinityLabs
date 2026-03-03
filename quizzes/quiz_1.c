
/* #include <stdio.c>  */
#include <stdio.h>

/* void Main(int argc, char* argv[])   */
int main(int argc, char* argv[])
{
	int num;
	const int num2 = 6;
	const int num3;
	char ch = 97; /* is not used & was at line 16 where C90 can not compile a decleration after code  */
	
	printf("%d\n" , num); /* num is used uninitialized  */
	scanf("%d" , &num);  /* expect a pointer and not an int. added "&" to make it an address */
	printf("100 divided by %d id %f\n" , num , 100.0/num); /* added ".0" to the 100 so it would become a float */
	
	
/*	num3 = num2 - 5;   trying to overwrite const (read only)   */
	printf("%f", num3);  /* num is used uninitialized & float vs int */
	
	num = 4.7;
/*	(double)num = 4.7;  trying to cast an lvalue, cast only has an effects at the same line it operates on */
	
	num = 2 * num++; /* the operator "++" may have an undefined behavior */
	
	printf("\n");
	
	if (-1 < (unsigned char)1)
	{
		printf("A\n");
	}
	else
	{
		printf("B\n");
	}
	
	if (-1 < (unsigned int)1)
	{
		printf("A\n");
	}
	else
	{
		printf("B\n");
	}
	
	return(0);
}









