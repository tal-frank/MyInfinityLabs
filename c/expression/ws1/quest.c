#include <stdio.h>

long l = 8;
long* foo()
{
	return &l;
}

int main()
{

	int x = 20 , y = 35;
	int a = 3, b = 4, c, d; c = ++a; d = b++;
	printf("a=%d , b=%d , c=%d, d=%d" , a , b , c , d);
	printf("\n\n");
	*(foo()) = 5;
	printf("%ld\n", l);
	return (0);
	
	x = y++ + x++;
	y = ++y + ++x;
	printf("%d%d" , x, y);
	printf("/n/n");
	
	
}
