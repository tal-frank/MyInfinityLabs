#define _POSIX_C_SOURCE 1

#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <errno.h> /* perror */
#include <stdio.h> /* printf */
#include <signal.h> /* kill , SIGUSR1 */

static void SignalHandler(int signal);

void PingPong()
{
    int count = 0;
    struct sigaction signal;
    pid_t pid = 0;

    signal.sa_handler = SignalHandler;
    sigaction(SIGUSR1, &signal, NULL);
    sigaction(SIGUSR2, &signal, NULL);
    
    pid = fork();
    if (0 < pid)
    {
        while (5 > count)
        {
            printf("ping\n");
            
            sleep(1);
            
            kill(pid, SIGUSR1);
            pause();
            ++count;
        }
    }
    else if (0 == pid)
    {
        execl("pong.out", "pong.out");
/*
        sleep(1);

        while (5 > count)
        {
            printf("pong\n");

            sleep(1);

            kill(getppid(), SIGUSR2);
            pause();
            ++count;
        }
        wait(NULL);
*/ 
    }
    else
    {
        perror("couldn't create a child process");
    }
}

static void SignalHandler(int signal)
{
    (void)signal;
    return;
}