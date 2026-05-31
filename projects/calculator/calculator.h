#ifndef __CALCULATOR_H__ 
#define __CALCULATOR_H__

typedef enum status 
{
    SUCCESS,
    SYNTAX_ERROR,
    MATH_ERROR,
    MEMORY_ERROR
}status_t;

/****************************************************************************
* 		
* Description: Gets a mathematical expression string and calcultes its value. The answer will be
*	       inserted into the "result" argument. Rules for the expression argument are written
	       in the argument section below. The function return a status after the calculation.
*		        
*   Arguments: expression - A mathematical expression string to calculate.
*			    Any violation of the followed rule will return 0 and SYNTAX_ERROR status.
*			    Rules for the string:
*			    1. string must start with a number/open parenthesis/'-'/'+'.
*			       A series of minus/plus signs are valid as long as it folowed by number.
*			    2. A series of minus/plus signs are valid in the middle of the code 
*			       as long as it does not have an operator before it and folowed by number.
*			    3. Parenthesis must be resolved, any open parenthesis that does not answered
*			       by close parenthesis is invalid. only '(', ')' parenthesis are allowed.
*			    4. Equal sign ("=") is allowed at the end of the string. Equal sign can be 
*			       folowed only by spaces end other terminators ('\n', '\0').
*			    5. Spaces are ignored accept for spaces between two numbers or an extra 
			       space after unary "-"/"+" which are invalid.
*			    
*	       result     - A variable to insert the result.
*		
*      Return: The function returns one of the possible statuses above after the calculation.
*		
*  Complexity: Time: O(n) Space: O(n)
*		
*		
******************************************************************************/

status_t Calculate(const char* expression, double* result);

#endif /** End of __CALCULATOR_H__ */
