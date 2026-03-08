/**********************
 * structs
 * Author: Tal Frank
 * Reviewer: Name
**********************/

#include <string.h>

#define MAX(a, b) (a > b ? a : b)
#define MAX3(a, b, c) ((a > b && a > c) ? (a) : (b > c) ? (b) : (c))
#define SIZEOF(a) ((char*)(&a + 1) - (char*)(&a))
#define TYPE_SIZEOF(type) (((char*)((type*)NULL + 1)) - (char*)((type*)NULL))


typedef struct operations
{
	void (*Print)(const void*);
	void (*Add)(void*, int);
	void (*Clear)(void*);
}operation_t;


typedef struct elements
{
	void* data;
	const operation_t* op;
}element_t;


/************************* FUNCTIONS DECLERATIONS ***************************/

void PrintAll(const element_t arr[], size_t size);
void AddAll(element_t arr[], size_t size ,int num);
void Clear(element_t arr[], size_t size);

void PrintInt(const void* integer);
void AddInt(void* integer, int num);
void ClearInt(void* somthing);

void PrintFloat(const void* floater);
void AddFloat(void* floater, int num);
void ClearFloat(void* somthing);

void PrintString(const void* string);
void AddString(void* somthing, int num);
void ClearString(void* somthing);


/************************* ARR OPERATIONS ***************************/


void PrintAll(const element_t arr[], size_t size)
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		if (NULL == arr[i].data)
		{
			printf("arr[%ld] is cleared\n", i);
			continue;
		}
		arr[i].op->Print(arr[i].data);
	}
}


void AddAll(element_t arr[], size_t size , int num)
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		arr[i].op->Add(&arr[i], num);
	}
}

void Clear(element_t arr[], size_t size)
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		arr[i].op->Clear(&arr[i]);
	}
}


/************************* INT OPERATIONS ***************************/

void PrintInt(const void* integer)
{
	printf("arr[0] = %d\n" , *(int*)&integer);
}


void AddInt(void* integer, int num)
{
	element_t* integer_ptr = (element_t*)integer;
	*(int*)&integer_ptr->data += num;
}


void ClearInt(void* integer)
{
	element_t* int_ptr = (element_t*)integer;
	int_ptr->data = NULL;
}

/************************* FLOAT OPERATIONS ***************************/

void PrintFloat(const void* floater)
{	
	printf("arr[1] = %f\n" , *(float*)&floater);
}


void AddFloat(void* floater, int num)
{
	element_t* floater_ptr = (element_t*)floater;
	*(float*)&floater_ptr->data += num;
}


void ClearFloat(void* floater)
{
	element_t* float_ptr = (element_t*)floater;
	float_ptr->data = NULL;
}


/************************* STRING OPERATIONS ***************************/

void PrintString(const void* string)
{
	printf("arr[2] = %s\n" , (char*)string);
}


void AddString(void* string, int num)
{
	element_t* str_ptr = (element_t*)string;
	char* num_str;
	int cnt = 0;	
	int log = num;
	
	while (0 != log)
	{
		log /= 10;
		++cnt;
	}
	num_str = malloc(sizeof(char)*cnt);
	sprintf(num_str, "%d" , num);
	
	str_ptr->data = (char*)realloc(str_ptr->data, strlen(str_ptr->data) + sizeof(char) * cnt);
	strcat(str_ptr->data, num_str);
	free(num_str);
}


void ClearString(void* string)
{
	element_t* str_ptr = (element_t*)string;
	free(str_ptr->data);
	str_ptr->data = NULL;
}






