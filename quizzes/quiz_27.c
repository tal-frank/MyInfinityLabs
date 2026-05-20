#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char* ReverseWordInSentence(char* str)
{
	int i = 0;
	size_t len = strlen(str);
	char* str_rev_begin = NULL;
	size_t num_chars_to_copy = 0;
	char* str_rev = (char*)malloc(sizeof(char) * len + 2);
	
	str_rev_begin = str_rev;
	str += len;
	for (i = len; i > 0; --i)
	{
		while (' ' != *str && i > 0)
		{
			--str; --i; ++num_chars_to_copy;
		}
		if (0 == i)
		{
			*str_rev = ' ';
			++str_rev;
		}
		memcpy(str_rev, str , num_chars_to_copy);

		str_rev += num_chars_to_copy;
		if (0 < i)
		{
			--str;
		}
		num_chars_to_copy = 1;
	}
	*str_rev = '\0';
	strcpy(str, str_rev_begin);
	str_rev = str_rev_begin;
	free(str_rev);
	return str;
}


int main()
{
	char* str = (char*)malloc(60);
	strcpy(str, "some insegnificant word to test for reversing");
	printf ("%s\n", str);
	ReverseWordInSentence(str);
	printf("%s\n", str);
	free(str);
	return 0;
}


