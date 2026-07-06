#define _POSIX_C_SOURCE 1

#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <sys/wait.h> /* wait */
#include <errno.h> /* perror */
#include <stdio.h> /* printf */
#include <signal.h> /* kill , SIGUSR1 */

static void SignalHandler(int signal);

int main()
{
    int count = 0;
    struct sigaction signal;

    signal.sa_handler = SignalHandler;
    sigaction(SIGUSR1, &signal, NULL);
    sigaction(SIGUSR2, &signal, NULL);
    sleep(1);
    while (100 > count)
    {
        printf("pong\n");
        
        sleep(1);
        kill(getppid(), SIGUSR1);
        pause();
        ++count;
    }
    return 1;
}


static void SignalHandler(int signal)
{
    (void)signal;
    return;
}