#include "arrays.h"
#include <stdio.h> /* printf */
#include <stdlib.h>
#include "../strings/string.c"
#include <ctype.h>

size_t Jusephus(size_t start_index, size_t soldier_num)
{
	size_t i = 2;
	
	while (i <= soldier_num)
	{
		i *= 2;
	}
	i /= 2;
	
	return (soldier_num - i) * 2 + start_index;
}


void TwoD( const int* mat, int* dest ,int rows, int cols)
{
	int c; int r;
	
	for (r = 0; r < rows; ++r)
	{
		*(dest + r) = 0;
		
		for (c = 0; c < cols; ++c)
		{
			*(dest + r) += *(mat + c + cols * r);
		}
	}
}


size_t instantJuseph(size_t n)
{
	int high_bit = 1 << (31 - __builtin_clz(n));
	int reminder = n ^ high_bit;
	return (reminder << 1);
}




void PrintEnv(const char* envp[])
{
	int i;
	int j;
	int cnt = 0;
	char* item;
	char** env_arr;
	int item_len;
	while (NULL != envp[cnt])
	{	
		++cnt;
	}
	
	env_arr = (char**)malloc(cnt * (sizeof(char*) + 1));
	if (NULL == env_arr)
	{
		printf("error with buffer allocating\n");
		return;
	}

	for (i = 0; NULL != envp[i]; ++i)
	{
		item_len = StrLen(envp[i]);
		item = (char*)malloc(item_len * (sizeof(char) + 1));
		if (NULL == item)
		{
			printf("error with buffer allocating\n");
			return;
		}
		StrCpy(item, envp[i]);
		for (j = 0; j < item_len; ++j)
		{
			item[j] = (char)(tolower(item[j]));
		}
		item[j] = '\0';
		env_arr[i] = item;
	}
	for (i = 0; NULL != env_arr[i]; ++i)
	{
		printf("%s\n", env_arr[i]);
	}

}














