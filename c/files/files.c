/**********************
 * ws6_files
 * Author: Tal Frank
 * Reviewer: Name
**********************/

#include <stdlib.h>
#include <stdio.h>
#include "files.h"
#include "../strings/string.c"
#define UNUSED(X) ((void)X)


logger_status_t Count(const char* file_name, char* cmd);

logger_status_t Remove(const char* file_name, char* cmd);

logger_status_t Exit(const char* file_name, char* cmd);

logger_status_t Append(const char* file_name, char* cmd);




/******************************* REMOVE_TMP FUNCTION *************************************/

logger_status_t RemoveTmp(char* file_name)
{
	if (0 != remove(file_name))
	{
		printf("Error : file can not be removed.\n");
		return FAIL_REMOVE_FILE;
	}
	return SUCCESS;
}



/******************************* COUNT FUNCTION *************************************/

logger_status_t Count(const char* file_name, char* cmd)
{
	int ch;
	int cnt;
	FILE* cmd_file = fopen(file_name, "r");
	UNUSED(cmd);
	
	cnt = 0;
	if (NULL == cmd_file)
	{
		printf("%d", cnt);
		return SUCCESS;
	}
	while (EOF != ch)
	{
		ch = fgetc(cmd_file);
		if ('\n' == ch)
		{
			++cnt;
		}
	}
	
	printf("%d\n" , cnt);
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
	char* enter;
	char cmd_line[100];
	logger_status_t status;
	FILE* cmd_file = fopen(file_name, "r+");
	FILE* tmp_file;
	
	enter = "\n";
	
	if (NULL == cmd_file)
	{
		printf("Error : can not open file.\n");
		return FAIL_CREATE_FILE;
	}
	
	cmd = StrCat(cmd, enter);
	++cmd;
	
	tmp_file = fopen("tmp_file.txt" , "w");

	while (NULL != fgets(cmd_line, 100, cmd_file))
	{
		if (EOF == fputs(cmd_line, tmp_file))
		{
			printf("Error : can not write to this file.\n");
			status = RemoveTmp("tmp_file.txt");
			return status == FAIL_REMOVE_FILE ? FAIL_REMOVE_FILE : FAIL_WRITE_FILE;
		}
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
	
	while (NULL != fgets(cmd_line, 100, tmp_file))
	{
		if (EOF == fputs(cmd_line, cmd_file))
		{
			printf("Error : can not write to this file.\n");
			status = RemoveTmp("tmp_file.txt");
			return status == FAIL_REMOVE_FILE ? FAIL_REMOVE_FILE : FAIL_WRITE_FILE;
		}
	}
	
	fclose(tmp_file);
	status = RemoveTmp("tmp_file.txt");	
	fclose(cmd_file);
	return status == FAIL_REMOVE_FILE ? FAIL_REMOVE_FILE : SUCCESS;
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
	char* enter;
	FILE* cmd_file = fopen(file_name, "a+");
	
	enter = "\n";
	
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
	choose_handler[0].activate = &Count;
	
	choose_handler[1].cmd = "-remove";
	choose_handler[1].Cmp = &StrNCmp;
	choose_handler[1].activate = &Remove;
	
	choose_handler[2].cmd = "<";
	choose_handler[2].Cmp = &StrNCmp;
	choose_handler[2].activate = &Append;
	
	choose_handler[3].cmd = "-exit";
	choose_handler[3].Cmp = &StrNCmp;
	choose_handler[3].activate = &Exit;
	
	choose_handler[4].Cmp = &StrNCmp;
	choose_handler[4].activate = &Default;
}


/******************************* LOGGER FUNCTION *************************************/

logger_status_t Logger(const char* file_name)
{
	int i;
	size_t cmp_length;
	char user_input[100];	
	logger_status_t prog_state;
	struct logger_handler choose_handler[5];

	if (NULL == file_name)
	{
		file_name = "Logger.txt";
	}

	InitHandler(choose_handler);
	
	while (EXIT != prog_state)
	{
		scanf ("%[^\n]%*c", user_input);
		for (i = 0; i < 5; ++i)
		{
			cmp_length = StrLen(choose_handler[i].cmd);
			if(0 == choose_handler[i].Cmp(choose_handler[i].cmd, 
							user_input, 
							cmp_length) || 4 == i)
			{	
				prog_state = choose_handler[i].activate(file_name, user_input); 
				break;
			}
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























