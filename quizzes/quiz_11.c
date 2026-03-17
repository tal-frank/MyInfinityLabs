#include <stdio.h>

#define MAX3(a, b, c) (a > b) && (a > c) ? (a) : (b > c) ? (b) : (c)
#define TO_LOWER(a) a > 'A' && a < 'Z' ? (a + 32) : (a)
#define OFFSET(s,f) (((char*)&s.f) - ((char*)&s))

union check2
{
	short num;
	char arr[5];
};

struct check
{
	char num;
	char a;
};

int main()
{
	union check2 un;
	struct check something;
	
	int a = 9;
	int b = 12;
	int c = 8;
	int max = MAX3(a, b, c);
	char ch = 'f';
	int offset = OFFSET(something, a);
	
	ch = TO_LOWER(ch);
	
	printf("offset is : %d\n", offset);
	printf("char after TO_LOWER is %c\n", ch);
	printf("max = %d\n", max);
	printf("the size is : %ld\n", sizeof(something));
	printf("the size is : %ld\n", sizeof(un));

	return 0;
}
