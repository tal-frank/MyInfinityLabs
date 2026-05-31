#include <string.h> /* strlen */
#include <stdlib.h>  /* strtod */ 
#include <math.h> /* pow */
#include <stddef.h> /* size_t */

#include "calculator.h"
#include "stack.h"

#define UNUSED(x) (void)(x)

#define TRUE (1)
#define FALSE (0)

/*---------------------------------------------------------------*/
/***************************** ENUMS *****************************/
/*---------------------------------------------------------------*/

typedef enum
{
	ERROR = 0,
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	GET_RESULT
}state_t;

typedef enum priority
{
	NO_PRIORITY = 0,
	PLUS,	
	MINUS,
	MUL_DIV,
	POW
}priority_t;

/*---------------------------------------------------------------------------------------*/
/***************************** STATIC FUNCTIONS DECLARATIONS *****************************/
/*---------------------------------------------------------------------------------------*/

static void OpHandler(char** input);
static void NumHandler(char** input);
static void CalcHandler(char** input);
static void OpenParenthesisHandler(char** input);
static void CloseParenthesisHandler(char** input);
static void TerminatorHandler(char** input);
static void ErrorHandler(char** input);
static void UnaryMinusHandler(char** input);
static void UnaryPlusHandler(char** input);
static void SpaceHandler(char** input);

static void InitializeHandlersLut(void);
static void InitializeASCIILut(void);
static void InitializePriorityLut(void);
static double CalcMinus(double first_operand, double second_operand);
static double CalcPlus(double first_operand, double second_operand);
static double CalcMul(double first_operand, double second_operand);
static double CalcDiv(double first_operand, double second_operand);
static double CalcPow(double first_operand, double second_operand);
static void DoNotInitialize(void );
static void GetPrevPriority(char* prev_operator, priority_t* prev_op_priority);
static void DoNotGetPriority(char* prev_operator, priority_t* prev_op_priority);
static void CalcParenthesisWithoutPromote(char** input);
static void ParenthesisPromotion(char** input);
static void FinishCalculate(char** input);
static void KeepCalculate(char** input);
static void PopParenthesisStack(char** input);
static void IsBalancedParenthesis(char** input);

static void OpParser(char** input);
static void NumParser(char** input);
static void OpenParenthesisParser(char** input);
static void CloseParenthesisParser(char** input);
static void TerminatorParser(char** input);
static void ErrorParser(char** input);
static void UnaryMinusParser(char** input);
static void UnaryPlusParser(char** input);
static void InitializeParserLut(void);
static void SpaceParser(char** input);
static void InitializeSpaceLut(void);
static void NoSpaceFound(char** input);

/*--------------------------------------------------------------------------*/
/***************************** STATIC VARIABLES *****************************/
/*--------------------------------------------------------------------------*/

static state_t state = WAIT_FOR_NUM;
static status_t status = SUCCESS;

static stack_t* num_stack = NULL;
static stack_t* op_stack = NULL;
static stack_t* parenthesis_stack = NULL;

static char ascii_lut[128] = {0};
static char priority_lut[128] = {0};
static char space_lut[128] = {0};

static void (*handlers_lut[4][128])(char** input) = {0};
static void (*parser_lut[4][128])(char** input) = {0};

static void (*calculate_all_lut[])(char** input) = {KeepCalculate, FinishCalculate};
static void (*get_prev_priority_lut[2])(char* prev_operator, priority_t* prev_op_priority) =
							{GetPrevPriority, DoNotGetPriority};

static void (*CheckSpaceAfterUnary[2])(char** input) = {NoSpaceFound, ErrorParser,};

static void (*pop_parenthesis_lut[2])(char** input) = {PopParenthesisStack, ErrorParser};
static void (*is_balanced_parenthesis_lut[4][2])(char**) = {{ErrorParser, ErrorParser},
							    {ErrorParser, IsBalancedParenthesis},
							    {ErrorParser, IsBalancedParenthesis},
							    {ErrorParser, IsBalancedParenthesis}};

