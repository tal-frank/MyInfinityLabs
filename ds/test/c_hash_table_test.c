#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_hash_table.h"

#define UNUSED(x) (void)x

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

int act_func(void* data, void* param)
{
	char* str = (char*)data;
	UNUSED(param);
	printf("%s\n", str);
	return 0;
}

size_t hash_func (const void* key)
{
	char* str = (char*)key;
	size_t ch = (size_t)*str;
	size_t converted_key = ch - 97;
	return converted_key; 
}

int cmp_func (const void* key1, const void* key2)
{
	char* str1 = (char*)key1;
	char* str2 = (char*)key2;
	return strcmp(str1, str2);
}

void InsertTest(void)
{
	hash_t* hash = HashCreate(26, hash_func, cmp_func);
	
	char* str1 = (char*)malloc(10);
	char* str2 = (char*)malloc(10);
	char* str3 = (char*)malloc(10);
	char* str4 = (char*)malloc(10);
	char* str5 = (char*)malloc(10);
	char* str6 = (char*)malloc(10);
	char* str7 = (char*)malloc(10);
	char* str8 = (char*)malloc(10);
	char* str9 = (char*)malloc(10);
	char* str10 = (char*)malloc(10);
	char* str11 = (char*)malloc(10);
	
	printf(CYAN "IS EMPTY TEST\n" RESET_COLOR);
	
	strcpy(str1, "and");
	strcpy(str2, "end");
	strcpy(str3, "system");
	strcpy(str4, "if");
	strcpy(str5, "string");
	strcpy(str6, "long");
	strcpy(str7, "large");
	strcpy(str8, "main");
	strcpy(str9, "good");
	strcpy(str10, "bad");
	strcpy(str11, "start");

	if (!HashIsEmpty(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("get not empty although is empty\n\n");
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty is working\n\n");

	printf(CYAN "COUNT TEST\n" RESET_COLOR);
	if (0 != HashCount(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("count finds elements in empty hash\n");
		printf("expected : 0\nactual : %ld\n\n", HashCount(hash));
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count is working\n\n");

	HashInsert(hash, (void*)str1, (void*)str1);

	printf(CYAN "IS EMPTY TEST\n" RESET_COLOR);
	if (HashIsEmpty(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("get not empty although is empty\n\n");
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty is working\n\n");

	printf(CYAN "COUNT TEST\n" RESET_COLOR);
	if (1 != HashCount(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("count is not working\n");
		printf("expected : 1\nactual : %ld\n\n", HashCount(hash));
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count is working\n\n");

	HashInsert(hash, (void*)str2, (void*)str2);
	HashInsert(hash, (void*)str3, (void*)str3);
	HashInsert(hash, (void*)str4, (void*)str4);
	HashInsert(hash, (void*)str5, (void*)str5);
	HashInsert(hash, (void*)str6, (void*)str6);
	HashInsert(hash, (void*)str7, (void*)str7);
	HashInsert(hash, (void*)str8, (void*)str8);
	HashInsert(hash, (void*)str9, (void*)str9);
	HashInsert(hash, (void*)str10, (void*)str10);
	HashInsert(hash, (void*)str11, (void*)str11);

	if (11 != HashCount(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("count is not working\n");
		printf("expected : 11\nactual : %ld\n\n", HashCount(hash));
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count is working\n\n");

	free(str1);
	free(str2);
	free(str3);
	free(str4);
	free(str5);
	free(str6);
	free(str7);
	free(str8);
	free(str9);
	free(str10);
	free(str11);

	HashDestroy(hash);

}

void RemoveTest(void)
{
	hash_t* hash = HashCreate(26, hash_func, cmp_func);
	
	char* str1 = (char*)malloc(10);
	char* str2 = (char*)malloc(10);
	char* str3 = (char*)malloc(10);
	char* str4 = (char*)malloc(10);
	char* str5 = (char*)malloc(10);
	char* str6 = (char*)malloc(10);
	char* str7 = (char*)malloc(10);
	char* str8 = (char*)malloc(10);
	char* str9 = (char*)malloc(10);
	char* str10 = (char*)malloc(10);
	char* str11 = (char*)malloc(10);
	
	
	strcpy(str1, "and");
	strcpy(str2, "end");
	strcpy(str3, "system");
	strcpy(str4, "if");
	strcpy(str5, "string");
	strcpy(str6, "long");
	strcpy(str7, "large");
	strcpy(str8, "main");
	strcpy(str9, "good");
	strcpy(str10, "bad");
	strcpy(str11, "start");
	
	HashInsert(hash, (void*)str1, (void*)str1);
	HashInsert(hash, (void*)str2, (void*)str2);
	HashInsert(hash, (void*)str3, (void*)str3);
	HashInsert(hash, (void*)str4, (void*)str4);
	HashInsert(hash, (void*)str5, (void*)str5);
	HashInsert(hash, (void*)str6, (void*)str6);
	HashInsert(hash, (void*)str7, (void*)str7);
	HashInsert(hash, (void*)str8, (void*)str8);
	HashInsert(hash, (void*)str9, (void*)str9);
	HashInsert(hash, (void*)str10, (void*)str10);
	HashInsert(hash, (void*)str11, (void*)str11);

	printf(CYAN "REMOVE TEST\n" RESET_COLOR);
	
	HashRemove(hash, (void*)str4);
	if (10 != HashCount(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("remove is not working\n");
		printf("expected : 10\nactual : %ld\n\n", HashCount(hash));
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("remove is working\n\n");

	HashRemove(hash, (void*)str6);
	if (9 != HashCount(hash))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("remove is not working\n");
		printf("expected : 9\nactual : %ld\n\n", HashCount(hash));
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("remove is working\n\n");
	
}

void FindTest(void)
{
	hash_t* hash = HashCreate(26, hash_func, cmp_func);
	
	char* str1 = (char*)malloc(10);
	char* str2 = (char*)malloc(10);
	char* str3 = (char*)malloc(10);
	char* str4 = (char*)malloc(10);
	char* str5 = (char*)malloc(10);
	char* str6 = (char*)malloc(10);
	char* str7 = (char*)malloc(10);
	char* str8 = (char*)malloc(10);
	char* str9 = (char*)malloc(10);
	char* str10 = (char*)malloc(10);
	char* str11 = (char*)malloc(10);
	char* str12 = (char*)malloc(10);
	
	
	strcpy(str1, "and");
	strcpy(str2, "end");
	strcpy(str3, "system");
	strcpy(str4, "if");
	strcpy(str5, "string");
	strcpy(str6, "long");
	strcpy(str7, "large");
	strcpy(str8, "main");
	strcpy(str9, "good");
	strcpy(str10, "bad");
	strcpy(str11, "start");
	
	HashInsert(hash, (void*)str1, (void*)str1);
	HashInsert(hash, (void*)str2, (void*)str2);
	HashInsert(hash, (void*)str3, (void*)str3);
	HashInsert(hash, (void*)str4, (void*)str4);
	HashInsert(hash, (void*)str5, (void*)str5);
	HashInsert(hash, (void*)str6, (void*)str6);
	HashInsert(hash, (void*)str7, (void*)str7);
	HashInsert(hash, (void*)str8, (void*)str8);
	HashInsert(hash, (void*)str9, (void*)str9);
	HashInsert(hash, (void*)str10, (void*)str10);
	HashInsert(hash, (void*)str11, (void*)str11);

	printf(CYAN "FIND TEST\n" RESET_COLOR);

	strcpy(str12, (char*)HashFind(hash, str5));
	if(strcmp(str12, str5))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("remove is not working\n");
		printf("expected : '%s'\nactual : '%s'\n\n",str5, str12);
		HashDestroy(hash);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("remove is working\n\n");

}

void ForEachTest(void)
{
	hash_t* hash = HashCreate(26, hash_func, cmp_func);
	
	char* str1 = (char*)malloc(10);
	char* str2 = (char*)malloc(10);
	char* str3 = (char*)malloc(10);
	char* str4 = (char*)malloc(10);
	char* str5 = (char*)malloc(10);
	char* str6 = (char*)malloc(10);
	char* str7 = (char*)malloc(10);
	char* str8 = (char*)malloc(10);
	char* str9 = (char*)malloc(10);
	char* str10 = (char*)malloc(10);
	char* str11 = (char*)malloc(10);
	
	
	strcpy(str1, "and");
	strcpy(str2, "end");
	strcpy(str3, "system");
	strcpy(str4, "if");
	strcpy(str5, "string");
	strcpy(str6, "long");
	strcpy(str7, "large");
	strcpy(str8, "main");
	strcpy(str9, "good");
	strcpy(str10, "bad");
	strcpy(str11, "start");
	
	HashInsert(hash, (void*)str1, (void*)str1);
	HashInsert(hash, (void*)str2, (void*)str2);
	HashInsert(hash, (void*)str3, (void*)str3);
	HashInsert(hash, (void*)str4, (void*)str4);
	HashInsert(hash, (void*)str5, (void*)str5);
	HashInsert(hash, (void*)str6, (void*)str6);
	HashInsert(hash, (void*)str7, (void*)str7);
	HashInsert(hash, (void*)str8, (void*)str8);
	HashInsert(hash, (void*)str9, (void*)str9);
	HashInsert(hash, (void*)str10, (void*)str10);
	HashInsert(hash, (void*)str11, (void*)str11);

	printf(CYAN "FOR EACH TEST\n" RESET_COLOR);
	HashForEach(hash, act_func, NULL);

}

int main()
{
	printf("\n");

	InsertTest();
	RemoveTest();
	FindTest();
	ForEachTest();
	return 0;
}


