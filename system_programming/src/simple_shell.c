/**********************
* simple shell
* Author: Tal Frank
* Reviewer: Or Zellner
* Last update: 05/07/2026
**********************/

#include <stdio.h> /* ptintf */
#include <stdlib.h> /* atoi */
#include <string.h> /* strcmp */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork , execvp */
#include <sys/wait.h> /* wait */
#include <errno.h> /* errno, strerror */


/*------------------------------------------------------*/
/************************* ENUM *************************/
/*------------------------------------------------------*/

enum 
{
    SUCCESS = 0,
    FAILURE
};

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static void SystemShell(void);
static void ForkShell(void);
static void RunCommand(char buffer[]);
static void CleanBuffer(char buffer[]);

/*--------------------------------------------------------------*/
/************************* SIMPLE SHELL *************************/
/*--------------------------------------------------------------*/

void SimpleShell(void)
{
    int running_choice;
    char buffer[BUFSIZ] = {0};
    
    printf("to use 'fork' press 0, to use system press 1\n");
    fgets(buffer, BUFSIZ, stdin);
    
    running_choice = atoi(buffer);
    if (0 == running_choice)
    {
        printf("chose fork\n");
        ForkShell();
    }
    else
    {
        printf("chose system\n");
        SystemShell();
    }
}

/*------------------------------------------------------------------*/
/************************* SYSTEM EXECUTION *************************/
/*------------------------------------------------------------------*/

static void SystemShell(void)
{
    char command[BUFSIZ] = {0};
    int keep_running = 1;

    printf("enter command:\n");
    while(1 == keep_running)
    {
        fgets(command, BUFSIZ, stdin);
        if (0 == strcmp(command, "exit\n"))
        {
            keep_running = 0;
        }
        else
        {
            if (SUCCESS != system(command))
            {
                fprintf(stderr, "error detected: %s\n", strerror(errno));
            }
        }
        CleanBuffer(command);
    }
}

/*----------------------------------------------------------------*/
/************************* FORK EXECUTION *************************/
/*----------------------------------------------------------------*/

static void ForkShell(void)
{
    char command[BUFSIZ] = {0};
    int keep_running = 1;
    pid_t pid = 0;

    printf("enter command:\n");
  
    while(1 == keep_running)
    {
        fgets(command, BUFSIZ, stdin);
        command[strcspn(command, "\n")] = '\0';
        pid = fork();
        if (0 == strcmp(command, "exit"))
        {
            keep_running = 0;
        }
        
        else if (0 == pid)
        {
            RunCommand(command);
        }
        else
        {
            wait(NULL);         
        }
        CleanBuffer(command);
    }
}

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static void RunCommand(char command[])
{
    int i = 0;
    const char delimiters[1] = " ";
    char* args[127] = {0};
    char* token = strtok(command, delimiters);

    while (NULL != token)
    {
        args[i++] = token;
        token = strtok(NULL, delimiters);
    }

    args[i] = NULL;
    if (FAILURE == execvp(args[0], args))
    {
        fprintf(stderr, "error detected: %s\n", strerror(errno));
    }
}

static void CleanBuffer(char buffer[])
{
    size_t i = 0;
    while ('\0' != buffer[i])
    {
        buffer[i++] = '\0';
    }
}