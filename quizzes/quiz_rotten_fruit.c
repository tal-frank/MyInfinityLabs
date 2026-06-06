#include <stdlib.h>

#include "queue.h"

#define FAILURE (-1)

typedef struct Rotten_fruit
{
    size_t row;
    size_t col;
    int iter;
}rf_t;

void InsertRotten(queue_t* queue, size_t row, size_t col)
{
    rf_t* rotten = (rf_t*)malloc(sizeof(rf_t));
    rotten->row = row;
    rotten->col = col;
    rotten->iter = 0;

    QueueEnqueue(queue, rotten);
}

void UpdateRottenQueue(int* arr, size_t rows, size_t cols, rf_t rotten)
{
    
    if (rows > rotten.row && 1 == arr[(rotten.row + 1) * cols + (rotten.col)])
    {
        QueueEnqueue()
    }
    if (rows > rotten.row && 1 == arr[(rotten.row + 1) * cols + (rotten.col)])
    {

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
                InsertRotten(queue, i, j);
            }
        }
    }

    while(!QueueIsEmpty(queue))
    {
        rotten = *(rf_t*)QueuePeek(queue);
        UpdateRottenQueue();
    }
}