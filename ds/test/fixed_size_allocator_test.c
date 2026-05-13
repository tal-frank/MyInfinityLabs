
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "fixed_size_allocator.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

typedef struct test_stract
{
	double d;
	int i;
	char ch;
}tryout_t;

void TestSuggest(void)
{
	size_t suggest = 0;
	
	suggest = FSASuggestSize(13, 6);
	printf(CYAN "SUGGEST\n" RESET_COLOR);
	if (104 != suggest)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("wrong number of bytes suggestion\n");
		printf("expected: 104\nactual: %ld\n\n", suggest);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("right number of bytes suggestion\n\n");
}

void TestInitAlloc(void)
{
	size_t suggest = 0;
	void* pool = NULL;
	tryout_t* tryout1 = NULL;
	tryout_t* tryout2 = NULL;
	tryout_t* tryout3 = NULL;
	tryout_t* tryout4 = NULL;
	tryout_t* tryout5 = NULL;
	tryout_t* tryout6 = NULL;
	
	suggest = FSASuggestSize(13, 6);
	pool = (void*)malloc(suggest);

	FSAInit(pool, suggest, 13);
	
	tryout1 = FSAAlloc(pool);
	tryout2 = FSAAlloc(pool);
	tryout3 = FSAAlloc(pool);
	tryout4 = FSAAlloc(pool);
	tryout5 = FSAAlloc(pool);
	tryout6 = FSAAlloc(pool);
	
	tryout1->d = 1; tryout1->i = 1; tryout1->ch = 'a';	
	tryout2->d = 2; tryout2->i = 2; tryout2->ch = 'b';
	tryout3->d = 3; tryout3->i = 3; tryout3->ch = 'c';
	tryout4->d = 4; tryout4->i = 4; tryout4->ch = 'd';
	tryout5->d = 5; tryout5->i = 5; tryout5->ch = 'e';
	tryout6->d = 6; tryout6->i = 6; tryout6->ch = 'f';
	
	printf(CYAN "ALLOC\n" RESET_COLOR);
	if (1.0 != (double)tryout1->d || 1 != (int)tryout1->i || 'a' != (char)tryout1->ch ||
	    6.0 != (double)tryout6->d || 6 != (int)tryout6->i || 'f' != (char)tryout6->ch)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("not saved as expected\n");
		printf("expected: 1\nactual: %f\n\n", tryout1->d);
		printf("expected: 1\nactual: %d\n\n", tryout1->i);
		printf("expected: a\nactual: %c\n\n", tryout1->ch);
		printf("expected: 6\nactual: %f\n\n", tryout6->d);
		printf("expected: 6\nactual: %d\n\n", tryout6->i);
		printf("expected: f\nactual: %c\n\n", tryout6->ch);
		free(pool);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("saved as expected\n\n");
	free(pool);
	pool = NULL;
}

