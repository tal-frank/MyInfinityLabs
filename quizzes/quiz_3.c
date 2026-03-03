#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* was missing for ""touapper" function */
#include <string.h>

int main()
{
	char *str1 = "hello"; /* makes constant string */
/*	char str2[strlen(str1)] can't have a variable to dictate the length of a string */	
	char* str2 = (char*)malloc(strlen(str1) + 1);  /* has to be malloced */
	char *str3 = (char*)malloc(strlen(str1) + 1);
	
	strcpy(str2, str1); /* was at line 20 and therefor was copied blank because str1 was at the end of the string */
	
	while (*str1)
	{
		*str3 = *str1;
		++str3;
		++str1;
	}
	
	
	str3 -= strlen(str2); /* wasn't existed. had to be returned to the first place it was for freeing the memory  */
	
	if (islower(*str1))
	{
		*str1 = toupper(*str1);
	}
	
	free(str2); /* free to malloc that wasn;t existed before */
	free(str3);
	str2 = NULL;
	str3 = NULL;
	
	return 0; /* was missing a return to non void function */
}
 





