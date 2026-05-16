
#include <stdio.h>
#include <stdlib.h>

#include "variable_size_allocator.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

typedef struct big_struct
{
	size_t s1;
	size_t s2;
	size_t s3;
	size_t s4;
}four_words_t;

typedef struct small_struct
{
	int i1;
	int i2;
}one_word_t;

/*-------------------------------------------------------*/
/************************* ALLOC *************************/
/*-------------------------------------------------------*/

void TestAlloc(void)
{
	size_t space = 300
#ifndef NDEBUG
	+ 100
#endif
	;
	void* pool = (void*)malloc(space);
	
	four_words_t* four1 = NULL;
	four_words_t* four2 = NULL;
	four_words_t* four3 = NULL;
	four_words_t* four4 = NULL;
	four_words_t* four5 = NULL;
	
	one_word_t* one1 = NULL;
	one_word_t* one2 = NULL;
	one_word_t* one3 = NULL;
	one_word_t* one4 = NULL;
	one_word_t* one5 = NULL;
	
	vsa_t* vsa = VSAInit(pool, space);
	
	four1 = VSAAlloc(vsa, 32);
	four2 = VSAAlloc(vsa, 32);
	four3 = VSAAlloc(vsa, 32);
	four4 = VSAAlloc(vsa, 32);
	four5 = VSAAlloc(vsa, 32);
	
	four1->s1 = 1; four1->s2 = 2; four1->s3 = 3; four1->s4 = 4;
	four2->s1 = 1; four2->s2 = 2; four2->s3 = 3; four1->s4 = 4;
	four3->s1 = 1; four3->s2 = 2; four3->s3 = 3; four1->s4 = 4;
	four4->s1 = 1; four4->s2 = 2; four4->s3 = 3; four1->s4 = 4;
	four5->s1 = 1; four5->s2 = 2; four5->s3 = 3; four1->s4 = 4;
	
	printf(CYAN "ALLOCATE SIZE 4\n" RESET_COLOR);	
	if (1 != four1->s1 || 2 != four1->s2 || 3 != four1->s3 || 4 != four1->s4 ||
	    1 != four2->s1 || 2 != four2->s2 || 3 != four2->s3 || 4 != four1->s4 ||
	    1 != four3->s1 || 2 != four3->s2 || 3 != four3->s3 || 4 != four1->s4 ||
	    1 != four4->s1 || 2 != four4->s2 || 3 != four4->s3 || 4 != four1->s4 ||
	    1 != four5->s1 || 2 != four5->s2 || 3 != four5->s3 || 4 != four1->s4)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("allocated wrong \n");
		printf("expected: 1\nactual: %ld\n", four1->s1);
		printf("expected: 2\nactual: %ld\n", four1->s2);
		printf("expected: 3\nactual: %ld\n\n", four1->s3);
		free(pool);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("allocated right\n\n");
	
	one1 = VSAAlloc(vsa, 8);
	one2 = VSAAlloc(vsa, 8);
	one3 = VSAAlloc(vsa, 8);
	one4 = VSAAlloc(vsa, 8);
	one5 = VSAAlloc(vsa, 8);
	
	one1->i1 = 1; one1->i2 = 2;
	one2->i1 = 1; one2->i2 = 2;
	one3->i1 = 1; one3->i2 = 2;
	one4->i1 = 1; one4->i2 = 2;
	one5->i1 = 1; one5->i2 = 2;
	
	printf(CYAN "ALLOCATE SIZE 1\n" RESET_COLOR);
	if (1 != one1->i1 || 2 != one1->i2 ||
	    1 != one2->i1 || 2 != one2->i2 ||
	    1 != one3->i1 || 2 != one3->i2 ||
	    1 != one4->i1 || 2 != one4->i2 ||
	    1 != one5->i1 || 2 != one5->i2)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("allocated wrong \n");
		printf("expected: 1\nactual: %d\n", one1->i1);
		printf("expected: 2\nactual: %d\n", one1->i2);
		free(pool);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("allocated right\n\n");
	
	free(pool);
}

/*------------------------------------------------------*/
/************************* FREE *************************/
/*------------------------------------------------------*/

