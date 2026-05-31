
#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

int main()
{
	double result = 0;
	int status = 0;
	
	status = Calculate("-3-(2.5*5 + 5*2)+5\n", &result);
	printf("result : -3-(2.5*5 + 5*2)+5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("=\n", &result);
	printf("result : = = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("45+3.5\n", &result);
	printf("result : 45+3.5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("(35-6\n", &result);
	printf("result : (35-6 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("7*5\n", &result);
	printf("result : 7*5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("2+4*5\n", &result);
	printf("result : 2+4*5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	

	status = Calculate("4*5+2\n", &result);
	printf("result : 4*5+2 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("4*5/2\n", &result);
	printf("result : 4*5/2 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("4/-5*2\n", &result);
	printf("result : 4/-5*2 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("4/- 5*2\n", &result);
	printf("result : 4/- 5*2 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("1+2+3\n", &result);
	printf("result : 1+2+3 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("1-2-3\n", &result);
	printf("result : 1-2-3 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+4*5/-2\n", &result);
	printf("result : -+-+4*5/-2 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+4*5/-2 3+5\n", &result);
	printf("result : -+-+4*5/-2 3+5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);
	
	status = Calculate("-+-+4*5/-2*3+5\n", &result);
	printf("result : -+-+4*5/-2*3+5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+- +4*5/-2*3+5\n", &result);
	printf("result : -+- +4*5/-2*3+5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+(4*5/-2)*(3+5\n", &result);
	printf("result : -+-+(4*5/-2)*(3+5 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+(4*5/-2)*(3+5)+\n", &result);
	printf("result : -+-+(4*5/-2)*(3+5)+ = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+(4*5/-2)*3+5)+3\n", &result);
	printf("result : -+-+(4*5/-2)*3+5)+3 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+(4*5/-2)*(*3+5)\n", &result);
	printf("result : -+-+(4*5/-2)*(*3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+(4*5/-2^)*(3+5)\n", &result);
	printf("result : -+-+(4*5/-2^)*(3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-+-+(4*5/-2)*(-3+5)\n", &result);
	printf("result : -+-+(4*5/-2)*(-3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+(4*5/-2)*(-*3+5)\n", &result);
	printf("result : -+-+(4*5/-2)*(-*3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+((4*5/-2))*(-3+5)\n", &result);
	printf("result : -+-+((4*5/-2))*(-3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+(4*5/-2)**(3+5)\n", &result);
	printf("result : -+-+(4*5/-2)**(3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-+-+(4*5/-2)*(3+5)\n", &result);
	printf("result : -+-+(4*5/-2)*(3+5) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("-2^3+(5^2)^3\n", &result);
	printf("result : -2^3+(5^2)^3 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("-2^3+5^2^3\n", &result);
	printf("result : -2^3+5^2^3 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("5+6/0+7*6\n", &result);
	printf("result : 5+6/0+7*6 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("5+6/(7-7)*6\n", &result);
	printf("result : 5+6/(7-7)*6 = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	       
	status = Calculate("5+6 =   \n", &result);
	printf("result : 5+6 =   (spaces with enter) = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);	
	
	status = Calculate("5+6 = 11\n", &result);
	printf("result : 5+6 = 11  = %f\n", result);
	printf(status == 0 ? GREEN "SUCCESS\n" RESET_COLOR    :
	       status == 1 ? RED "SYNTAX ERROR\n" RESET_COLOR :
	       status == 2 ? RED "MATH ERROR\n" RESET_COLOR   : 
	       RED "MEMORY ERROR" RESET_COLOR);
	
	return 0;
}
