#include <stdlib.h> 
#include <assert.h> 
#include <stdio.h>

int main()
{

/*	int* p = (int*)17;
	printf("%d", (int)(long)(p+4));
	printf("\n\n");
*/
	
/*	size_t i = 3;
	size_t array[] = {0,1,2,3,4,5};
	printf("%lu", i[array]);
	printf("\n\n");
*/	
	
/*	unsigned int* ip = 0;
	float f = 3;
	float* fp = &f;
	ip = (unsigned int *)fp;
	printf("%u", *ip);
	printf("\n");
*/

	const char * str1 = NULL;
	char const * str2;
	char * const str3 = NULL;
	char* str4 = NULL;
	char* const str5;
	
	str1 = str2; 
	str2 = str3; 
	str4 = str3; 
	str3 = str4; 
	str2 = str4; 
	str4 = str2; 
	str5 = str4; 
}