void TestFree(void)
{
	size_t suggest = 0;
	void* pool = NULL;
	tryout_t* tryout1 = NULL;
	tryout_t* tryout2 = NULL;
	tryout_t* tryout3 = NULL;
	tryout_t* tryout4 = NULL;
	tryout_t* tryout5 = NULL;
	tryout_t* tryout6 = NULL;
	tryout_t* tryout7 = NULL;
	tryout_t* tryout8 = NULL;
	tryout_t* tryout9 = NULL;
	tryout_t* tryout10 = NULL;
	
	suggest = FSASuggestSize(13, 6);
	pool = (void*)malloc(suggest);

	FSAInit(pool, suggest, 13);
	
	tryout1 = FSAAlloc(pool);
	tryout2 = FSAAlloc(pool);
	tryout3 = FSAAlloc(pool);
	tryout4 = FSAAlloc(pool);
	tryout5 = FSAAlloc(pool);
	tryout6 = FSAAlloc(pool);
	
	tryout1->d = 1; tryout1->i = 1; tryout1->ch = 'a';
	tryout2->d = 2; tryout2->i = 2; tryout2->ch = 'b';
	tryout3->d = 3; tryout3->i = 3; tryout3->ch = 'c';
	tryout4->d = 4; tryout4->i = 4; tryout4->ch = 'd';
	tryout5->d = 5; tryout5->i = 5; tryout5->ch = 'e';
	tryout6->d = 6; tryout6->i = 6; tryout6->ch = 'f';
	
	FSAFree(pool, tryout3);
	tryout7 = FSAAlloc(pool);
	tryout7->d = 7; tryout7->i = 7; tryout7->ch = 'g';
	
	printf(CYAN "1 FREE\n" RESET_COLOR);
	if (7.0 != (double)tryout7->d || 7 != (int)tryout7->i || 'g' != (char)tryout7->ch)
	    
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("not saved as expected\n");
		printf("expected: 9\nactual: %f\n\n", tryout9->d);
		printf("expected: 9\nactual: %d\n\n", tryout9->i);
		printf("expected: i\nactual: %c\n\n", tryout9->ch);
		free(pool);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("saved as expected\n\n");
	
	FSAFree(pool, tryout1);
	FSAFree(pool, tryout5);
	FSAFree(pool, tryout6);
	
	tryout8 = FSAAlloc(pool);
	tryout9 = FSAAlloc(pool);
	tryout10 = FSAAlloc(pool);
	tryout8->d = 8; tryout8->i = 8; tryout8->ch = 'h';
	tryout9->d = 9; tryout9->i = 9; tryout9->ch = 'i';
	tryout10->d = 10; tryout10->i = 10; tryout10->ch = 'j';
	
	printf(CYAN "3 FREEs\n" RESET_COLOR);
	if (9.0 != (double)tryout9->d || 9 != (int)tryout9->i || 'i' != (char)tryout9->ch)
	    
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("not saved as expected\n");
		printf("expected: 9\nactual: %f\n\n", tryout9->d);
		printf("expected: 9\nactual: %d\n\n", tryout9->i);
		printf("expected: i\nactual: %c\n\n", tryout9->ch);
		free(pool);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("saved as expected\n\n");

	free(pool);
	pool = NULL;
}

void TestAmount(void)
{
	size_t suggest = 0;
	size_t amount_free = 0;
	void* pool = NULL;
	tryout_t* tryout1 = NULL;
	tryout_t* tryout2 = NULL;
	tryout_t* tryout3 = NULL;
	tryout_t* tryout4 = NULL;
	tryout_t* tryout5 = NULL;
	tryout_t* tryout6 = NULL;
	
	suggest = FSASuggestSize(13, 6);
	pool = (void*)malloc(suggest);

	FSAInit(pool, suggest, 13);
	
	printf(CYAN "3 FREEs\n" RESET_COLOR);
	amount_free = FSACountFree(pool);
	if (6 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right when initialized\n");
		printf("expected: 6\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right when initialized\n\n");
	
	tryout1 = FSAAlloc(pool);
	tryout2 = FSAAlloc(pool);
	tryout3 = FSAAlloc(pool);
	
	amount_free = FSACountFree(pool);
	if (3 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right after 3 allocs\n");
		printf("expected: 3\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right after 3 allocs\n\n");
	
	tryout4 = FSAAlloc(pool);
	tryout5 = FSAAlloc(pool);
	tryout6 = FSAAlloc(pool);
	
	amount_free = FSACountFree(pool);
	if (0 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right after 6 allocs\n");
		printf("expected: 0\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right after 6 allocs\n\n");
	
	FSAFree(pool, tryout1);
	FSAFree(pool, tryout5);
	FSAFree(pool, tryout6);
	
	amount_free = FSACountFree(pool);
	if (3 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right after 3 frees\n");
		printf("expected: 3\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right after 3 frees\n\n");
	
	FSAFree(pool, tryout2);
	FSAFree(pool, tryout3);
	FSAFree(pool, tryout4);
	
	amount_free = FSACountFree(pool);
	if (6 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right after free all\n");
		printf("expected: 6\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right after free all\n\n");
	free(pool);
}
/*
void TestInitWithoutSuggest(void)
{
	size_t amount_free = 0;
	void* pool = NULL;
	size_t suggest = FSASuggestSize(13, 6);
	pool = (void*)malloc(80);
	FSAInit(pool, 72, 13);
	
	printf(CYAN "INIT WITHOUT SUGGEST\n" RESET_COLOR);
	amount_free = FSACountFree(pool);
	if (4 != amount_free)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("amount is not right when initialized\n");
		printf("expected: 4\nactual: %ld\n\n", amount_free);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("amount is right when initialized\n\n");
	
}
*/
int main()
{
	printf("\n");
	TestSuggest();
	TestInitAlloc();
	TestFree();
	TestAmount();
/*	TestInitWithoutSuggest();
*/	return 0;
}
