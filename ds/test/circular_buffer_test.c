
#include <stdio.h>
#include <stdlib.h>

#include "../include/circular_buffer.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"


/*-----------------------------------------------------------------------*/
/************************* CREATE & DESTROY TEST *************************/
/*-----------------------------------------------------------------------*/

void CreateDestroyTest(void)
{
	cbuff_t* cbuff = CBuffCreate(10UL);

	printf("started " CYAN "CREATE/DESTROY" RESET_COLOR " test:\n");
	
	if (NULL == cbuff)
	{
		printf(RED "create FAILED\n\n" RESET_COLOR);
		return;
	}
	
	CBuffDestroy(cbuff);	
	printf(GREEN "create/destroy PASSED\n\n" RESET_COLOR);
}


/*------------------------------------------------------------*/
/************************* WRITE TEST *************************/
/*------------------------------------------------------------*/

void WriteTest(void)
{
	cbuff_t* cbuff = CBuffCreate(24UL);
	int src[] = {1, 2, 3, 4, 5, 6};
	size_t amount_of_bytes_copied = 0;
	
	printf("started " CYAN "WRITE" RESET_COLOR " test:\n");
	
	amount_of_bytes_copied = CBuffWrite(cbuff, src, 4);
	if (4 != amount_of_bytes_copied || 20 != CBuffFreeSpaceLeft(cbuff))
	{
		printf(RED "write FAILED 1\n\n" RESET_COLOR);
		return;
	}
	
	amount_of_bytes_copied = CBuffWrite(cbuff, src, 12);
	if (12 != amount_of_bytes_copied || 8 != CBuffFreeSpaceLeft(cbuff))
	{
		printf(RED "write FAILED 2\n\n" RESET_COLOR);
		return;
	}
	
	amount_of_bytes_copied = CBuffWrite(cbuff, src, 12);
	if (8 != amount_of_bytes_copied || 0 != CBuffFreeSpaceLeft(cbuff))
	{
		printf(RED "write FAILED 3\n\n" RESET_COLOR);
		return;
	}
	
	printf(GREEN "write PASSED\n\n" RESET_COLOR);
	CBuffDestroy(cbuff);	
}


/*-----------------------------------------------------------*/
/************************* READ TEST *************************/
/*-----------------------------------------------------------*/

void ReadTest(void)
{
	cbuff_t* cbuff = CBuffCreate(24UL);
	int src[] = {1, 2, 3, 4, 5, 6};
	int* dest = (int*)malloc(7 * sizeof(int));
	size_t amount_of_bytes_copied = 0;
	
	printf("started " CYAN "READ" RESET_COLOR " test:\n");
	
	CBuffWrite(cbuff, src, 24);
	
	amount_of_bytes_copied = CBuffRead(cbuff, dest, 4);
	if (4 != amount_of_bytes_copied    || 
	    4 != CBuffFreeSpaceLeft(cbuff) ||
	    1 != dest[0])
	{
		printf(RED "write FAILED 1\n\n" RESET_COLOR);
		return;
	}
	
	amount_of_bytes_copied = CBuffRead(cbuff, dest, 12);
	if (12 != amount_of_bytes_copied    || 
	    16 != CBuffFreeSpaceLeft(cbuff) ||
	    2 != dest[0] || 3 != dest[1] || 4 != dest[2])
	{
		printf(RED "write FAILED 2\n\n" RESET_COLOR);
		return;
	}
	
	amount_of_bytes_copied = CBuffRead(cbuff, dest, 12);
	if (8 != amount_of_bytes_copied     || 
	    24 != CBuffFreeSpaceLeft(cbuff) ||
	    5 != dest[0] || 6 != dest[1])
	{
		printf(RED "write FAILED 3\n\n" RESET_COLOR);
		return;
	}
	
	CBuffWrite(cbuff, src, 12);
	amount_of_bytes_copied = CBuffRead(cbuff, dest, 8);
	if (8 != amount_of_bytes_copied     || 
	    20 != CBuffFreeSpaceLeft(cbuff) ||
	    1 != dest[0] || 2 != dest[1])
	{
		printf(RED "write FAILED 4\n\n" RESET_COLOR);
		return;
	}
	
	free(dest);
	printf(GREEN "read PASSED\n\n" RESET_COLOR);
	CBuffDestroy(cbuff);
}


/*---------------------------------------------------------------*/
/************************* IS EMPTY TEST *************************/
/*---------------------------------------------------------------*/

void IsEmptyTest(void)
{
	cbuff_t* cbuff = CBuffCreate(24UL);
	int src[] = {1, 2, 3, 4, 5, 6};
	int* dest = (int*)malloc(7 * sizeof(int));

	printf("started " CYAN "IS EMPTY" RESET_COLOR " test:\n");
	
	if (!CBuffIsEmpty(cbuff))
	{
		printf(RED "is empty FAILED 1\n\n" RESET_COLOR);
		return;
	}
	
	CBuffWrite(cbuff, src, 1);	
	if (CBuffIsEmpty(cbuff))
	{
		printf(RED "is empty FAILED 2\n\n" RESET_COLOR);
		return;
	}
	
	CBuffRead(cbuff, dest, 4);
	if (!CBuffIsEmpty(cbuff))
	{
		printf(RED "is empty FAILED 3\n\n" RESET_COLOR);
		return;
	}
	
	free(dest);
	printf(GREEN "is empty PASSED\n\n" RESET_COLOR);
	CBuffDestroy(cbuff);
}


/*---------------------------------------------------------------*/
/************************* CAPACITY TEST *************************/
/*---------------------------------------------------------------*/

void CapacityTest(void)
{
	cbuff_t* cbuff1 = CBuffCreate(24UL);
	cbuff_t* cbuff2 = CBuffCreate(5UL);
	
	printf("started " CYAN "CAPACITY" RESET_COLOR " test:\n");
	
	if (24 != CBuffSize(cbuff1))
	{
		printf(RED "capacity FAILED 1\n\n" RESET_COLOR);
		return;
	}
	CBuffDestroy(cbuff1);
	
	if (5 != CBuffSize(cbuff2))
	{
		printf(RED "capacity FAILED 2\n\n" RESET_COLOR);
		return;
	}
	CBuffDestroy(cbuff2);
	
	printf(GREEN "capacity PASSED\n\n" RESET_COLOR);
}


/*-----------------------------------------------------------*/
/************************* MAIN TEST *************************/
/*-----------------------------------------------------------*/

int main()
{
	printf("\n");
	
	CreateDestroyTest();
	CapacityTest();
	WriteTest();
	ReadTest();
	IsEmptyTest();
	return 0;
}

