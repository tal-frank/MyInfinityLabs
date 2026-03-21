
#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "atoi_itoa.h"


/*********************************** MACROS ***********************************/

#define ASCII_TABLE_SIZE (377)
#define TEST_VAL (1)
#define NEG (-1)
#define POS (1)

#define DECIMAL (10)
#define MIN_BASE (2)
#define MAX_BASE (36)

#define CHAR_0_ALIGN (48)
#define CHAR_9_ALIGN (58)
#define CHAR_A_ALIGN (65)
#define APEARS_IN_ARR (1)


/*********************************** FUNCTION DECLARATIONS ***********************************/

static void MakeConvertList(int arr[], size_t size, size_t base);
static void MakeConvertListTo36(int arr[], size_t base);
static void CheckApearanceInArr(int arr_dest[], const char arr_src[], size_t size_src);
static void PrintCommonChars(int arr[3][ASCII_TABLE_SIZE], size_t size);
static char FindValChar(int* val, int base);
static char* ReverseString (char* str);
static void EraseSpaces(const char** str);
static int DecideSign(const char** str);
static void AddSign(char** str, int sign);


/*********************************** STATIC FUNCTIONS ***********************************/

static void AddSign(char** str, int sign)
{
	if (sign)
	{
		**str = '-';
		++*str;
	}
}


static int DecideSign(const char** str)
{
	int neg_flag = POS;
	
	if ('-' == **str || '+' == **str)
	{
		neg_flag = '-' == **str ? NEG : POS;
		++*str;
	}
	
	return neg_flag;
}


static void EraseSpaces(const char** str)
{
	while (' ' == **str)
	{
		++*str;
	}
}


static char* ReverseString (char* str)
{
	int i = 0;
	int len = 0;
	char* rev_str = NULL;
	
	len = strlen(str);
	rev_str = (str + len - 1);
	
	for (i = 0; i < len / 2; ++i)
	{
		char temp = *rev_str;
		*rev_str = *str;
		*str = temp;
		++str; --rev_str;
	}
	
	return rev_str;
}


static char FindValChar(int* val, int base)
{
	int val_char = *val % base;
		
	*val /= base;
	
	if (val_char < 10)
	{
		val_char += CHAR_0_ALIGN;
	}
	else
	{
		val_char += CHAR_A_ALIGN - DECIMAL;
	}
	
	return (char)val_char;
}


static void CheckApearanceInArr(int arr_dest[], const char arr_src[], size_t size_src)
{
	size_t i = 0;
	for (i = 0; i < size_src; ++i)
	{
		arr_dest[(int)arr_src[i]] = APEARS_IN_ARR;
	}
}


static void PrintCommonChars(int arr[3][ASCII_TABLE_SIZE], size_t size)
{
	size_t i = 0;
	for (i = 0; i < size; ++i)
	{
		if (APEARS_IN_ARR == arr[0][i] && 
		    APEARS_IN_ARR == arr[1][i] && 
		    APEARS_IN_ARR != arr[2][i])
		{
			printf("%c ", (char)i);
		}
	}
	printf("\n");
}


static void MakeConvertList(int arr[], size_t size, size_t base)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (i >= CHAR_0_ALIGN && i < base + CHAR_0_ALIGN)
		{
			arr[i] = i - CHAR_0_ALIGN;
		}
		else
		{
			arr[i] = NEG;
		}
	}
	
	if (base > 10)
	{
		MakeConvertListTo36(arr, base);
	}
}

static void MakeConvertListTo36(int arr[], size_t base)
{
	size_t i = 0;
	
	for (i = CHAR_A_ALIGN ; i < base + CHAR_A_ALIGN - DECIMAL; ++i)
	{
		arr[i] = i - CHAR_A_ALIGN + DECIMAL;
	}
}


/*********************************** FIND ENDIAN FUNCTION ***********************************/

int IsLittleEndian(void)
{
	int i = TEST_VAL;
	char* endian_check = NULL;
	
	endian_check = (char*)&i;
	return (TEST_VAL == *endian_check) ? 1 : 0;
}

/*********************************** ATOI FUNCTIONS ***********************************/


int Atoi(const char *str)
{
	int conv_num = 0;
	int neg_flag = POS;
	static int convert_list[ASCII_TABLE_SIZE] = {0};

	assert(str);
	
	MakeConvertList(convert_list, ASCII_TABLE_SIZE, DECIMAL);
	
	EraseSpaces(&str);	
	neg_flag = DecideSign(&str);
	
	while ('\0' != *str)
	{
		if (NEG == convert_list[(int)*str])
		{
			return neg_flag * conv_num;
		}
		conv_num = conv_num * DECIMAL + convert_list[(int)*str];
		++str;
	}
	return neg_flag * conv_num;
}


int AtoiBase(const char* str, size_t base)
{
	int conv_num = 0;
	int neg_flag = POS;
	static int convert_list[ASCII_TABLE_SIZE] = {0};
	
	assert(str);
	
	if (base > MAX_BASE || base < MIN_BASE)
	{
		printf("unsupported base\n");
		return 0;
	}
	
	MakeConvertList(convert_list, ASCII_TABLE_SIZE, base);
	
	EraseSpaces(&str);
	neg_flag = DecideSign(&str);
	
	while ('\0' != *str)
	{
		if (NEG == convert_list[(int)*str])
		{
			return neg_flag * conv_num;
		}
		conv_num = conv_num * base + convert_list[(int)*str];
		++str;
	}
	return neg_flag * conv_num;
}


/*********************************** ITOA FUNCTIONS ***********************************/


char* Itoa(int value, char* str)
{
	int neg_flag = 0;
	char* real_str = str;
	
	assert(str);
	
	neg_flag = value < 0 ? 1 : 0;	
	value = value < 0 ? -value : value;
	
	while (value > 0)
	{
		*str = FindValChar(&value, DECIMAL);
		++str;
	}
	
	AddSign((char**)&str, neg_flag);
	*str = '\0';
	ReverseString(real_str);
	
	return real_str;
}

char* ItoaBase(int value, char* str,  size_t base)
{
	int neg_flag = 0;
	char* real_str = str;
	
	assert(str);
	
	if (base > MAX_BASE || base < MIN_BASE)
	{
		printf("unsupported base\n");
		return 0;
	}
	
	neg_flag = value < 0 ? 1 : 0;	
	value = value < 0 ? -value : value;
	
	while (value > 0)
	{
		*str = FindValChar(&value, base);
		++str;
	}

	AddSign((char**)&str, neg_flag);
	*str = '\0';
	ReverseString(real_str);
	
	return real_str;
}


/*********************************** ARRAT REPEAT APEARANCE ***********************************/

void RepeatingChars(const char* array_1, size_t array_1_length, 
                     const char* array_2, size_t array_2_length, 
                     const char* array_3, size_t array_3_length)
{
	static int arr[3][ASCII_TABLE_SIZE] = {0};
	
	CheckApearanceInArr(arr[0], array_1, array_1_length);
	CheckApearanceInArr(arr[1], array_2, array_2_length);
	CheckApearanceInArr(arr[2], array_3, array_3_length);
	
	PrintCommonChars(arr, ASCII_TABLE_SIZE);
}

