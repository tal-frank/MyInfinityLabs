#include <unistd.h> /* sleep */
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "watchdog.h"

#define UNUSED(x) ((void)x)

int main(int argc, char* argv[])
{
    time_t timeout = 5;
    time_t time_left = 5;
    int counter = 0;
    char name[50] = {0};
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    WDStart(argv);
    UNUSED(argc);
    while (100 > counter)
    {
        ++counter;
        printf("process running some tests %d\n", counter);
        if (0 == time_left)
        {
            time_left = 5;
        }
        while (0 != time_left)
        {
            time_left = sleep(time_left);
        }  
    }

    WDStop(timeout);
    return 0;
}