void TestFree(void)
{
	size_t space = 200
#ifndef NDEBUG
	+ 100
#endif
	;
	void* pool = (void*)malloc(space);
	
	four_words_t* four1 = NULL;
	four_words_t* four2 = NULL;
	
	one_word_t* one1 = NULL;
	one_word_t* one2 = NULL;
	one_word_t* one3 = NULL;
	one_word_t* one4 = NULL;
	one_word_t* one5 = NULL;
	one_word_t* one6 = NULL;
	one_word_t* one7 = NULL;
	one_word_t* one8 = NULL;
	one_word_t* one9 = NULL;
	one_word_t* one10 = NULL;
	one_word_t* one11 = NULL;
	
	vsa_t* vsa = VSAInit(pool, space);
	
	one1 = VSAAlloc(vsa, 8);
	one2 = VSAAlloc(vsa, 8);
	one3 = VSAAlloc(vsa, 8);
	one4 = VSAAlloc(vsa, 8);
	one5 = VSAAlloc(vsa, 8);
	one6 = VSAAlloc(vsa, 8);
	one7 = VSAAlloc(vsa, 8);
	one8 = VSAAlloc(vsa, 8);
	one9 = VSAAlloc(vsa, 8);
	one10 = VSAAlloc(vsa, 8);
	one11 = VSAAlloc(vsa, 8);
	

	
	one1->i1 = 1; one1->i2 = 2;
	one2->i1 = 1; one2->i2 = 2;
	one3->i1 = 1; one3->i2 = 2;
	one4->i1 = 1; one4->i2 = 2;
	one5->i1 = 1; one5->i2 = 2;
	one6->i1 = 1; one6->i2 = 2;
	one7->i1 = 1; one7->i2 = 2;
	one8->i1 = 1; one8->i2 = 2;
	one9->i1 = 1; one9->i2 = 2;
	one10->i1 = 1; one10->i2 = 2;
	one11->i1 = 1; one11->i2 = 2;

	VSAFree(one2);
	VSAFree(one4);
	VSAFree(one5);
	VSAFree(one6);
	VSAFree(one8);
	VSAFree(one9);
	VSAFree(one10);
	

	four1 = VSAAlloc(vsa, 32);
	four1->s1 = 1; four1->s2 = 2; four1->s3 = 3; four1->s4 = 4;
	four2 = VSAAlloc(vsa, 32);
	four2->s1 = 1; four2->s2 = 2; four2->s3 = 3; four2->s4 = 4;	
	
	printf(CYAN "ALLOCATE AFTER FREE\n" RESET_COLOR);
	if (1 != four1->s1 || 2 != four1->s2 || 3 != four1->s3 || 4 != four1->s4 ||
	    1 != four2->s1 || 2 != four2->s2 || 3 != four2->s3 || 4 != four1->s4)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("free or defraction failed \n");
		printf("expected: 1\nactual: %ld\n", four1->s1);
		printf("expected: 2\nactual: %ld\n", four1->s2);
		printf("expected: 3\nactual: %ld\n\n", four1->s3);
		free(pool);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("free and defraction work right\n\n");
	free(pool);
}

/*---------------------------------------------------------------------*/
/************************* LARGEST CHUNCK FREE *************************/
/*---------------------------------------------------------------------*/

void TestLargestChunck(void)
{
	size_t space = 232
#ifndef NDEBUG
	+ 100
#endif
	;
	void* pool = (void*)malloc(space);
	size_t largest_chunck = 0;
	
	four_words_t* four1 = NULL;
	four_words_t* four2 = NULL;
	
	one_word_t* one1 = NULL;
	one_word_t* one2 = NULL;
	one_word_t* one3 = NULL;
	one_word_t* one4 = NULL;
	one_word_t* one5 = NULL;
	one_word_t* one6 = NULL;
	one_word_t* one7 = NULL;
	one_word_t* one8 = NULL;
	vsa_t* vsa = NULL;
	pool = (void*)((char*)pool + 3);
	vsa = VSAInit(pool, space);
/*
	vsa_t* vsa = VSAInit(pool, space);
*/	
	one1 = VSAAlloc(vsa, 8);
	one2 = VSAAlloc(vsa, 8);
	one3 = VSAAlloc(vsa, 8);
	one4 = VSAAlloc(vsa, 8);
	
	four1 = VSAAlloc(vsa, 32);

	one5 = VSAAlloc(vsa, 8);
	one6 = VSAAlloc(vsa, 8);

	four2 = VSAAlloc(vsa, 32);

	one7 = VSAAlloc(vsa, 8);
	one8 = VSAAlloc(vsa, 8);
		
	one1->i1 = 1; one1->i2 = 2;
	one2->i1 = 1; one2->i2 = 2;
	one3->i1 = 1; one3->i2 = 2;
	one4->i1 = 1; one4->i2 = 2;
	one5->i1 = 1; one5->i2 = 2;
	one6->i1 = 1; one6->i2 = 2;
	one7->i1 = 1; one7->i2 = 2;
	one8->i1 = 1; one8->i2 = 2;
	four1->s1 = 1; four1->s2 = 2; four1->s3 = 3; four1->s4 = 4;
	four2->s1 = 1; four2->s2 = 2; four2->s3 = 3; four1->s4 = 4;	
	
	VSAFree(one2);
	VSAFree(one3);
	VSAFree(one5);
	VSAFree(four1);
	
	largest_chunck = VSALargestChunkFree(vsa);
	printf(CYAN "LARGEST CHUNCK\n" RESET_COLOR);
	if (56 != largest_chunck)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("didnt get the right size of largest chunck\n");
		printf("expected: 56\nactual: %ld\n", largest_chunck);
		free(pool);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("got largest chunk right\n\n");
	pool = (void*)((char*)pool - 3);
	free(pool);	
}


int main()
{
	printf("\n");
	TestAlloc();
	TestFree();
	TestLargestChunck();
	return 0;
}
