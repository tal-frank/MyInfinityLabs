#ifndef __ATOI_ITOA_H__
#define __ATOI_ITOA_H__
 
#define IS_LITTLE_ENDIAN(i) *(char*)&i == 1 ? 1 : 0
 
#include <stddef.h> /*size_t*/
 
int Atoi(const char *str);
 
int AtoiBase(const char* str, size_t base); 
 
char* Itoa(int value, char* str);
 
char* ItoaBase(int value, char* str, size_t base); 
 
 
void RepeatingChars(const char* array_1, size_t array_1_length, 
                     const char* array_2, size_t array_2_length, 
                     const char* array_3, size_t array_3_length);
 
int IsLittleEndian(void);
 
 
#endif /** end of __ATOI_ITOA_H__ */
