#include "strings.h"
#include "strings.c"
#include <string.h>
#include <assert.h>


/*
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
	size_t how_many_items = StrSpn(str3, str4); 
	char* concat; 
	concat = StrNCat(str, str2, 6);  
	str_tok = StrTok(str5, str6);
	char* partof = StrStr(str2, substr);  
	StrNCpy(str_cpy, str2, 5);  
	
	
	printf("strtok returns : %s", str_tok);
	printf("this is the char to start from: %c\n" , ch);  	
	printf("this is the sub str : %s\n" , partof);  
	printf("this is the concat string: %s\n" , concat);   
	printf("str length is %d\n" , length);  
	printf("there are %zu numbers in the srting\n" , how_many_items); 
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
*/





int main()
{
	int pass_fail = 0;
	char str1[6] = "short";
	char str2[100] = "the long string";
	char str3[100] = "t1e lo2g str3ng";
	char str4[50] = "";
	char str5[50] = "";
	char str6[100] = "the long string";
	char str7[100] = "the long string that start the same as string";
	char str8[100] = " ";
	char str9[100] = "@";
	char str10[100] = "";
	char str11[100] = "string";
	char* str12 = "detartrated";
	char* str13 = "redder";
	char* str14 = "runner";
	char* str15 = "       a sentence    with  a   lot of          spaces       ";
	char str16[100] = "";
	char phrase_to_delimit[100] = "hey,,this,is8sparta!";
	char phrase_to_delimit2[100] = "hey,,this,is8sparta!";
	char* pointer_to_free = NULL;
	int palindrom_check;
	
	
	printf("SpacesReview test:\n\n");
	printf("before: %s\n", str15);
	SpaceReview(str16, str15);
	printf("after: %s\n", str16);
	printf("\n");
	
	
	printf("Print7BOOM test:\n\n");
	Print7Boom(990, 1027);
	printf("\n\n");
	
	
	printf ("IsPalindrome test:\n\n");
	printf("first test :\nexpected: is palindrom\n");
	palindrom_check = IsPalindrome(str12);
	if (palindrom_check == 0)
	{
		
		printf("result: is palindrom\nPASSED\n");
	}
	else
	{
		printf("result: is not palindrom\nFAILED\n");
	}
	printf("second test :\nexpected: is palindrom\n");
	palindrom_check = IsPalindrome(str13);
	if (palindrom_check == 0)
	{
		
		printf("result: is palindrom\nPASSED\n");
	}
	else
	{
		
		printf("result: is not palindrom\nFAILED\n");
	}
	printf("third test :\nexpected: is not palindrom\n");
	palindrom_check = IsPalindrome(str14);
	if (palindrom_check == 0)
	{
		
		printf("result: is palindrom\nFAILED\n");
	}
	else
	{
		
		printf("result: is not palindrom\nPASSED\n\n");
	}
	
	
	/*------------------------------------------------------------*/
	printf ("StrLen Tests:\n\n");
	
	
	printf ("T1:\nexpected: %ld\nactual: %ld\n" , strlen (""), StrLen (""));
	pass_fail = (strlen ("") == StrLen (""));
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!");
	
	
	printf ("T2:\nexpected: %ld\nactual: %ld\n" , strlen ("hello strlen"), StrLen ("hello strlen"));
	pass_fail = (strlen ("hello strlen") == StrLen ("hello strlen"));
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	/*------------------------------------------------------------*/
	printf ("\nStrCpy Tests:\n\n");
	
	
	printf ("T1:\nexpected: %s\nactual: %s\n", strcpy (str4, str5), StrCpy (str4, str5));
	
	pass_fail = strcmp (strcpy (str4, str5), StrCpy (str4, str5) );
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T2:\ninitial: %s\n", str2);
	printf ("expected: %s\n", strcpy (str2, str1));
	strcpy (str2, str6);
	printf("actual: %s\n", StrCpy (str2, str1));
	strcpy (str2, str6);
	
	pass_fail = strcmp(strcpy (str2, str1), (strcpy (str2, str6), StrCpy (str2, str1)));
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2, str6);
	
	
	printf ("T3:\ninitial: %s\n", str2);
	printf ("expected: %s\n",strcpy(str2, str3));
	strcpy (str2, str6);
	printf("actual: %s\n", StrCpy(str2, str3));
	strcpy (str2, str6);
	
	pass_fail = strcmp(strcpy (str2, str3), (strcpy (str2, str6), StrCpy (str2, str3)));
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2, str6);
	
	
	
	printf ("\nStrNCpy Tests:\n\n");
	
	strcpy (str2, str6);
	printf ("T1:\nexpected: %s\n", strncpy (str2, str1 , 4));
	strcpy (str2, str6);
	printf("actual: %s\n", StrNCpy (str2, str1, 4));
	
	pass_fail = strcmp(strncpy (str2, str1 , 4), (strcpy (str2, str6), StrNCpy (str2, str1, 4)));
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2, str6);
	
	
	strcpy (str2, str6);
	printf ("T2:\nexpected: %s\n", strncpy (str2, str1 , 8));
	strcpy (str2, str6);
	printf("actual: %s\n", StrNCpy (str2, str1, 8));
	
	pass_fail = strcmp(strncpy (str2, str1 , 8), (strcpy (str2, str6), StrNCpy (str2, str1, 8)));
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2, str6);
	
	
	printf ("T3:\nexpected: %s\n", strncpy (str2, str4 , 8));
	strcpy (str2, str6);
	printf("actual: %s\n", StrNCpy (str2, str4, 8));
	
	pass_fail = strcmp(strncpy (str2, str4 , 8), (strcpy (str2, str6), StrNCpy (str2, str4, 8) ) );
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2, str6);
	
	
	printf ("T4:\nexpected: %s\n", strncpy (str2, str1 , 0));
	strcpy (str2, str6);
	printf("actual: %s\n", StrNCpy (str2, str1, 0));
	strcpy (str2, str6);
	
	pass_fail = strcmp(strncpy (str2, str1 , 0), ( strcpy (str2, str6), StrNCpy (str2, str1, 0) ) );
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );;
	strcpy (str2, str6);
	
	/*------------------------------------------------------------*/
	printf("\nStrCmp Tests:\n\n");
	
	printf ("T1:\nexpected: %d\n", strcmp (str2, str6) );
	printf("actual: %d\n", StrCmp (str2, str6));
	
	pass_fail = ( strcmp (str2, str6) == StrCmp (str2, str6) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T2:\nexpected: %d\n", strcmp (str2, str7));
	printf("actual: %d\n", StrCmp (str2, str7));
	
	pass_fail = ( strcmp (str2, str7) == StrCmp (str2, str7) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T3:\nexpected: %d\n", strcmp (str7, str2));
	printf("actual: %d\n", StrCmp (str7, str2));
	
	pass_fail = ( strcmp (str7, str2) == StrCmp (str7, str2) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T4:\nexpected: %d\n", strcmp (str2, str3));
	printf("actual: %d\n", StrCmp (str2, str3));
	
	pass_fail = ( strcmp (str2, str3) == StrCmp (str2, str3) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T5:\nexpected: %d\n", strcmp (str3, str2));
	printf("actual: %d\n", StrCmp (str3, str2));
	
	pass_fail = ( strcmp (str3, str2) == StrCmp (str3, str2) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	/*----------------------------------------------------------------------*/
	printf("\nStrNCmp Tests:\n\n");
	
	printf ("T1:\nexpected: %d\n", strncmp (str2, str6, 12) );
	printf("actual: %d\n", StrNCmp (str2, str6, 12) );
	
	pass_fail = ( strncmp (str2, str6, 12) == StrNCmp (str2, str6, 12) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T2:\nexpected: %d\n", strncmp (str2, str3, 4));
	printf("actual: %d\n", StrNCmp (str2, str3, 4));
	
	pass_fail = ( strncmp (str2, str3, 4) == StrNCmp (str2, str3, 4) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T3:\nexpected: %d\n", strncmp (str3, str2, 4));
	printf("actual: %d\n", StrNCmp (str3, str2, 4));
	
	pass_fail = ( strncmp (str3, str2, 4) == StrNCmp (str3, str2, 4) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T4:\nexpected: %d\n", strncmp (str2, str7, 14));
	printf("actual: %d\n", StrNCmp (str2, str7, 14));
	
	pass_fail = ( strncmp (str2, str7, 14) == StrNCmp (str2, str7, 14) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T5:\nexpected: %d\n", strncmp (str2, str7, 0));
	printf("actual: %d\n", StrNCmp (str2, str7, 0));
	
	pass_fail = ( strncmp (str2, str7, 0) == StrNCmp (str2, str7, 0) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	
	/*----------------------------------------------------------------------*/
	printf("\nStrCaseCmp Tests:\n\n");
	
	
	printf ("T1:\nexpected: %d\n", strcasecmp (str2, str6) );
	printf("actual: %d\n", StrCaseCmp (str2, str6) );
	
	pass_fail = ( strcasecmp (str2, str6) == StrCaseCmp (str2, str6) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T2:\nexpected: %d\n", strcasecmp (str2, str3) );
	printf("actual: %d\n", StrCaseCmp (str2, str3) );
	
	pass_fail = ( strcasecmp (str2, str3) == StrCaseCmp (str2, str3) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T3:\nexpected: %d\n", strcasecmp (str8, str9) );
	printf("actual: %d\n", StrCaseCmp (str8, str9) );
	
	pass_fail = ( strcasecmp (str8, str9) == StrCaseCmp (str8, str9) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T4:\nexpected: %d\n", strcasecmp (str1, str2) );
	printf("actual: %d\n", StrCaseCmp (str1, str2) );
	
	pass_fail = ( strcasecmp (str1, str2) == StrCaseCmp (str1, str2) ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	/*----------------------------------------------------------------*/
	
	printf("\nStrChr Tests:\n\n");
	
	printf ("T1:\nexpected: %s\n", strchr (str1, 's') );
	printf("actual: %s\n", StrChr (str1, 's') );
	
	pass_fail = ( strchr (str1, 's') == StrChr (str1, 's') ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T2:\nexpected: %s\n", strchr (str1, 'o') );
	printf("actual: %s \n", StrChr (str1, 'o') );
	
	pass_fail = ( strchr (str1, 'o') == StrChr (str1, 'o') ) ? 1 : 0;
	printf("%s \n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T3:\nexpected: %s\n", strchr (str1, 't') );
	printf("actual: %s\n", StrChr (str1, 't') );
	
	pass_fail = ( strchr (str1, 't') == StrChr (str1, 't') ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T4:\nexpected: %s\n", strchr (str2, 'n') );
	printf("actual: %s\n", StrChr (str2, 'n') );
	
	pass_fail = ( strchr (str2, 'n') == StrChr (str2, 'n') ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T5:\nexpected: %s\n", strchr (str2, '!') );
	printf("actual: %s\n", StrChr (str2, '!') );
	
	pass_fail = ( strchr (str2, '!') == StrChr (str2, '!') ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	printf ("T6:\nexpected: %s\n", strchr (str2, '\0') );
	printf("actual: %s\n", StrChr (str2, '\0') );
	
	pass_fail = ( strchr (str2, '!') == StrChr (str2, '!') ) ? 1 : 0;
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!" );
	
	
	/*----------------------------------------------------------------*/
	printf("\nStrDup Tests:\n\n");
	
	
	printf ("T1:\nexpected: %s\n", str1 );
	
	pointer_to_free = StrDup (str1);
	strcpy ( str11, pointer_to_free);
	printf("actual: %s\n", str11 );
	
	pass_fail = strcmp ( str1, str11 );
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	
	pass_fail = pointer_to_free != (char*)&str1 ? 1 : 0;
	printf ("T2:\naddress is diffrent?\n%s\n", (pass_fail ? "PASSED!" : "FAILED!" ) );
	
	free(pointer_to_free);
	pointer_to_free = NULL;
	
	
	/*----------------------------------------------------------------*/
	printf("\nStrCat Tests:\n\n");
	
	
	printf ("T1:\nexpected: %s\n", strcat (str2, str1) );
	strcpy (str2,str6);
	printf("actual: %s\n", StrCat (str2, str1) );
	
	pass_fail = strcmp ( strcat (str2, str1), (strcpy (str2,str6), StrCat (str2, str1)) );
	printf("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2,str6);
	
	/*----------------------------------------------------------------*/
	printf("\nStrNCat Tests:\n\n");
	
	
	printf ("T1:\nexpected: %s\n", strncat (str2, str1, 2) );
	strcpy (str2,str6);
	printf ("actual: %s\n", StrNCat (str2, str1, 2) );
	
	pass_fail = strcmp ( strncat (str2, str1 ,2), (strcpy (str2,str6), StrNCat (str2, str1, 2)) );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2,str6);
	
	printf ("T2:\nexpected: %s\n", strncat (str2, str1, 8) );
	strcpy (str2,str6);
	printf ("actual: %s\n", StrNCat (str2, str1, 8) );
	
	pass_fail = strcmp ( strncat (str2, str1 ,8), (strcpy (str2,str6), StrNCat (str2, str1, 8)) );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2,str6);
	
	printf ("T3:\nexpected: %s\n", strncat (str2, str1, 0) );
	strcpy (str2,str6);
	printf ("actual: %s\n", StrNCat (str2, str1, 0) );
	
	pass_fail = strcmp ( strncat (str2, str1 ,0), (strcpy (str2,str6), StrNCat (str2, str1, 0)) );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	strcpy (str2,str6);
	
	
	/*----------------------------------------------------------------*/
	printf("\nStrStr Tests:\n\n");
	
	
	strcpy(str10, "");
	pointer_to_free = strstr (str7, "string");
	strcpy(str10, pointer_to_free);
	printf ("T1:\nexpected: %s\n", str10 );
	strcpy(str10, "");
	
	strcpy(str10, "");
	pointer_to_free = StrStr (str7, "string");
	strcpy(str10, pointer_to_free);
	printf ("actual: %s\n", str10 );
	strcpy(str10, "");
	
	pass_fail = strcmp ( strstr (str7, "string"), StrStr (str7, "string") );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	
	
	strcpy(str10, "");
	pointer_to_free = strstr (str2, "the");
	strcpy(str10, pointer_to_free);
	printf ("T2:\nexpected: %s\n", str10 );
	strcpy(str10, "");
	
	strcpy(str10, "");
	pointer_to_free = StrStr (str2, "the");
	strcpy(str10, pointer_to_free);
	printf ("actual: %s\n", str10 );
	strcpy(str10, "");
	
	pass_fail = strcmp ( strstr (str2, "the"), StrStr (str2, "the") );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	
	
	strcpy(str10, "");
	pointer_to_free = strstr (str7, "that");
	strcpy(str10, pointer_to_free);
	printf ("T3:\nexpected: %s\n", str10 );
	strcpy(str10, "");
	
	strcpy(str10, "");
	pointer_to_free = StrStr (str7, "that");
	strcpy(str10, pointer_to_free);
	printf ("actual: %s\n", str10 );
	strcpy(str10, "");
	
	pass_fail = strcmp ( strstr (str7, "that"), StrStr (str7, "that") );
	printf ("%s\n", !pass_fail ? "PASSED!" : "FAILED!" );
	
	
	/*----------------------------------------------------------------*/
	printf("\nStrSpn Tests:\n\n");
	
	
	printf ("T1:\nexpected: %ld\nactual: %ld\n" , strspn (str1, "so"), StrSpn (str1, "so"));
	pass_fail = (strspn (str1, "so") == StrSpn (str1, "so"));
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!");
	
	printf ("T2:\nexpected: %ld\nactual: %ld\n" , strspn (str1, "ldu"), StrSpn (str1, "ldu"));
	pass_fail = (strspn (str1, "ldu") == StrSpn (str1, "ldu"));
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!");
	
	printf ("T3:\nexpected: %ld\nactual: %ld\n" , strspn (str1, "tso"), StrSpn (str1, "tso"));
	pass_fail = (strspn (str1, "tso") == StrSpn (str1, "tso"));
	printf("%s\n", pass_fail ? "PASSED!" : "FAILED!");
	
	
	/*----------------------------------------------------------------*/
	/*phrase_to_delimit = "hey,,this,is8sparta!"*/
	
	printf("\nStrTok Tests:\n\n");
	
	printf("strtok() result: ");
	strcpy(str10, strtok ( phrase_to_delimit, "," ) );
	printf("%s ", str10);
	strcpy(str10, strtok ( NULL, "8" ) );
	printf("%s ", str10);
	strcpy(str10, strtok ( NULL, ",8" ) );
	printf("%s\n", str10);
	
	printf("StrTok() result: ");
	
	
	strcpy(str10, StrTok ( phrase_to_delimit2, "," ) );
	printf("%s ", str10);
	strcpy(str10, StrTok ( NULL, "8" ) );
	printf("%s ", str10);
	strcpy(str10, StrTok ( NULL, ",8" ) );
	printf("%s\n", str10);
	

	return 0;
}



