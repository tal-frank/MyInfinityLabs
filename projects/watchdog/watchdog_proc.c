#ifndef NDEBUG
    #include <stdio.h>
#endif
#include "watchdog.h"

extern int is_watch_dog;

enum
{
    FALSE = 0,
    TRUE
};

int main(int argc, char* argv[])
{
    #ifndef NDEBUG
        printf("im am the watcdog! respect my athoretaaa\n");
    #endif
    is_watch_dog = TRUE;
    WDStart(argv);
    return 0;
}