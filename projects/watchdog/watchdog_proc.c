#include <stdio.h>

#include "watchdog.h"

extern int is_watch_dog;

enum
{
    FALSE = 0,
    TRUE
};

int main(int argc, char* argv[])
{
    printf("im am the watcdog! respect my athoretaaa\n");
    is_watch_dog = TRUE;
    WDStart(argv);
    return 0;
}