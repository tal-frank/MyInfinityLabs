#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

void SwapLetters(char* str, size_t first_index, size_t second_index)
{
	char temp = str[first_index];
	str[first_index] = str[second_index];
	str[second_index] = temp;
}

void FindPermutations(size_t index, char* str)
{
	size_t i = 0;
	size_t len = strlen(str);
	if (index == len)
	{
		printf(" { %s } ", str);
	}
	for (i = index; i < len; ++i)
	{
		SwapLetters(str, index, i);
		FindPermutations(index + 1, str);
		SwapLetters(str, index, i);
	}
}


void PrintPermutations(char* str)
{
	FindPermutations(0, str);
}



int main()
{
	char* str = (char*)malloc(15);
	strcpy(str, "ABC");
	
	PrintPermutations(str);
	printf("\n");
	return 0;
}
