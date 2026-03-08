#include <stdio.h>
#include <stdlib.h>
/*
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

*/
int main(void)
{
	int g1;
	static int g2;
	static int g3 = 0;
	static int g4 = 8;


/*	struct point p = {1, 2};
	int n = *(int *)&p;
	
	printf("%ld\n" , sizeof(union numbers));
	printf("%ld\n" , sizeof(struct X));
	printf("%ld\n" , sizeof(struct card));
	printf("%d\n", n);
*/	
	return 0;

}

static void foo1()
{
	static int g5;
	int l1 = 9;
}



void foo2()
{
	static int g6 = 0;
	static int g7 = 7;
	
	void *p = malloc(10);
	free(p);
	p = 0;
}

extern void bar();


















