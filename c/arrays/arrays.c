#include "arrays.h"
#include <stdio.h> /* printf */
#include <stdlib.h>
#include "../strings/string.c"


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
	int cnt = 0;
	char** env_arr;
	char envp_runner = envp;
	char** envp_init = (char**)envp;
	char** env_arr_init;
	char* item;
	
	while (NULL != *envp_runner)
	{
		++envp_runner; ++cnt;
	}
	
	env_arr = (char**)malloc(cnt * sizeof(char*) + 1);
	if (NULL == env_arr)
	{
		printf("error with buffer allocating\n");
	}
	envp_runner = envp;
	env_arr_init = env_arr;
/*	(char**)envp = envp_init;*/
	
	while (NULL != *envp_runner)
	{
		item = (char*)malloc((StrLen(*envp) + 1)* sizeof(char));
/*		*env_arr = (char*)malloc((StrLen(*envp) + 1)* sizeof(char));*/
		*env_arr = StrCpy(item, tolower(*envp_runner));
		++env_arr; ++envp_runner;
	}
	
	env_arr = env_arr_init;
	
	while (NULL != arr_env)
	{
		printf("%s\n", *env_arr);
		++env_arr;
	}
	
	free(env_arr);
}



















