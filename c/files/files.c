/**********************
 * ws6_files
 * Author: Tal Frank
 * Reviewer: Ori Joseph
 * Last update: 14/03/2026
**********************/

#include <stdlib.h>
#include <stdio.h>

#include "files.h"
#include "../strings/strings.c"

#define HANDLERS_NUM 5
#define DEFAULT_FILE_NAME "exercises/Logger.txt"
#define UNUSED(X) ((void)X)


logger_status_t Count(const char* file_name, char* cmd);

logger_status_t Remove(const char* file_name, char* cmd);

logger_status_t Exit(const char* file_name, char* cmd);

logger_status_t Append(const char* file_name, char* cmd);


/******************************* HANDLER STRUCT *************************************/

struct logger_handler
{
	char* cmd;
	int (*Cmp)(const char* cmd_line, const char* user_input, size_t num_ch_to_check);
	logger_status_t (*Activate)(const char* file_name, char* user_input);
};

/******************************* LINE COUNTER COUNT FUNCTION *************************************/

static int CountLines(FILE* file)
{
	int ch = 0;
	int cnt = 0;
	while (EOF != ch)
	{
		ch = fgetc(file);
		if ('\n' == ch)
		{
			++cnt;
		}
	}
	return cnt;	
}


/******************************* REMOVE TMP FUNCTION *************************************/

static logger_status_t RemoveTmp(char* file_name)
{
	if (0 != remove(file_name))
	{
		printf("Error : file can not be removed.\n");
		return FAIL_REMOVE_FILE;
	}
	return SUCCESS;
}


/******************************* FILE COPY FUNCTION *************************************/

static logger_status_t CopyFile(FILE* dest_file, FILE* src_file, char* cmd_line)
{
	logger_status_t status = SUCCESS;
	while (NULL != fgets(cmd_line, BUFSIZ, src_file))
	{
		if (EOF == fputs(cmd_line, dest_file))
		{
			printf("Error : can not write to this file.\n");
			status = RemoveTmp("tmp_file.txt");
			return status == FAIL_REMOVE_FILE ? FAIL_REMOVE_FILE : FAIL_WRITE_FILE;
		}
	}
	return status;
}


/******************************* COUNT FUNCTION *************************************/

logger_status_t Count(const char* file_name, char* cmd)
{
	int cnt = 0;
	FILE* cmd_file = fopen(file_name, "a+");
	UNUSED(cmd);
	
	cnt = CountLines(cmd_file);
	
	fclose(cmd_file);
	printf("The number of commands is : %d\n" , cnt);
	return SUCCESS;
}


/******************************* REMOVE FUNCTION *************************************/

logger_status_t Remove(const char* file_name, char* cmd)
{
	UNUSED(cmd);
	if (0 == remove(file_name))
	{
		printf("file %s removed.\n", file_name);
	}	
	else
	{
		printf("Error : file can not be removed.\n");
		return FAIL_REMOVE_FILE;
	}
	
	return SUCCESS;
}



/******************************* APPEND FUNCTION *************************************/

logger_status_t Append(const char* file_name, char* cmd)
{
	char* enter = "\n";
	char cmd_line[BUFSIZ] = {0};
	logger_status_t status = SUCCESS;
	FILE* cmd_file = fopen(file_name, "r+");
	FILE* tmp_file;
	
	if (NULL == cmd_file)
	{
		printf("Error : can not open file.\n");
		return FAIL_CREATE_FILE;
	}
	
	cmd = StrCat(cmd, enter);
	++cmd;
	
	tmp_file = fopen("tmp_file.txt" , "w");
	status = CopyFile(tmp_file, cmd_file, cmd_line);
	if (SUCCESS != status)
	{
		return status;
	}

	fclose(tmp_file);
	tmp_file = fopen("tmp_file.txt" , "r");
	fseek(cmd_file, 0, SEEK_SET);	
		
	if (EOF == fputs(cmd, cmd_file))
	{
		printf("Error : can not write to this file.\n");
		status = RemoveTmp("tmp_file.txt");
		return status == FAIL_REMOVE_FILE ? FAIL_REMOVE_FILE : FAIL_WRITE_FILE;
	}
	
	status = CopyFile(cmd_file, tmp_file, cmd_line);
	if (SUCCESS != status)
	{
		return status;
	}
	
	fclose(tmp_file);
	status = RemoveTmp("tmp_file.txt");	
	fclose(cmd_file);
	return status;
}


