#ifndef _POINTERS_PART1_H_
#define _POINTERS_PART1_H_

#include <stdlib.h> /* included for malloc and free operations*/
#include <stdio.h>  /* included for io feedback */
#include <assert.h> 
#include "pointer1.c"


void SwapInt(int* var1, int* var2);

void CopyArray(const int* arr_src, const size_t size_src, int* arr_cpy, size_t size_cpy);

void PrintVarAddrss();

void SwapSize_t(size_t* var1, size_t* var2);

void SwapSize_tPointers(size_t** var1, size_t** var2);

#endif
