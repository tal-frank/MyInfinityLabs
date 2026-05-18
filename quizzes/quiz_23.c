#include <stdio.h>

#include "stack.h"

#define True (1)
#define False (0)

void CheckParentheses(char* str);


void TestCheckParentheses(char* str, char* expected)
{
	printf("expected: %s\n", expected);
	printf("actual:   ");
	CheckParentheses(str);
	printf("\n");
}

int IsEqualParentheses(stack_t* stack, char parentheses_open, char parentheses_close, char ch)
{
	int is_balanced = True;
	if (parentheses_close == ch)
	{
		if (!StackIsEmpty(stack))
		{
			is_balanced = (parentheses_open == *(char*)StackPeek(stack)) ? True : False;
			StackPop(stack);
		}
		else
		{
			is_balanced = False;
		}
	}
	return is_balanced;
}

void IsBalanced(stack_t* parentheses_stack, int* is_balanced, char ch)
{
	if (']' == ch)
	{
		*is_balanced = IsEqualParentheses(parentheses_stack, '[', ']', ch);
	}
	else if (')' == ch)
	{
		*is_balanced = IsEqualParentheses(parentheses_stack, '(', ')', ch);
	}
	else if ('}' == ch)
	{
		*is_balanced = IsEqualParentheses(parentheses_stack, '{', '}', ch);
	}
}


void CheckParentheses(char* str)
{
	int is_balanced = True;
	stack_t* parentheses_stack = StackCreate(20, sizeof(char));
	
	while (is_balanced && '\0' != *str)
	{
		if ('{' == *str || '[' == *str || '(' == *str)
		{
			StackPush(parentheses_stack, &*str);
		}
		else
		{
			IsBalanced(parentheses_stack, &is_balanced, *str);
		}
		++str;
	}
	if (!is_balanced || !StackIsEmpty(parentheses_stack))
	{
		printf("Not ");
	}
	printf("Balanced\n");
	
	StackDestroy(parentheses_stack);
}


int main()
{
	char* str1 = "[]()({})";
	char* str2 = "f(fg[y]) {gr()}";
	char* str3 = "[]()({)}";
	char* str4 = "f(fg[y]) {gr)}";
	char* str5 = "(((()))))";
	char* str6 = "][(){()}";
	char* str7 = "()()()()(";
		
	TestCheckParentheses(str1, "Balanced");
	TestCheckParentheses(str2, "Balanced");
	TestCheckParentheses(str3, "Not Balanced");
	TestCheckParentheses(str4, "Not Balanced");
	TestCheckParentheses(str5, "Not Balanced");
	TestCheckParentheses(str6, "Not Balanced");
	TestCheckParentheses(str7, "Not Balanced");
	
	return 0;
}



