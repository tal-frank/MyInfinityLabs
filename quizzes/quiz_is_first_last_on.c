#include <stdio.h>

int IsFirsAndLastOn(int input)
{
    return ((0 > input) && (1 == (-input) % 2));
}

void TesFunc(int input)
{
    int is_first_and_last_on = (input & 1) && (input & 0x80000000);
    if (is_first_and_last_on != IsFirsAndLastOn(input))
    {
        printf("---FAILURE---\n");
    }
    else
    {
        printf("---SUCCESS---\n");
    }
}


int main()
{
    TesFunc(6);
    TesFunc(-6);
    TesFunc(7);
    TesFunc(-7);
    TesFunc(51);
    TesFunc(-51);
    TesFunc(30);
    TesFunc(-30);
    return 0;
}
