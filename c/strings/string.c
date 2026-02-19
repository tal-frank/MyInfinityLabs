#include "string.h"
#include <ctype.h>
#include <stdio.h> /* Needed for I/O operations */
#include <stdlib.h>
#include <assert.h>


size_t StrLen(const char* str)
{
	int len_cnt = 0;
	while (*str != '\0')
	{
		len_cnt += 1;
		str++;
	}
	
	return len_cnt;
}


char* StrCpy (char* dest, const char* src)
{
	
	while (*src != '\0')
	{
		*dest = *src;
		dest++;	src++;
	}
	*dest = '\0';
	return dest;
}

char* StrNCpy (char* dest, const char* src, size_t n)
{
	size_t size = 0;
	while (*src != '\0' && n > size)
	{	
		*dest = *src;
		dest++;	src++; size++;
	}
	for (; size < n; size++)
	{
		*dest = '\0';
		dest++;
	}
	return dest;
}


int StrCmp(const char* str1, const char* str2)
{
	while (*str1 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++; str2++;
	}
	return (*str1 - *str2);
}

int StrNCmp(const char* str1, const char* str2, size_t n)
{
	size_t cnt = 0;
	if (str1 == NULL || str2 == NULL)
	{
		return (*str1 - *str2);
	}
	while (*str1 != '\0' && cnt < n - 1)
	{
		cnt++;
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++; str2++;	
	}
	return (*str1 - *str2);
}


int StrCaseCmp(const char* s1, const char* s2)
{ 
	while (*s1 != '\0')
	{	
		if (tolower(*s1) != tolower(*s2))
		{
			return (*s1 - *s2);
		}
		s1++; s2++;
	}
	return(*s1 - *s2);
}


char* StrChr(const char* str, int ch)
{
	while (*str != '\0')
	{
		if (*str == (char)ch)
		{
			return (char*)str;
		}
		str++;
	}
	return '\0';
}


char* StrDup(const char* src)
{
	size_t size = StrLen(src);
	char* dest;
	dest = (char*)malloc(sizeof(char) * size);
	while (*src != '\0')
	{
		*dest = *src;
		dest++; src++;
	}
	*dest = *src;
	return dest;
}



char* StrCat(char* dest, const char* src)
{	
	char* real_dest = dest;
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src; 
		src++; dest++;
	}
	*dest = '\0';
	return real_dest;
}

char* StrNCat(char* dest, const char* src, size_t cnt)
{
	char* real_dest = dest;
	size_t size = 0;
	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		if (size >= cnt)
		{
			*dest = '\0';
			break;
		}
		*dest = *src; 
		src++; dest++; size++;
	}
	return real_dest;
}



char* StrStr(const char* str, const char* substr)
{
	int is_equal_str;
	size_t substr_len = StrLen(substr);
	char* search_for_char = (char*)str;
	while (search_for_char != NULL)
	{
		search_for_char = StrChr(search_for_char, (int)*substr);		
		if (search_for_char == NULL)
		{
			return '\0';
		}		
		is_equal_str = StrNCmp(search_for_char, substr, substr_len);
		if (is_equal_str == 0)
		{
			return (char*)search_for_char;
		}
		search_for_char++; 
	}
	return (char*)search_for_char;
}



size_t StrSpn(const char* dest, const char* search)
{
	int cnt = 0;
	char* char_in_search = StrChr(search, *dest);
	while (char_in_search != NULL && *dest != '\0')
	{
		dest++; cnt++;
		char_in_search = StrChr(search, *dest);
	}
	return cnt;	
}

char* StrTok(char* str, const char* delim)
{
	int is_delim;
	static char* str_ptr;
	str_ptr = str;
	if (*str != '\0')
	{
		str_ptr = str;
	}
	while (*str_ptr != '\0')
	{
		is_delim = StrSpn(str_ptr, delim);
		if (is_delim)
		{
			*str_ptr = '\0';
			return str;
		}
		str_ptr++;
	}
	return '\0';

}



int IsPalindrome(const char* str)
{
	int i;
	int length = StrLen(str);
	char* end_ptr;
	end_ptr = (char*)(str + length);
	for (i = 0; i < (length / 2); ++i)
	{
		if (*(str + i) == *(end_ptr - i))
		{
			return 1;
		}
	}
	return 0;
} 


/* void Print7Boom(int from, int to); 

void SpaceReview(char* dest, const char* src);*/





















