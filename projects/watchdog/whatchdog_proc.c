
#include "watchdog.h"

enum
{
    FALSE = 0,
    TRUE
}

extern is_watch_dog;

int main(int argc, char* argv[])
{
    is_watch_dog = TRUE;
    WDStart(argv);
    return 0;
}