#ifndef _STRINGS_H_
#define _STRINGS_H_
#include <stddef.h>




int IsPalindrome(const char* str);

void Print7Boom(int from, int to); 

void SpaceReview(char* dest, const char* src); 




size_t StrLen( const char* str );

int StrCmp( const char* src1, const char* src2  ); 

char* StrCpy( char* dest, const char* src ); 

char* StrNCpy( char* dest, const char* src, size_t n ); 

int StrNCmp( const char* lhs, const char* rhs, size_t count ); 

int StrCaseCmp( const char* s1, const char* s2); 
       
char* StrChr( const char* str, int ch ); 

char* StrDup( const char* src ); 

char* StrCat( char* dest, const char* src ); 

char* StrNCat( char* dest, const char* src, size_t count ); 

char* StrStr( const char* str, const char* substr ); 

size_t StrSpn( const char* dest, const char* search ); 

char* StrTok( char* str, const char* delim ); 

#endif
