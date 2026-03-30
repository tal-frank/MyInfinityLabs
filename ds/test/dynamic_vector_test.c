
#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#include "../include/dynamic_vector.h"


int main()
{
	size_t cap = 0;
	size_t size = 0;
	size_t access_2 = 2;
	size_t access_5 = 5;
	size_t access_7 = 7;
	int capacity = 4;
	size_t element_size = 4;
	int* element1 = 0;
	int* element2 = 0;
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	int num7 = 7;
	int num8 = 8;
	int num9 = 9;
	int num10 = 10;
	
	dvector_t* dvector = DvectorCreate(capacity, element_size);

/*-------------------------------------------------------------------*/
/***************************** PUSHING 4 *****************************/
/*-------------------------------------------------------------------*/

	
	DvectorPush(dvector, &num1);
	DvectorPush(dvector, &num2);
	DvectorPush(dvector, &num3);
	DvectorPush(dvector, &num4);
	
	element1 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is: %d\n", *element1);
	*element1 = 4;
	
	element2 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is now: %d\n\n", *element2);
	
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("after 4 elements pushed\n");
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);
	
/*-------------------------------------------------------------------*/
/***************************** PUSHING 3 *****************************/
/*-------------------------------------------------------------------*/

	DvectorPush(dvector, &num5);
	DvectorPush(dvector, &num6);
	DvectorPush(dvector, &num7);	
	
	element1 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is: %d\n", *element1);
	*element1 = 5;
	
	element2 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is now: %d\n\n", *element2);
	
	element1 = (int*)DvectorGetAccessToElement(dvector, access_5);
	printf("fifth element is: %d\n", *element1);
	*element1 = 7;
	
	element2 = (int*)DvectorGetAccessToElement(dvector, access_5);
	printf("fifth element is now: %d\n\n", *element2);
	
	printf("after 7 elements pushed\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);
	
/*-------------------------------------------------------------------*/
/***************************** PUSHING 3 *****************************/
/*-------------------------------------------------------------------*/
	
	DvectorPush(dvector, &num8);
	DvectorPush(dvector, &num9);
	DvectorPush(dvector, &num10);
	
	printf("after 10 elements pushed\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);
	
/*------------------------------------------------------------------*/
/***************************** POPING 2 *****************************/
/*------------------------------------------------------------------*/


	DvectorPop(dvector);
	DvectorPop(dvector);
	
	printf("after 2 elements poped\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);

/*------------------------------------------------------------------*/
/***************************** POPING 6 *****************************/
/*------------------------------------------------------------------*/

	DvectorPop(dvector);
	DvectorPop(dvector);
	DvectorPop(dvector);
	DvectorPop(dvector);
	DvectorPop(dvector);
	DvectorPop(dvector);
	
	printf("after 8 elements poped\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);
	
	element1 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is: %d\n", *element1);
	*element1 = 4;
	
	element2 = (int*)DvectorGetAccessToElement(dvector, access_2);
	printf("second element is now: %d\n\n", *element2);
	
/*-------------------------------------------------------------------*/
/***************************** PUSHING 8 *****************************/
/*-------------------------------------------------------------------*/

	DvectorPush(dvector, &num5);
	DvectorPush(dvector, &num6);
	DvectorPush(dvector, &num7);
	DvectorPush(dvector, &num5);
	DvectorPush(dvector, &num6);
	DvectorPush(dvector, &num7);
	DvectorPush(dvector, &num5);
	DvectorPush(dvector, &num9);

	printf("after 6 elements pushed again\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);

	
	element1 = (int*)DvectorGetAccessToElement(dvector, access_7);
	printf("seventh element is: %d\n", *element1);
	*element1 = 6;
	
	element2 = (int*)DvectorGetAccessToElement(dvector, access_7);
	printf("seventh element is now: %d\n\n", *element2);
	
/*-------------------------------------------------------------------*/
/***************************** SHRINKING *****************************/
/*-------------------------------------------------------------------*/
	
	DvectorShrink(dvector);
	printf("after shrinking less then half\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);

/*-------------------------------------------------------------------------*/
/***************************** EXPANDING TO 45 *****************************/
/*-------------------------------------------------------------------------*/
	
	DvectorExpand(dvector, 45);
	printf("after expanding to 45\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);


/*-----------------------------------------------------------------------*/
/***************************** POPING SAFE 6 *****************************/
/*-----------------------------------------------------------------------*/

	DvectorSafePop(dvector);
	DvectorSafePop(dvector);
	DvectorSafePop(dvector);
	DvectorSafePop(dvector);
	DvectorSafePop(dvector);
	DvectorSafePop(dvector);
	
	printf("after popin safely 6\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);

/*------------------------------------------------------------------------*/
/***************************** SHRINKING HALF *****************************/
/*------------------------------------------------------------------------*/
	
	DvectorShrink(dvector);
	printf("after shrinking more then half\n");
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);

/*-------------------------------------------------------------------------*/
/***************************** EXPANDING TO 15 *****************************/
/*-------------------------------------------------------------------------*/
	
	printf("after expanding to less then 22\n");
	DvectorExpand(dvector, 18);
	cap = DvectorCapacity(dvector);
	size = DvectorSize(dvector);
	printf("capacity is: %ld\n", cap);
	printf("size is: %ld\n\n", size);
	
	
	DvectorDestroy(dvector);
		
	return 0;
}