/******************************* EXIT FUNCTION *************************************/

logger_status_t Exit(const char* file_name, char* cmd)
{			
	UNUSED(cmd);
	UNUSED(file_name);															
	printf("EXIT LOGGER\n");
	return EXIT;	
}


/******************************* DEFAULT FUNCTION *************************************/

logger_status_t Default(const char* file_name, char* cmd)
{
	char* enter = "\n";
	FILE* cmd_file = fopen(file_name, "a+");
	
	if (NULL == cmd_file)
	{
		printf("Error : can not create file.\n");
		return FAIL_CREATE_FILE;
	}

	cmd = StrCat(cmd, enter);

	if (EOF == fputs(cmd, cmd_file))
	{
		printf("Error : can not write to this file.\n");
		return FAIL_WRITE_FILE;
	}
	fclose(cmd_file);
	return SUCCESS;
}


/******************************* INIT_HANDLER FUNCTION *************************************/

void InitHandler(struct logger_handler choose_handler[])
{
	choose_handler[0].cmd = "-count";
	choose_handler[0].Cmp = &StrNCmp;
	choose_handler[0].Activate = &Count;
	
	choose_handler[1].cmd = "-remove";
	choose_handler[1].Cmp = &StrNCmp;
	choose_handler[1].Activate = &Remove;
	
	choose_handler[2].cmd = "<";
	choose_handler[2].Cmp = &StrNCmp;
	choose_handler[2].Activate = &Append;
	
	choose_handler[3].cmd = "-exit";
	choose_handler[3].Cmp = &StrNCmp;
	choose_handler[3].Activate = &Exit;
	
	choose_handler[4].Cmp = &StrNCmp;
	choose_handler[4].Activate = &Default;
}


/******************************* LOGGER FUNCTION *************************************/

logger_status_t Logger(const char* file_name)
{
	int i = 0;
	int is_handler_found = 0;
	static char user_input[BUFSIZ] = {0};	
	logger_status_t prog_state = SUCCESS;
	struct logger_handler choose_handler[HANDLERS_NUM] = {0};

	if (NULL == file_name)
	{
		file_name = DEFAULT_FILE_NAME;
	}

	InitHandler(choose_handler);
	
	while (EXIT != prog_state)
	{
		scanf ("%[^\n]%*c", user_input);

		for (i = 0; i < HANDLERS_NUM - 1; ++i)
		{
			size_t cmp_length = StrLen(choose_handler[i].cmd);
			if(0 == choose_handler[i].Cmp(choose_handler[i].cmd, 
							user_input, cmp_length))
			{	
				prog_state = choose_handler[i].Activate(file_name, user_input); 
				is_handler_found = 1;
			}
		}
		if (!is_handler_found)
		{
			prog_state = choose_handler[HANDLERS_NUM - 1].Activate(file_name, user_input);
		}
	}
	return 0;
}

/******************************* PRINT FUNCTION *************************************/

void Print(int num)
{
	printf("%d\n", num);
}


/******************************* PRINT_THE_INT FUNCTION *************************************/

void PrintTheInt(void)
{
	int i;
	struct print_me arr[10];
	for (i = 0; i < 10; ++i)
	{
		arr[i].num = i;
		arr[i].print_ptr = &Print;
	}
	for (i = 0; i < 10; ++i)
	{
		arr[i].print_ptr(arr[i].num);
	}
}


