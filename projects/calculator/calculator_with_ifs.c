
#include <string.h> /* strlen */
#include <stdlib.h> /* free */
#include <math.h> /* pow */
#include <stdio.h> /* printf */

#include "calculator.h"
#include "stack.h"

typedef enum
{
	WRONG_INPUT = 0,
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	GET_RESULT
}state_t;

typedef enum priority
{
	PLUS_MINUS = 1,
	MUL_DIV,
	POW,
	PARENTHESIS
}priority_t;

static void OpHandler(char* input, stack_t* op_stack, stack_t* num_stack);
static void NumHandler(double num, stack_t* num_stack);
static double CalcHandler(stack_t* num_stack, stack_t* op_stack);
static double CalcMinus(double first_operand, double second_operand);
static double CalcPlus(double first_operand, double second_operand);
static double CalcMul(double first_operand, double second_operand);
static double CalcDiv(double first_operand, double second_operand);
static double CalcPow(double first_operand, double second_operand);


static priority_t GetPriority(char operator)
{
	priority_t priority = ('-' == operator || '-' == operator) ? PLUS_MINUS  : 
			      ('*' == operator || '/' == operator) ? MUL_DIV     :
			      ('^' == operator) 		   ? POW         :
			      (')' == operator) 		   ? PARENTHESIS : 0;
	
	return priority;
}

static void OpHandler(char* input, stack_t* op_stack, stack_t* num_stack)
{
	char new_op = *input;
	char cur_op = 0;
	priority_t new_op_priority = 0;
	priority_t cur_op_priority = 0;
	double priority_result = 0;
	
	if (!StackIsEmpty(op_stack))
	{
		cur_op = *(char*)StackPeek(op_stack);
	}
	new_op_priority = GetPriority(new_op);
	cur_op_priority = GetPriority(cur_op);
	if (PARENTHESIS == new_op_priority)
	{
		while ('(' != *(char*)StackPeek(op_stack))
		{
			priority_result = CalcHandler(num_stack, op_stack);
			StackPush(num_stack, &priority_result);
		}
		StackPop(op_stack);
	}
	else if (cur_op_priority > new_op_priority)
	{
		priority_result = CalcHandler(num_stack, op_stack);
		StackPush(num_stack, &priority_result);
	}
	if (')' != new_op)
	{
		StackPush(op_stack, &new_op);
	}
}

static void NumHandler(double num, stack_t* num_stack)
{
	StackPush(num_stack, &num);
}

static double CalcHandler(stack_t* num_stack, stack_t* op_stack)
{
	double first_operand = 0;
	double second_operand = 0;
	double result = 0;
	char operator = 0;
	
	second_operand = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	first_operand = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	
	operator = *(char*)StackPeek(op_stack);
	StackPop(op_stack);
	
	switch (operator)
	{
		case '-' :
			result = CalcMinus(first_operand, second_operand);
			break;
			
		case '+' :
			result = CalcPlus(first_operand, second_operand);
			break;
			
		case '*' :
			result = CalcMul(first_operand, second_operand);
			break;
			
		case '/' :
			result = CalcDiv(first_operand, second_operand);
			break;
			
		case '^' :
			result = CalcPow(first_operand, second_operand);
			break;
	}
	
	return result;
}

static double CalcMinus(double first_operand, double second_operand)
{
	return first_operand - second_operand;
}

static double CalcPlus(double first_operand, double second_operand)
{
	return first_operand + second_operand;
}

static double CalcMul(double first_operand, double second_operand)
{
	return first_operand * second_operand;
}

static double CalcDiv(double first_operand, double second_operand)
{
	return first_operand / second_operand;
}

static double CalcPow(double first_operand, double second_operand)
{
	return pow(first_operand , second_operand);
}

double Calculate(const char* expression)
{
	state_t state = WAIT_FOR_NUM;
	char* input = (char*)expression;
	int capacity = strlen(expression);
	int i = 0;
	int is_digit = 0;
	int is_op = 0;
	int is_terminator = 0;
	char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char ops[7] = {'-','+','*','/','^', '(', ')'};
	char terminators[3] = {'\n', '\0', '='};
	double next_num = 0;
	double result = 0;
	stack_t* num_stack = StackCreate(capacity, sizeof(double));
	stack_t* op_stack = StackCreate(capacity, sizeof(char));
	if (NULL == num_stack || NULL == op_stack)
	{
		free(num_stack);
		num_stack = NULL;
		free(op_stack);
		op_stack = NULL;
		return 0;
	}
	while (WRONG_INPUT != state && GET_RESULT != state)
	{
		is_digit = 0;
		is_op = 0;
		is_terminator = 0;
		
		switch (state)
		{
			case WAIT_FOR_NUM:
				for (i = 0; i < 10 && !is_digit; ++i)
				{
					is_digit = (*input == digits[i]);
				}
				
				if (is_digit)
				{
					next_num = strtod(input, &input);
					NumHandler(next_num, num_stack);
					state = WAIT_FOR_OP;
				}
				else if ('-' == *input)
				{
					NumHandler(-1, num_stack);
					OpHandler("*", op_stack, num_stack);
					++input;
				}
				else if ('(' == *input)
				{
					
				}
				else if (')' == *input)
				{
					
				}
				else if (' ' == *input || '+' == *input)
				{
					++input;
				}
				else
				{
					state = WRONG_INPUT;
					printf("syntax error!\n");
				}
				
				break;
			
			case WAIT_FOR_OP:
				for (i = 0; i < 7 && !is_op; ++i)
				{
					is_op = (*input == ops[i]);
				}
				for (i = 0; i < 10 && !is_digit; ++i)
				{
					is_digit = (*input == digits[i]);
				}
				for (i = 0; i < 3 && !is_terminator; ++i)
				{
					is_terminator = (*input == terminators[i]);
				}
				if (is_digit)
				{
					state = WRONG_INPUT;
					printf("syntax error!\n");
				}
				else if (is_op)
				{
					OpHandler(input, op_stack, num_stack);
					++input;
					state = WAIT_FOR_NUM;
				}
				else if (is_terminator)
				{
					state = GET_RESULT;
					while (!StackIsEmpty(op_stack))
					{
						result = CalcHandler(num_stack, op_stack);
						StackPush(num_stack, &result);
					}
				}
				
				break;
			
			default:
				break;
		}
	}
	return result;
}