static void (*initialized_parser_lut[2])(void) = {InitializeParserLut, DoNotInitialize};
static void (*initialized_handlers_lut[2])(void) = {InitializeHandlersLut, DoNotInitialize};
static void (*initialize_ascii_lut[2])(void) = {InitializeASCIILut, DoNotInitialize};
static void (*initialize_priority_lut[2])(void) = {InitializePriorityLut, DoNotInitialize};
static void (*initialize_Space_lut[2])(void) = {InitializeSpaceLut, DoNotInitialize};

static void (*parenthsis_while_loop_lut[6])(char** input) = {CalcParenthesisWithoutPromote,
							     CalcParenthesisWithoutPromote,
							     CalcParenthesisWithoutPromote,
							     CalcParenthesisWithoutPromote,
							     CalcParenthesisWithoutPromote,
							     ParenthesisPromotion};
						   
static double (*CalcOperation[5])(double first_operand, double second_operand) = {CalcMinus, 
										  CalcPlus, 
										  CalcMul, 
										  CalcDiv, 
										  CalcPow};


static void InitializeSpaceLut(void)
{
	space_lut[(int)' '] = TRUE;
}

static void InitializeASCIILut(void)
{
	size_t i = 0;
	int ops_arr[] = {'-', '+', '*', '/', '^', '('};
	
	for (i = 0; i < 6; ++i)
	{
		ascii_lut[ops_arr[i]] = i;
	}
}

static void InitializePriorityLut(void)
{
	size_t i = 0;
	for (i = 0; i < 128; ++i)
	{
		priority_lut[i] = NO_PRIORITY;
	}

	priority_lut['+'] = PLUS;
	priority_lut['-'] = MINUS;
	priority_lut['/'] = MUL_DIV;
	priority_lut['*'] = MUL_DIV;
	priority_lut['^'] = POW;
}

static void InitializeHandlersLut(void)
{
	size_t i = 0;
	size_t j = 0;
	int ops_arr[] = {'-', '+', '*', '/', '^'};
	int terminators_arr[] = {'=', '\n', '\0'};
	
	for(i = 1; i < 128; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			handlers_lut[j][i] = ErrorHandler;
		}
	}
	
	for(i = '0'; i <= '9'; ++i)
	{
		handlers_lut[WAIT_FOR_NUM][i] = NumHandler;
	}
	
	for (i = 0; i < 5; ++i)
	{
		handlers_lut[WAIT_FOR_OP][ops_arr[i]] = OpHandler;
	}
		
	for (i = 0; i < 3; ++i)
	{
		handlers_lut[WAIT_FOR_OP][terminators_arr[i]] = TerminatorHandler;
	}
	
	handlers_lut[WAIT_FOR_NUM]['-'] = UnaryMinusHandler;
	handlers_lut[WAIT_FOR_NUM]['+'] = UnaryPlusHandler;
	handlers_lut[WAIT_FOR_NUM]['('] = OpenParenthesisHandler;
	handlers_lut[WAIT_FOR_OP][')'] = CloseParenthesisHandler;
	handlers_lut[WAIT_FOR_NUM][' '] = SpaceHandler;
	handlers_lut[WAIT_FOR_OP][' '] = SpaceHandler;
}

static void InitializeParserLut(void)
{
	size_t i = 0;
	size_t j = 0;
	int ops_arr[] = {'-', '+', '*', '/', '^'};
	int terminators_arr[] = {'=', '\n'};
	
	for(i = 1; i < 128; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			parser_lut[j][i] = ErrorParser;
		}
	}
	
	for(i = '0'; i <= '9'; ++i)
	{
		parser_lut[WAIT_FOR_NUM][i] = NumParser;
	}
	
	for (i = 0; i < 5; ++i)
	{
		parser_lut[WAIT_FOR_OP][ops_arr[i]] = OpParser;
	}
		
	for (i = 0; i < 2; ++i)
	{
		parser_lut[WAIT_FOR_OP][terminators_arr[i]] = TerminatorParser;
	}
	
	parser_lut[WAIT_FOR_NUM]['-'] = UnaryMinusParser;
	parser_lut[WAIT_FOR_NUM]['+'] = UnaryPlusParser;
	parser_lut[WAIT_FOR_NUM]['('] = OpenParenthesisParser;
	parser_lut[WAIT_FOR_OP][')'] = CloseParenthesisParser;
	parser_lut[WAIT_FOR_NUM][' '] = SpaceParser;
	parser_lut[WAIT_FOR_OP][' '] = SpaceParser;
	
}

