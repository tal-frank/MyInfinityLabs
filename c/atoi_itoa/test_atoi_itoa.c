
#include <stdio.h>
#include <stdlib.h>

#include "atoi_itoa.h"


static void AtoiTest(char* str)
{
	if (atoi(str) == Atoi(str))
	{
		printf("expected %d\nactual %d\n", atoi(str), Atoi(str));
		printf("PASSED\n\n");
	}
	else
	{
		printf("expected %d\nactual %d\n", atoi(str), Atoi(str));
		printf("FAILED\n\n");
	}
}

int main()
{
	int check_func = 0;
	int check_macro = 1;
	int conv_num = 0;
	int value = -3930;
	char str[10] = "F";
	
	char str1[8] = {'R', 'f', '3', '%', 'e', 'S', 'e', '0'};
	char str2[6] = {'J', '?', 'e', '$', '0', 'R'};
	char str3[4] = {'f', 'J', 'd', 'S'};
	
	char str4[10] = "0";
	char str5[10] = "19";
	char str6[10] = " +159";
	char str7[10] = "-476";
	char str8[10] = "46G5";
	char str9[10] = "+45A";
	char str10[10] = "R56";
	char str11[10] = "-467A3";
	char str12[10] = "-45 4";
	char str13[10] = "890";
	char str14[10] = "";
	
	char* str15 = (char*)malloc(10);
	char* str16 = (char*)malloc(30);
	
	RepeatingChars(str1, 8, str2, 6, str3, 4);
	
	conv_num = AtoiBase(str, 16);
	
	Itoa(value, str15);
	ItoaBase(value, str16, 2);
	
	check_func = IsLittleEndian();
	check_macro = IS_LITTLE_ENDIAN(check_macro);
		
	printf("converted number from string equals %d\n", conv_num);

	printf("Itoa converted string from number equals %s\n", str15);
	printf("ItoaBase converted string from number equals %s\n", str16);
	
	free (str15);
	
	AtoiTest(str4);
	AtoiTest(str5);
	AtoiTest(str6);
	AtoiTest(str7);
	AtoiTest(str8);
	AtoiTest(str9);
	AtoiTest(str10);
	AtoiTest(str11);
	AtoiTest(str12);
	AtoiTest(str13);
	AtoiTest(str14);

	
	
	if (1 == check_func)
	{
		printf("function found little endian\n");
	}
	else
	{
		printf("function found big endian\n");
	}
	
	if (1 == check_macro)
	{
		printf("macro found little endian\n");
	}
	else
	{
		printf("macro found big endian\n");
	}
	return 0;
}
