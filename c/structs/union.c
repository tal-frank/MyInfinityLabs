/**********************
 * structs
 * Author: Tal Frank
 * Reviewer: Name
**********************/

#include <string.h>

typedef union arr_types
{
	int i;
	float f;
	char* s;
} arr_type_u;

typedef struct operations
{
	void (*Print)(const void*);
	void (*Add)(void*, int);
	void (*Clear)(void*);
}operation_t;

typedef struct elements
{
	arr_type_u data;
	const operation_t* op;
}element_t;


void PrintInt(const void* integer);
void AddInt(void* integer, int num);
void ClearInt(void* somthing);

void PrintFloat(const void* floater);
void AddFloat(void* floater, int num);
void ClearFloat(void* somthing);

void PrintString(const void* string);
void AddString(void* somthing, int num);
void ClearString(void* somthing);

void PrintAll(const element_t arr[], size_t size);
void AddAll(element_t arr[], size_t size ,int num);
void Clear(element_t arr[], size_t size);

/************************* ARR OPERATIONS ***************************/


void PrintAll(const element_t arr[], size_t size)
{
	size_t i;
	for (i = 0; i < size; ++i)
	{
		arr[i].op->Print(&arr[i]);
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
	element_t* integer_ptr = (element_t*)integer;
	printf("arr[0] = %d\n" , integer_ptr->data.i);
}


void AddInt(void* integer, int num)
{
	element_t* integer_ptr = (element_t*)integer;
	integer_ptr->data.i += num;
}


void ClearInt(void* integer)
{
	element_t* int_ptr = (element_t*)integer;
	int_ptr->data.s = NULL;
}

/************************* FLOAT OPERATIONS ***************************/

void PrintFloat(const void* floater)
{	
	element_t* floater_ptr = (element_t*)floater;
	printf("arr[1] = %f\n" , floater_ptr->data.f);
}


void AddFloat(void* floater, int num)
{
	element_t* floater_ptr = (element_t*)floater;
	floater_ptr->data.f += num;
}


void ClearFloat(void* floater)
{
	element_t* float_ptr = (element_t*)floater;
	float_ptr->data.s = NULL;
}


/************************* STRING OPERATIONS ***************************/

void PrintString(const void* string)
{
	element_t* str_ptr = (element_t*)string;
	printf("arr[2] = %s\n" , str_ptr->data.s);
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
	
	str_ptr->data.s = (char*)realloc(str_ptr->data.s, strlen(str_ptr->data.s) + sizeof(char) * cnt);
	strcat(str_ptr->data.s, num_str);
	free(num_str);
}


void ClearString(void* string)
{
	element_t* str_ptr = (element_t*)string;
	free(str_ptr->data.s);
	str_ptr->data.s = NULL;
}



