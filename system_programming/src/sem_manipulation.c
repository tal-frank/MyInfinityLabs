#include <sys/sem.h> /* semaphore API */
#include <string.h> /* strcmp */
#include <stdio.h> /* printf , BUFSIZ */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* atoi */

#define EQUAL (0)

static void RunCommand(char command[], int semaphore);
static void CleanBuffer(char buffer[]);

int main()
{
    int keep_running = 1;
    char command[BUFSIZ] = {0};
    key_t key = 0;
    int semaphore = 0;
    FILE* file = fopen("sem", "a");


    printf("enter semaphore name :\n");
    fgets(command, BUFSIZ, stdin);
    command[strcspn(command, "\n")] = '\0';
    key = ftok(command, 'a');
    semaphore = semget(key, 1, 0666 | IPC_CREAT);

    CleanBuffer(command);
    while (keep_running)
    {
        fgets(command, BUFSIZ, stdin);
        if (EQUAL == strcmp(command, "X\n"))
        {
            keep_running = 0;
        }
        else
        {
            RunCommand(command, semaphore);
            CleanBuffer(command);
        }
    }
    
    semctl(semaphore, 0, IPC_RMID);
    fclose(file);
    return 0;
}

static void RunCommand(char command[], int semaphore)
{
    size_t i = 0;
    int num = 0;
    int sum = 0;
    const char delimiters[1] = " ";
    char* args[10] = {0};
    char* token = strtok(command, delimiters);
    struct sembuf* operation = (struct sembuf*)malloc(sizeof(struct sembuf));

    while (NULL != token)
    {
        args[i++] = token;
        token = strtok(NULL, delimiters);
    }

    if (NULL != args[0] && EQUAL == strcmp(args[0], "I"))
    {
        if (NULL == args[1])
        {
            printf ("not a valid input first");
            return;
        }
        num = atoi(args[1]);
        if (0 < num)
        {
            if (NULL != args[2] && EQUAL == strcmp("undo\n", args[2]))
            {
                operation->sem_flg = SEM_UNDO;
                operation->sem_op = num;
                operation->sem_num = 0;
                if (-1 == semop(semaphore, operation, 1))
                {
                    perror ("error occured ");
                    return;
                }
            }
            else
            {
                printf("incremented\n");
                operation->sem_flg = 0;
                operation->sem_op = num;
                operation->sem_num = 0;
                if (-1 == semop(semaphore, operation, 1))
                {
                    perror ("error occured ");
                    return;
                }
            }
        }
        else
        {
            printf ("not a valid input second\n");
            return;
        }
    }
    else if (NULL != args[0] && EQUAL == strcmp(args[0], "D"))
    {
        if (NULL == args[1])
        {
            printf ("not a valid input third\n");
            return;
        }
        num = atoi(args[1]);
        if (0 < num)
        {
            if (NULL != args[2] && EQUAL == strcmp("undo\n", args[2]))
            {
                operation->sem_flg = SEM_UNDO;
                operation->sem_op = -num;
                operation->sem_num = 0;
                if (-1 == semop(semaphore, operation, 1))
                {
                    perror ("error occured ");
                    return;
                }
            }
            else
            {
                printf("dencremented\n");
                operation->sem_flg = 0;
                operation->sem_op = -num;
                operation->sem_num = 0;
                if (-1 == semop(semaphore, operation, 1))
                {
                    perror ("error occured ");
                    return;
                }
            }
        }
        else
        {
            printf ("not a valid input fourth\n");
            return;
        }
    }
    
    else if (EQUAL == strcmp(args[0], "V\n"))
    {
        sum = semctl(semaphore, 0, GETVAL);
        if (-1 == sum)
        {
            perror("error occured ");
        }
        printf("number in semaphore is : %d\n", sum);
    }
    else
    {
        printf("not a valid input fifth\n");
        return;
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