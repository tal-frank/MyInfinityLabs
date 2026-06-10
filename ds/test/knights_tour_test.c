#include <stdio.h>

#include "knights_tour.h"

static void PrintArr(path_t arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    path_t rec_result = {0};
    path_t warndorffs_result = {0};
    unsigned char x = 0;
    unsigned char y = 0;
    pos_xy_t start_pos = {0};
    int timeout = 0;
    int status = 0;


    start_pos = BuildPosition(x, y);

    if (!IsValidPosition(start_pos))
    {
        printf("the input is not valid\n");
    }

    status = KnightsTour(start_pos, rec_result, timeout, 0);
    ParsePosition(rec_result[10], &x, &y);
    printf("x = %d , y = %d\n", x, y);
    printf ("status = %d\n" , status);
    
    PrintArr(rec_result, BOARD_SIZE);
    start_pos = BuildPosition(x, y);
    status = KnightsTour(start_pos, rec_result, timeout, 0);
    ParsePosition(rec_result[10], &x, &y);
    printf("x = %d , y = %d\n", x, y);
    printf ("status = %d\n" , status);
    
    PrintArr(rec_result, BOARD_SIZE);
    
    /*
    start_pos = BuildPosition(x, y);
    status = KnightsTour(start_pos, rec_result, timeout, 0);
    ParsePosition(rec_result[10], &x, &y);
    printf("x = %d , y = %d\n", x, y);
    printf ("status = %d\n" , status);
    
    PrintArr(rec_result, BOARD_SIZE);
    */  
    
    status = KnightsTour(start_pos, warndorffs_result, timeout, 1);
    ParsePosition(warndorffs_result[10], &x, &y);
    printf("x = %d , y = %d\n", x, y);
    printf ("status = %d\n" , status);

    PrintArr(warndorffs_result, BOARD_SIZE);

    status = KnightsTour(start_pos, warndorffs_result, timeout, 1);
    ParsePosition(warndorffs_result[2], &x, &y);
    printf("x = %d , y = %d\n", x, y);
    printf ("status = %d\n" , status);

    PrintArr(warndorffs_result, BOARD_SIZE);


    printf("\n");


    return 0;
}