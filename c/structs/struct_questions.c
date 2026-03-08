#include <stdio.h>

struct point
{
	int x;
	int y;
};


union numbers
{
	int i;
	float f;
	double d;
};

struct X
{
	int i;
	char c;
	double d;
	short s;
};

struct card
{
	unsigned int suit : 2;
	unsigned int face_value : 4;
};


int main(void)
{
	struct point p = {1, 2};
	int n = *(int *)&p;
	
	printf("%ld\n" , sizeof(union numbers));
	printf("%ld\n" , sizeof(struct X));
	printf("%ld\n" , sizeof(struct card));
	printf("%d\n", n);
	
	return 0;
}











