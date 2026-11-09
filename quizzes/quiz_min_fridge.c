#include <stddef.h>
#include <stdio.h>

typedef struct product
{
    int min_temp;
    int max_temp;
}fridge_t;

void SwapFridges(fridge_t* fridge1, fridge_t* fridge2)
{
    fridge_t tmp = *fridge1;
    *fridge1 = *fridge2;
    *fridge2 = tmp;
}

void BubbleSortByMinTemp(fridge_t fridges[], size_t size)
{
    int is_fliped = 1;
    size_t i = 0;

    while (is_fliped)
    {
        is_fliped = 0;
        for (i = 0; i < size - 1; ++i)
        {
            if (fridges[i].min_temp > fridges[i + 1].min_temp)
            {
                SwapFridges(&fridges[i], &fridges[i + 1]);
                is_fliped = 1;
            } 
        }
    }
}

int MinFridge(fridge_t fridges[], size_t size)
{
    int max_temp = fridges[0].max_temp;
    int number_of_fridges = 1;
    size_t i = 0;

    BubbleSortByMinTemp(fridges, size);
    for (i = 0; i < size; ++i)
    {
        if (max_temp < fridges[i].min_temp)
        {
            number_of_fridges += 1;
            max_temp = fridges[i].max_temp;
        }
    }

    return number_of_fridges;
}

int main()
{
    int number_of_fridges = 0;

    fridge_t fridges[10] = {{3, 6},
                            {2, 4},
                            {6, 9},
                            {1, 6},
                            {2, 5},
                            {0, 2},
                            {0, 3},
                            {4, 7},
                            {8, 10},
                            {2, 8}};

    number_of_fridges = MinFridge(fridges, 10);
    printf("number of fridges needed is : %d\n", number_of_fridges);
    
    return 0;
}