static void DoNotInitialize(void)
{
	return;
}

static void NoSpaceFound(char** input)
{
	UNUSED(input);
	return;
}

/*--------------------------------------------------------------------------*/
/***************************** STATIC FUNCTIONS *****************************/
/*--------------------------------------------------------------------------*/

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
	if (0 == second_operand)
	{
		char** input = NULL;
		status = MATH_ERROR;
		ErrorHandler(input);
		return 0;
	}
	
	return first_operand / second_operand;
}

static double CalcPow(double first_operand, double second_operand)
{
	return pow(first_operand , second_operand);
}

static void GetPrevPriority(char* prev_operator, priority_t* prev_op_priority)
{
	*prev_operator = *(char*)StackPeek(op_stack);
	*prev_op_priority = priority_lut[(int)*prev_operator];
}

static void DoNotGetPriority(char* prev_operator, priority_t* prev_op_priority)
{
	UNUSED(prev_operator);
	UNUSED(prev_op_priority);
	return;
}

static void CalcParenthesisWithoutPromote(char** input)
{
	CalcHandler(input);
}

static void ParenthesisPromotion(char** input)
{
	StackPop(op_stack);
	++*input;
}

static void KeepCalculate(char** input)
{
	CalcHandler(input);
}

static void FinishCalculate(char** input)
{
	UNUSED(input);
	state = GET_RESULT;
}

static void PopParenthesisStack(char** input)
{
	UNUSED(input);
	StackPop(parenthesis_stack);
}

static void IsBalancedParenthesis(char** input)
{
	UNUSED(input);
	status = SUCCESS;
	state = WAIT_FOR_NUM;
}

/*----------------------------------------------------------------*/
/***************************** PARSER *****************************/
/*----------------------------------------------------------------*/

static void NumParser(char** input)
{
	char* input_without_first_num;
	strtod(*input, &input_without_first_num);
	*input = input_without_first_num;
	state = WAIT_FOR_OP;
}

static void UnaryMinusParser(char** input)
{
	state = WAIT_FOR_NUM;	
	++*input;
	CheckSpaceAfterUnary[(int)space_lut[(int)**input]](input);
}

static void UnaryPlusParser(char** input)
{
	state = WAIT_FOR_NUM;
	++*input;
	CheckSpaceAfterUnary[(int)space_lut[(int)**input]](input);
}

static void OpParser(char** input)
{
	state = WAIT_FOR_NUM;
	++*input;
}

static void OpenParenthesisParser(char** input)
{
	char parenthesis = **input;
	state = WAIT_FOR_NUM;
	StackPush(parenthesis_stack, &parenthesis);
	++*input;
}

static void CloseParenthesisParser(char** input)
{
	state = WAIT_FOR_OP;
	pop_parenthesis_lut[StackIsEmpty(parenthesis_stack)](input);
	++*input;
}

static void TerminatorParser(char** input)
{
	state = WAIT_FOR_OP;
	++*input;
}

static void SpaceParser(char** input)
{
	++*input;
}

static void ErrorParser(char** input)
{
	UNUSED(input);
	status = SYNTAX_ERROR;
	state = ERROR;
} 

/*------------------------------------------------------------------*/
/***************************** HANDLERS *****************************/
/*------------------------------------------------------------------*/

static void NumHandler(char** input)
{
	char* input_without_first_num;
	double num = strtod(*input, &input_without_first_num);
	
	*input = input_without_first_num;
	StackPush(num_stack, &num);
	state = WAIT_FOR_OP;
}

static void UnaryMinusHandler(char** input)
{
	double num = -1;
	char mul = '*';
	
	StackPush(num_stack, &num);
	StackPush(op_stack, &mul);

	++*input;
	
	state = WAIT_FOR_NUM;
}

