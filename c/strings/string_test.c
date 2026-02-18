#include "string.h"


int main()
{
	char str[30] = "world hello";
	char* str2 = "hello world";
	char* str3 = "3674hello world";
	char* str4 = "123456789";
	char* str5 = "wkjckbw,wieudgkqwed qkedjboq.qkedjbkjf,kdcsvjhgl";
	char* str6 = ", .";
	char* substr = {"hlo"};
	char str_cpy[15];
	char* ch = StrChr(str2, (int)*str);
	int length = StrLen(str);
	int cmp = StrNCmp(str2, substr, 3);
	char* str_tok;
/*	size_t how_many_items = StrSpn(str3, str4); */
	char* concat; 
/*	concat = StrNCat(str, str2, 6);  */
	str_tok = StrTok(str5, str6);
/*	char* partof = StrStr(str2, substr);  */
/*	StrNCpy(str_cpy, str2, 5);  */
	
	
	printf("strtok returns : %s", str_tok);
/*	printf("this is the char to start from: %c\n" , ch);  */
/*	printf("this is the sub str : %s\n" , partof);  */
/*	printf("this is the concat string: %s\n" , concat);   */
/*	printf("str length is %d\n" , length);  */
/*	printf("there are %zu numbers in the srting\n" , how_many_items); */
	printf("copied string is: %s\n" , str_cpy);
	if (cmp == 0)
	{
		printf("strings are equal\n");
	}
	else
	{
		printf("strings are different\n");	
	}

}
