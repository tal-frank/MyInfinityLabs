
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <stdlib.h> /* system */

#define UNUSED(x) (void)(x)

#define INIT (0)
#define	ACCEPTED (1)
#define UNACCEPTED (2)
#define UNACCEPTED_TERMINAL (3)

/*-------------------------------------------------------------------------------------------------*/
/********************************** STATIC FUNCTIONS DECLARATIONS **********************************/
/*-------------------------------------------------------------------------------------------------*/

static int INIT_state(char input);
static int ACCEPTED_state(char input);
static int UNACCEPTED_state(char input);
static int UNACCEPTED_TERMINAL_state(char input);

/*------------------------------------------------------------------------------------*/
/********************************** STATIC VARIABLES **********************************/
/*------------------------------------------------------------------------------------*/

static int (*state_lut[4])(char input) = {INIT_state, ACCEPTED_state, UNACCEPTED_state, UNACCEPTED_TERMINAL_state};
static int state = INIT;

/*---------------------------------------------------------------------------*/
/********************************** LUT FSM **********************************/
/*---------------------------------------------------------------------------*/

void StateMachineLUT(char input)
{
	state = state_lut[state](input);
}

/*----------------------------------------------------------------------------------*/
/********************************** LUT FSM STATES **********************************/
/*----------------------------------------------------------------------------------*/

static int INIT_state(char input)
{
	state = ('0' == input) ? UNACCEPTED : UNACCEPTED_TERMINAL;
	
	return state;
}

static int ACCEPTED_state(char input)
{
	state = ('0' == input) ? ACCEPTED : UNACCEPTED;
		
	return state;
}

static int UNACCEPTED_state(char input)
{
	state = ('0' == input) ? ACCEPTED : UNACCEPTED;
		
	return state;
}

static int UNACCEPTED_TERMINAL_state(char input)
{
	UNUSED(input);
	
	state = UNACCEPTED_TERMINAL;
		
	return state;
}

/*----------------------------------------------------------------------------------*/
/********************************** SWITCH CASE FSM STATES **********************************/
/*----------------------------------------------------------------------------------*/

void StateMachineSwitchCase(char input)
{	 	 
	 switch (state)
	 {
	 	case INIT:
	 		state = ('0' == input) ? UNACCEPTED : UNACCEPTED_TERMINAL;
	 		break;
	 		
	 	case ACCEPTED:
	 		state = ('0' == input) ? ACCEPTED : UNACCEPTED;
	 		break;
	 		
	 	case UNACCEPTED:
	 		state = ('0' == input) ? ACCEPTED : UNACCEPTED;
	 		break;
	 		
		default:
			break;			
	 }
}

/*--------------------------------------------------------------------------------------*/
/********************************** IF ELSE FSM STATES **********************************/
/*--------------------------------------------------------------------------------------*/

void StateMachineIfElse(char input)
{
	if (INIT == state)
	{
		state = ('0' == input) ? UNACCEPTED : UNACCEPTED_TERMINAL;
	}
	
	else if (ACCEPTED == state)
	{
		state = ('0' == input) ? ACCEPTED : UNACCEPTED;
	}
	
	else if (UNACCEPTED == state)
	{
		state = ('0' == input) ? ACCEPTED : UNACCEPTED;
	}
	
	else if (UNACCEPTED_TERMINAL == state)
	{
		state = UNACCEPTED_TERMINAL;
	}
}

/*------------------------------------------------------------------------*/
/********************************** MAIN **********************************/
/*------------------------------------------------------------------------*/

int main()
{
	char input = '0';
	printf("enter a digit:\n");
	system ("stty -icanon -echo");
	while ('0' == input || '1' == input)
	{
		input = getchar();
/*
		StateMachineSwitchCase(input);
		StateMachineLUT(input);
*/
		StateMachineIfElse(input);
		
		if (ACCEPTED == state)
		{
			printf("ACCEPTED\n");
		}
		else if (UNACCEPTED == state)
		{
			printf("UNECCEPTED:\n");
		}
		else if (UNACCEPTED_TERMINAL == state)
		{
			printf("UNECCEPTED_TERMINAL:\n");
		}
	}
	system ("stty icanon echo");
	
	
	return 0;
}

