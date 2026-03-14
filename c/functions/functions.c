/**********************
* functions
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 12/03/2026
**********************/


#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


void InputReceiverIfElse()
{
	int inp_char = '\0' ;
	
	system ("stty -icanon -echo");
	
	while (27 != inp_char)
	{
		printf ("if/else\ntype a char: \n");
		inp_char = getchar ();
		
		if (inp_char == 'A')
		{
			printf ("A\n");
		}
		
		if (inp_char == 'T')
		{
			printf ("T\n");
		}
	}
	
	system("stty icanon echo");
}

void InputReceiverSwitch()
{
	int inp_char = '\0' ;
	
	system("stty -icanon -echo");
	
	while (27 != inp_char)
	{
		printf ("switch\ntype a char: \n");
		inp_char = getchar ();
		
		switch(inp_char)
		{
			case 'T':
				printf("T\n");
				break;
			
			case 'A':
				printf("A\n");
				break;
			
			default:
				break;
		}
	}
	
	system ("stty icanon echo");
}

void PrintLut(int mem_to_prnt)
{
	printf ("%c", (char)mem_to_prnt);
	
	if (0 != mem_to_prnt)
	{
		printf (" - pressed\n");
	}
}

void InputReceiverLut()
{	
	int inp_char = '\0' ;
	void (*print_lut_ptr)(int);
	int arr[256] = {0};
	
	arr[65] = 'A';
	arr[84] = 'T';
	print_lut_ptr = &PrintLut;
	
	system("stty -icanon -echo");
	
	while (27 != inp_char)
	{
		printf("LUT\ntype a char: \n");
		
		inp_char = getchar();
		print_lut_ptr(arr[inp_char]);
	}
	
	system("stty icanon echo");
}

