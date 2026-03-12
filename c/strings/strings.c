/**********************
* strings
* Author: Tal Frank
* Reviewer: Barak Koifmam
* Last update: 12/03/2026
**********************/

#include "strings.h"
#include <ctype.h>
#include <stdio.h> /* Needed for I/O operations */
#include <stdlib.h>
#include <assert.h>


size_t StrLen(const char* str)
{
	const char* init_str;
	
	assert(str);
	
	init_str = str;
	while ('\0' != *str)
	{
		++str;
	}	
	return (size_t)(str - init_str);
}


char* StrCpy (char* dest, const char* src)
{	
	char* real_dest;
	
	assert(dest);
	assert(src);
	
	real_dest = dest;
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;	++src;
	}
	*dest = '\0';
	return real_dest;
}


char* StrNCpy (char* dest, const char* src, size_t n)
{
	char* real_dest;
	size_t size = 0;
	
	assert(dest);
	assert(src);
	
	real_dest = dest;
	while ('\0' != *src && n > size)
	{	
		*dest = *src;
		++dest;	++src; ++size;
	}
	for (; size < n; size++)
	{
		*dest = '\0';
		++dest;
	}
	return real_dest;
}


int StrCmp(const char* str1, const char* str2)
{
	assert(str1);
	assert(str2);
	
	while ('\0' != *str1)
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		++str1; ++str2;
	}
	return (*str1 - *str2);
}


int StrNCmp(const char* str1, const char* str2, size_t n)
{
	size_t cnt = 1;
	
	assert(str1);
	assert(str2);
	
	if (NULL == str1 || NULL == str2)
	{
		return (*str1 - *str2);
	}
	while ('\0' != *str1 && cnt < n)
	{
		cnt++;
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		++str1; ++str2;	
	}
	return (*str1 - *str2);
}


int StrCaseCmp(const char* s1, const char* s2)
{ 
	assert(s1);
	assert(s2);
	
	while ('\0' != *s1)
	{	
		if (tolower(*s1) != tolower(*s2))
		{
			return (*s1 - *s2);
		}
		++s1; ++s2;
	}
	return(*s1 - *s2);
}


char* StrChr(const char* str, int ch)
{
	assert(str);
	
	while ('\0' != *str)
	{
		if (*str == (char)ch)
		{
			return (char*)str;
		}
		++str;
	}
	return '\0';
}


char* StrDup(const char *src)
{
	size_t size;
	char* dest;
	
	assert(src);
	
	size = StrLen(src);
	dest = (char*) malloc(sizeof(src) * size + 1);
	return StrCpy(dest, src);
}


char* StrCat(char* dest, const char* src)
{	
	char* real_dest;
	
	assert(dest);
	assert(src);
	
	real_dest = dest;
	while ('\0' != *dest)
	{
		++dest;
	}
	while ('\0' != *src)
	{
		*dest = *src; 
		++src; ++dest;
	}
	*dest = '\0';
	return real_dest;
}


char* StrNCat(char* dest, const char* src, size_t cnt)
{
	char* real_dest;
	size_t size = 0;
	
	assert(dest);
	assert(src);
	
	real_dest = dest;
	while ('\0' != *dest)
	{
		++dest;
	}
	while ('\0' != *src)
	{
		if (size >= cnt)
		{
			*dest = '\0';
			break;
		}
		*dest = *src; 
		++src; ++dest; ++size;
	}
	return real_dest;
}


char* StrStr(const char* str, const char* substr)
{
	int is_equal_str;
	size_t substr_len;
	char* search_for_char;
	
	assert(str);
	assert(substr);
	
	substr_len = StrLen(substr);
	search_for_char = (char*)str;
	while (NULL != search_for_char)
	{
		search_for_char = StrChr(search_for_char, (int)*substr);		
		if (NULL == search_for_char)
		{
			return '\0';
		}		
		is_equal_str = StrNCmp(search_for_char, substr, substr_len);
		if (0 == is_equal_str)
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
	char* char_in_search;
	
	assert(dest);
	assert(search);
	
	char_in_search = StrChr(search, *dest);
	while (NULL != char_in_search && '\0' != *dest)
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
	char* str_init_pnt;
	
	assert(delim);
	
	if (NULL == str)
	{
		str = str_ptr;
	}
	
	
	assert(str);
	
	str_init_pnt = str;
	while ('\0' != *str)
	{
		is_delim = StrSpn(str, delim);
		if (is_delim)
		{
			*str = '\0';
			++str;
			str_ptr = str;
			return str_init_pnt;
		}
		++str;
	}
	str_ptr = str;
	return str_init_pnt;
}


int IsPalindrome(const char* str)
{
	int i;
	int length = StrLen(str);
	char* end_ptr;
	
	assert(str);
	
	end_ptr = (char*)(str + length - 1);
	for (i = 0; i < (length / 2); ++i)
	{
		if (*(str + i) != *(end_ptr - i))
		{
			return 1;
		}	
	}
	return 0;
} 


void Print7Boom(int from, int to)
{
	int has_seven = 0;
	int i, j = from;
	for (i = from; i <= to; ++i)
	{
		if (i % 7 == 0)
		{
			printf("  *BOOM!*  ");
			j = i + 1; 
			continue;
		}
		if (0 > i)
		{
			j = -i;
		}
		while (0 < j)
		{
			if (j % 10 == 7)
			{
				has_seven = 1;
				printf("  *BOOM!*  ");
				break;
			}
			j = j / 10;
		}
		j = i + 1;
		if (1 == has_seven)
		{
			has_seven = 0;
			continue;
		}		
		printf(" %d ", i);
	}
}


void SpaceReview(char* dest, const char* src)
{	
	size_t prt_to_cpy;
	char* tmp_dest = (char*)src;
	
	assert(src);
	
	while (' ' == *tmp_dest && '\0' != *tmp_dest)
	{
		++tmp_dest; ++src;
	}
	while ('\0' != *tmp_dest)
	{
		tmp_dest = StrChr(tmp_dest, ' ');
		prt_to_cpy = (tmp_dest - src + 1);
		dest = StrNCat(dest, src, prt_to_cpy);
		while (' ' == *(tmp_dest + 1) && '\0' != *(tmp_dest + 1))
		{
			++tmp_dest;
		}
		++tmp_dest;
		src = tmp_dest;
	}
}


