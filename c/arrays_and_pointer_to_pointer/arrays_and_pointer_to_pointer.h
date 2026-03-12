#ifndef ARRAYS_AND_POINTERS_TO_POINTERS_h
#define ARRAYS_AND_POINTERS_TO_POINTERS_h

#include <stddef.h> /* needed for size_t*/
#include "arrays_and_pointer_to_pointer.c"

size_t Jusephus( size_t start_index, size_t soldier_num );

void TwoD( const int* mat, int* dest ,int rows, int cols);

void PrintEnv(const char* envp[]);


#endif
