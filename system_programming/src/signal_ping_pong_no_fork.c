#define _POSIX_C_SOURCE (199309L)

#include <sys/types.h> /* pid_t */
#include <errno.h> /* perror */
#include <stdio.h> /* printf */
#include <signal.h> /* kill , SIGUSR1 */

volatile int signal_flag = 0;
volatile pid_t signal_pid = 0;

static void SignalHandler(int signal, siginfo_t* info, void* ucontext);

int main() 
{
    struct sigaction signal;
    pid_t pid = 0;

    signal.sa_flags = SA_SIGINFO;
    signal.sa_sigaction = SignalHandler;
    sigaction(SIGUSR1, &signal, NULL);
    sigaction(SIGUSR2, &signal, NULL);
    
    while(1)
    {
        while(!signal_flag);
        printf("pong\n");  
        kill(signal_pid, SIGUSR1);
    }
    
    return 0;
}

static void SignalHandler(int signal, siginfo_t* info, void* ucontext)
{
    (void)signal;
    signal_flag = 1;
    if (!signal_pid)
    {
        signal_pid = info->si_pid;
    }
}