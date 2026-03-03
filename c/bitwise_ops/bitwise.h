/**********************
 * ws6_files
 * Author: Tal frank
 * Reviewer: Name
**********************/

#include "bitwise.c"


#ifndef __BITWISE_H__
#define __BITWISE_H__

long Pow2(unsigned int x, unsigned int y);

int IsPowOf2Loop(unsigned int n);

int IsPowOf2Comp(unsigned int n);

int IsPowOf2(unsigned int n);

int Add1Comp(int n);

int Add1(int n);

void PrintNumsWith3BitsOn(unsigned int* arr, size_t size);

unsigned char ByteMirrorLoop(unsigned char byte);

unsigned char ByteMirror(unsigned char byte);

int IsSecondAndSixthBitOn(unsigned char byte);

int IsSecondOrSixthBitOn(unsigned char byte);

unsigned char SwapThirdAndFifthBits(unsigned char byte);

unsigned int MaxDivisedBy16(unsigned char byte);

void SwapVars(int* a, int* b);

void SwapVarsV2(int* a, int* b);

void SwapVarsV3(int* a, int* b);

unsigned int CountSetBitsLoop(unsigned int);

unsigned int CountSetBits(unsigned int);

void FloatAnalysis(float num);

#endif /* end of __BITWISE_H__*/





