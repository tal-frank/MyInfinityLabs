#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#define FAILURE (-1)

typedef struct Rotten_fruit
{
    size_t row;
    size_t col;
    int iter;
}rf_t;

void InsertRotten(queue_t* queue, size_t row, size_t col, int iter)
{
    rf_t* rotten = (rf_t*)malloc(sizeof(rf_t));
    rotten->row = row;
    rotten->col = col;
    rotten->iter = iter;

    QueueEnqueue(queue, rotten);
}

void UpdateRottenQueue(queue_t* queue, int* arr, size_t rows, size_t cols, rf_t rotten)
{
    if ((rows - 1 > rotten.row) && (1 == arr[(rotten.row + 1) * cols + (rotten.col)]))
    {
        InsertRotten(queue, rotten.row + 1, rotten.col, rotten.iter + 1);

        arr[(rotten.row + 1) * cols + (rotten.col)] = 2;
    }
    if ((0 < rotten.row) && (1 == arr[(rotten.row - 1) * cols + (rotten.col)]))
    {
        InsertRotten(queue, rotten.row - 1, rotten.col, rotten.iter + 1);
        
        arr[(rotten.row - 1) * cols + (rotten.col)] = 2;
    }
    if (0 < rotten.col && 1 == arr[(rotten.row) * cols + (rotten.col - 1)])
    {
        InsertRotten(queue, rotten.row, rotten.col - 1, rotten.iter + 1);
        
        arr[(rotten.row) * cols + (rotten.col - 1)] = 2;
    }
    if (cols - 1 > rotten.col && 1 == arr[(rotten.row) * cols + (rotten.col + 1)])
    {
        InsertRotten(queue, rotten.row, rotten.col + 1, rotten.iter + 1);
        
        arr[(rotten.row) * cols + (rotten.col + 1)] = 2;
    }
}

int RottenFruit(int* arr, size_t rows, size_t cols)
{
    size_t i = 0;
    size_t j = 0;
    rf_t rotten = {0};

    queue_t* queue = QueueCreate();
    if (NULL == queue)
    {
        return FAILURE;
    }

    for (i = 0; i < rows; ++i)
    {
        for(j = 0; j < cols; ++j)
        {
            if (2 == arr[j + (i * cols)]) 
            {
                InsertRotten(queue, i, j, 0);
            }
        }
    }

    while(!QueueIsEmpty(queue))
    {
        rotten = *(rf_t*)QueuePeek(queue);
        if (2 == arr[rotten.row * cols + rotten.col])
        {
            UpdateRottenQueue(queue, arr, rows, cols, rotten);
        }
        QueueDequeue(queue);
    }
    return rotten.iter;
}

int main()
{
    int arr[5][5] = {{2, 1, 1, 1, 0},
                     {0, 1, 0, 1, 0},
                     {0, 1, 1, 1, 1},
                     {0, 0, 1, 1, 1},
                     {0, 1, 0, 0, 0}};
    int check = RottenFruit((int*)arr, 5, 5);
    if (7 != check)
    {
        printf("---ERROR---\n");
        printf("return %d\n", check);
    }
    else
    {
        printf("---SUCCESS---\n");
        printf("return %d\n", check);
    }
    
    return 0;
}