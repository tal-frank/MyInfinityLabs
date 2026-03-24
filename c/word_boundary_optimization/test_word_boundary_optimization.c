#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy , memset , memmove , memcmp*/

#include "word_boundary_optimization.h"

#define DISALIGNMENT (4)

int main()
{
	char* str1 = "one long and complicated string that will have some words";
	char* str2 = (char*)malloc(BUFSIZ);
	char* str3 = (char*)malloc(BUFSIZ);
	char* str4 = (char*)malloc(BUFSIZ);
	char* str5 = (char*)malloc(BUFSIZ);
	
	MemCpy(str3, str1, 58);
	MemCpy(str4, str1, 58);
	MemCpy(str5, str1, 58);
	
	str1 += DISALIGNMENT;
	str2 += DISALIGNMENT;
	str3 += DISALIGNMENT;
	
	MemCpy(str2, str1, 29);

	MemSet(str3, '#', 16);
	
	MemMove((str4 + 7), (str4 + 15), 28);
	MemMove((str5 + 7), (str5 + 15), 28);
	
	printf("str2 after MemCpy = %s\n", str2);
	printf("str3 after MemSet = %s\n", str3);
	printf("str4 after MemMove = %s\n", str4);
	printf("str5 after memmove = %s\n", str5);
	
	
	if (0 == memcmp(str4, str5, 58))
	{
		printf("MemMove PASSED\n");
	}
	else
	{
		printf("MemMove FAILED\n");
	}
	
	str2 -= DISALIGNMENT;
	str3 -= DISALIGNMENT;
	free(str2);
	free(str3);
	free(str4);
	
	return 0;
}

