
#ifndef __WS6_FILES_H__
#define __WS6_FILES_H__
#include <stddef.h>

struct print_me
{
	int num;
	void (*print_ptr)(int);
};


typedef enum Logger_status
{
	SUCCESS = 0, 
	FAIL_OPEN_FILE,
	FAIL_WRITE_FILE,
	FAIL_READ_FILE,
	FAIL_CREATE_FILE,
	FAIL_ALLOCATING_MEMORY,
	FAIL_REMOVE_FILE,
	FAIL_GETTING_USER_INPUT,
	EXIT
} logger_status_t;


/* function definitions */
void PrintTheInt(void);

/*const char* file_name, const char* file_path* into logger*/

logger_status_t Logger(const char* file_name);



/*
 * Description: logging the input from stdin to a txt file 
 *              recives a pointer to string that indicates the file name 
 *              if the pointer is NULL , will create a new default <date_time>logger_file.txt in local directory 
 *              have the operations of :
 *              "-count"        - displays the count of number rows in file . (not creating a file)
*/
 
 #endif
