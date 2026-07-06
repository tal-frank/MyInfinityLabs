#define _POSIX_C_SOURCE 1

#include <sys/types.h> /* pid_t */
#include <errno.h> /* perror */
#include <stdio.h> /* printf */
#include <signal.h> /* kill , SIGUSR1 */
#include <stdlib.h> /* atoi */

volatile int signal_flag = 0;

static void SignalHandler(int signal);

int main(int argc, char* argv[])
{
    struct sigaction signal;
    pid_t pid = 0;

    signal.sa_handler = SignalHandler;
    sigaction(SIGUSR1, &signal, NULL);
    sigaction(SIGUSR2, &signal, NULL);
    pid = atoi(argv[1]);
    while(1)
    {
        printf("ping\n");
        kill(pid, SIGUSR2);
        while(!signal_flag);
    }

    return 0;
}

static void SignalHandler(int signal)
{
    (void)signal;
    signal_flag = 1;
}

