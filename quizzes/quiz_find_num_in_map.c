#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Map_point
{
    int row;
    int col;
}mpoint_t;

mpoint_t FindInMap(int* arr, size_t rows, size_t cols, int target)
{
    mpoint_t mpoint = {0};
    int row_index = 0;
    int col_index = cols - 1;

    while (target != arr[col_index + row_index] 
       && ((cols * rows) > (row_index + col_index)) 
       && col_index >= 0)
    {
        if (target < arr[col_index + row_index])
        {
            --col_index;
        }

        else
        {
            row_index += cols;
        }
    }
    if (target == arr[col_index + row_index])
    {
        mpoint.col = col_index;
        mpoint.row = row_index / cols;
    }
    else
    {
        mpoint.col = -1;
        mpoint.row = -1;
    }
    return mpoint;
}

void TestFunc(int* arr , size_t rows, size_t cols, int target)
{
    mpoint_t mpoint = FindInMap(arr, 4, 6, target);
    printf("%d is at:\n", target);
    printf("row = %d\n", mpoint.row);
    printf("col = %d\n", mpoint.col);
    printf("\n");
}

int main()
{
    mpoint_t mpoint = {0};
    int arr[4][6] = {{4,  8,  23, 45, 64 , 83 },
                     {15, 21, 44, 49, 78 , 91 },
                     {27, 46, 66, 75, 94 , 104},
                     {41, 55, 79, 99, 115, 148}};

    TestFunc(arr, 4, 6, 4);
    TestFunc(arr, 4, 6, 8);
    TestFunc(arr, 4, 6, 23);
    TestFunc(arr, 4, 6, 45);
    TestFunc(arr, 4, 6, 64);
    TestFunc(arr, 4, 6, 83);
    TestFunc(arr, 4, 6, 15);
    TestFunc(arr, 4, 6, 21);
    TestFunc(arr, 4, 6, 44);
    TestFunc(arr, 4, 6, 49);
    TestFunc(arr, 4, 6, 78);
    TestFunc(arr, 4, 6, 91);
    TestFunc(arr, 4, 6, 27);
    TestFunc(arr, 4, 6, 46);
    TestFunc(arr, 4, 6, 66);
    TestFunc(arr, 4, 6, 75);
    TestFunc(arr, 4, 6, 94);
    TestFunc(arr, 4, 6, 104);
    TestFunc(arr, 4, 6, 41);
    TestFunc(arr, 4, 6, 55);
    TestFunc(arr, 4, 6, 79);
    TestFunc(arr, 4, 6, 99);
    TestFunc(arr, 4, 6, 115);
    TestFunc(arr, 4, 6, 148);
    TestFunc(arr, 4, 6, 1);
    TestFunc(arr, 4, 6, -20);
    TestFunc(arr, 4, 6, 170);
    TestFunc(arr, 4, 6, 20);
    TestFunc(arr, 4, 6, 97);

    return 0;
}