static void UnaryPlusHandler(char** input)
{
	++*input;
}

static void OpHandler(char** input)
{
	char operator = **input;
	char prev_operator = POW;
	
	priority_t curr_op_priority = priority_lut[(int)operator];
	priority_t prev_op_priority = NO_PRIORITY;
	get_prev_priority_lut[StackIsEmpty(op_stack)](&prev_operator, &prev_op_priority);
	
	while (curr_op_priority <= prev_op_priority && !StackIsEmpty(op_stack))
	{
		CalcHandler(input);
		get_prev_priority_lut[StackIsEmpty(op_stack)](&prev_operator, &prev_op_priority);
	}
	
	StackPush(op_stack, &operator);
	++*input;
	state = WAIT_FOR_NUM;
}

static void CalcHandler(char** input)
{
	double first_operand = 0;
	double second_operand = 0;
	double mid_result = 0;
	char operator = 0;
	
	UNUSED(input);
	
	second_operand = *(double*)StackPeek(num_stack);
	StackPop(num_stack);

	first_operand = *(double*)StackPeek(num_stack);
	StackPop(num_stack);
	
	operator = *(char*)StackPeek(op_stack);
	StackPop(op_stack);
	
	mid_result = CalcOperation[(int)ascii_lut[(int)operator]](first_operand, second_operand);
	StackPush(num_stack, &mid_result);	
}

static void OpenParenthesisHandler(char** input)
{
	char open_parenthesis = **input;
	StackPush(op_stack, &open_parenthesis);
	++*input;
}

static void CloseParenthesisHandler(char** input)
{
	char prev_op = *(char*)StackPeek(op_stack);
	parenthsis_while_loop_lut[(int)ascii_lut[(int)prev_op]](input);
}

static void SpaceHandler(char** input)
{
	++*input;
}

static void TerminatorHandler(char** input)
{
	calculate_all_lut[StackIsEmpty(op_stack)](input);
}

static void ErrorHandler(char** input)
{	
	double error_result = 0;

	UNUSED(input);

	state = ERROR;
	
	StackPush(num_stack, &error_result);
}

/*--------------------------------------------------------------------*/
/***************************** CALCULATOR *****************************/
/*--------------------------------------------------------------------*/

status_t Calculate(const char* expression, double* result)
{
	char* input = (char*)expression;
	char* parser_input = (char*)expression;
	int capacity = strlen(expression);
	static int is_initialized = 0;

	state = WAIT_FOR_NUM;
	status = SUCCESS;
	num_stack = StackCreate(capacity, sizeof(double));
	op_stack = StackCreate(capacity, sizeof(char));
	parenthesis_stack = StackCreate(capacity, sizeof(char));
	
	if (NULL == num_stack || NULL == op_stack || NULL == parenthesis_stack)
	{
		StackDestroy(parenthesis_stack);
		parenthesis_stack = NULL;
		StackDestroy(num_stack);
		num_stack = NULL;
		StackDestroy(op_stack);
		op_stack = NULL;
		return 0;
	}
	
	initialized_parser_lut[is_initialized]();
	initialized_handlers_lut[is_initialized]();
	initialize_ascii_lut[is_initialized]();
	initialize_priority_lut[is_initialized]();
	initialize_Space_lut[is_initialized]();
	
	is_initialized = 1;
	while ('\0' != *parser_input && SYNTAX_ERROR != status)
	{
		parser_lut[state][(int)*parser_input](&parser_input);
	}
	
	is_balanced_parenthesis_lut[state][StackIsEmpty(parenthesis_stack)](&parser_input);
	
	while (ERROR != state && GET_RESULT != state && SUCCESS == status)
	{
		handlers_lut[state][(int)*input](&input);
	}
	
	*result = *(double*)StackPeek(num_stack);

	StackDestroy(parenthesis_stack);
	parenthesis_stack = NULL;

	StackDestroy(num_stack);
	num_stack = NULL;

	StackDestroy(op_stack);
	op_stack = NULL;

	return status;
}

