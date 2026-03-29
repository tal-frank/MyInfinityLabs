/**********************
* Dynamic Vector
* Author: Tal Frank
* Reviewer: Yael Novick
* Last update: 28/03/2026
**********************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

#include "../include/dynamic_vector.h"

#define GROWTH_FACTOR (2)

/*-------------------------------------------------------------------------------*/
/***************************** DYNAMIC VECTOR STRUCT *****************************/
/*-------------------------------------------------------------------------------*/

struct Dynamic_vector
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char* data;
};


enum 
{
	SUCCESS = 0,
	FAILURE = 1
};


/*-----------------------------------------------------------------------------------------*/
/***************************** CREATE & DESTROY DYNAMIC VECTOR *****************************/
/*-----------------------------------------------------------------------------------------*/

dvector_t* DvectorCreate(size_t capacity, size_t element_size)
{
	dvector_t* dvector = (dvector_t*)malloc(sizeof(dvector_t));
	if (NULL == dvector)
	{
		printf("can not allocate sapce for vector\n");
		return NULL;
	}
	
	dvector->data = (char*)malloc(capacity * element_size);
	if (NULL == dvector->data)
	{
		printf("can not allocate sapce for vector\n");
		free(dvector);
		return NULL;
	}
	
	dvector->capacity = capacity;
	dvector->element_size = element_size;
	dvector->size = 0;
	return dvector;
}


void DvectorDestroy(dvector_t* vector)
{
	free(vector->data);
	free(vector);
}


/*-------------------------------------------------------------------------*/
/***************************** PUSH POP ACCESS *****************************/
/*-------------------------------------------------------------------------*/

int DvectorPush(dvector_t* vector, const void* element)
{
	char* new_data = 0;
	
	assert(NULL != vector);
	assert(NULL != element);

	if (vector->size >= vector->capacity)
	{
		vector->capacity *= GROWTH_FACTOR;
		new_data = realloc(vector->data, vector->capacity * vector->element_size);
		if (NULL == new_data)
		{
			printf("can not insert data\n");
			return FAILURE;
		}
		vector->data = new_data;
	}
	
	memcpy(&vector->data[vector->size * vector->element_size],
		element, vector->element_size);
	++vector->size;
	
	return SUCCESS;
}


int DvectorPop(dvector_t* vector)
{
	char* new_data = 0;
	
	assert(NULL != vector);

	--vector->size;
	if (vector->size < (vector->capacity / (2 * GROWTH_FACTOR)))
	{
		vector->capacity /= GROWTH_FACTOR;
		new_data = realloc(vector->data, vector->capacity * vector->element_size);
		if (NULL ==  new_data)
		{
			printf("can not resize\n");
			return FAILURE;
		}
		vector->data = new_data;
	}
	return SUCCESS;
}


void* DvectorGetAccessToElement(dvector_t* vector, size_t index)
{
	return &vector->data[index * vector->element_size];
}


void DvectorSafePop(dvector_t* vector)
{
	assert(NULL != vector);
	--vector->size;
}


/*---------------------------------------------------------------------*/
/***************************** STRUCT DATA *****************************/
/*---------------------------------------------------------------------*/

size_t DvectorSize(const dvector_t* vector)
{
	assert(NULL != vector);
	return vector->size;
}


size_t DvectorCapacity(const dvector_t* vector)
{
	assert(NULL != vector);
	return vector->capacity;
}


/*-------------------------------------------------------------------------*/
/***************************** SHRINK & EXPAND *****************************/
/*-------------------------------------------------------------------------*/

int DvectorExpand(dvector_t* vector, size_t new_amount)
{
	char* new_data = 0;
	
	assert(NULL != vector);	
	
	if (new_amount > vector->capacity)
	{
		new_data = realloc(vector->data, new_amount * vector->element_size);
		if (NULL ==  new_data)
		{
			printf("can not resize\n");
			return FAILURE;
		}
		vector->data = new_data;
		vector->capacity = new_amount;
	}
	
	else 
	{
		printf("not a valid amount\n");
		return FAILURE;
	}	
		
	return SUCCESS;
}


int DvectorShrink(dvector_t* vector)
{
	char* new_data = 0;

	assert(NULL != vector);
	
	if (vector->size > vector->capacity / GROWTH_FACTOR)
	{
		new_data = realloc(vector->data, vector->size * vector->element_size);
		if (NULL ==  new_data)
		{
			printf("can not resize\n");
			return FAILURE;
		}
		vector->data = new_data;
		vector->capacity = vector->size;
	}
	
	else
	{
		new_data = realloc(vector->data, 
				  (vector->capacity / GROWTH_FACTOR) * vector->element_size);
		if (NULL == new_data)
		{
			printf("can not resize\n");
			return FAILURE;
		}
		vector->data = new_data;
		vector->capacity /= GROWTH_FACTOR;
	}
	return SUCCESS;
}


