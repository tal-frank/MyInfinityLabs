#include <stdio.h>


int CheckSign(char** str)
{
	if ('-' == **str)
	{
		++*str;
		return -1;
	}
	else if ('+' == **str)
	{
		++*str;
		return 1;
	}
	return 1;
}


int CheckIfNum(char*str)
{
	if (48 <= *str && 58 > *str)
	{
		return 1;
	}
	return 0;
}


int ConvertToInt(char* str)
{
	int num = (int)(*str - 48);
	return num;
}

int Atoi(char* str)
{
	int num = 0;
	int neg_flag = CheckSign(&str);
	while(CheckIfNum(str))
	{
		num = num * 10 + ConvertToInt(str++);
	}
	return neg_flag * num;
}


int main()
{
	int num = 0;
	
	char str1[10] = "123";
	char str2[10] = "-123";
	char str3[10] = "0";
	char str4[10] = "+156A3";
	
	num = Atoi(str1);
	printf("num is : %d\n", num);
	
	num = Atoi(str2);
	printf("num is : %d\n", num);
	
	num = Atoi(str3);
	printf("num is : %d\n", num);
	
	num = Atoi(str4);
	printf("num is : %d\n", num);

	return 0;
}










