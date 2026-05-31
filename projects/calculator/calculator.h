#ifndef __CALCULATOR_H__ 
#define __CALCULATOR_H__

typedef enum status
{
    SUCCESS,
    SYNTAX_ERROR,
    MATH_ERROR,
    MEMORY_ERROR
}status_t;

status_t Calculate(const char* expression, double* result);

#endif /** End of __CALCULATOR_H__ */
