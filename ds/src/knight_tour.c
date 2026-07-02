/**********************
* knights tour
* Author: Tal Frank
* Reviewer: Moshe Moiseev
* Last update: 01/07/2026
**********************/

#include <time.h> /* time */
#include <stddef.h> /* NULL */
#include <assert.h> /* assert */

#include "knight_tour.h" /* API */
#include "bit_array.h" /* BitarraySetBitOn */

#define NUMBER_OF_COLS (8)
#define NUMBER_OF_JUMP_OPTIONS (8)

typedef enum status
{
    FAILURE = -1,
    SUCCESS,
    TIMEOUT
}status_t;

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLARATIONS *************************/
/*-------------------------------------------------------------------------------*/

static const int row_lut[] = {2, 1, -1, -2, -2, -1, 1, 2};
static const int col_lut[] = {1, 2, 2, 1, -1, -2, -2, -1};

static pos_xy_t UpdateNextPos(pos_xy_t pos, int next);
static pos_xy_t FindBestMove(pos_xy_t pos, bitarray_t board);
static status_t RecKnightsTour(pos_xy_t curr_pos, 
                               path_t dest_path, 
                               bitarray_t board, 
                               int places_left,
                               time_t timeout);

static status_t WarndorffsKnightsTour(pos_xy_t curr_pos, 
                                      path_t dest_path, 
                                      bitarray_t board, 
                                      int step,
                                      time_t timeout);

/*--------------------------------------------------------------*/
/************************* KNIGHTS TOUR *************************/
/*--------------------------------------------------------------*/

int KnightsTour(pos_xy_t start_pos, path_t dest_path, unsigned int timeout, int use_heuristic)
{
    status_t status = SUCCESS;
    bitarray_t board = 0;
    int step = 0;
    time_t curr_time = time(NULL);

    assert(IsValidPosition(start_pos));
    assert(NULL != dest_path);

    if (use_heuristic)
    {
        status = WarndorffsKnightsTour(start_pos, 
                                       dest_path, 
                                       board, 
                                       step, 
                                       curr_time + timeout);
    }
    else
    {
        status = RecKnightsTour(start_pos, 
                                dest_path, 
                                board, 
                                step, 
                                curr_time + timeout);
    }
    return status;
}

/*----------------------------------------------------------*/
/************************* IS VALID *************************/
/*----------------------------------------------------------*/

int IsValidPosition(pos_xy_t pos)
{
    return (pos < BOARD_SIZE);
}

/*------------------------------------------------------------------------*/
/************************* BUILD & PARSE POSITION *************************/
/*------------------------------------------------------------------------*/

pos_xy_t BuildPosition(unsigned char x, unsigned char y)
{
    if (x < NUMBER_OF_COLS && y < NUMBER_OF_COLS)
    {
        return (x * NUMBER_OF_COLS + y);
    }
    else
    {
        return BOARD_SIZE;
    }
}

void ParsePosition(pos_xy_t pos, unsigned char *x, unsigned char *y)
{
    assert(NULL != x);
    assert(NULL != y);

    if (!IsValidPosition(pos))
    {
        return;
    }

    *x = pos / NUMBER_OF_COLS;
    *y = pos % NUMBER_OF_COLS;
}

/*----------------------------------------------------------------*/
/************************* NAIVE SOLUTION *************************/
/*----------------------------------------------------------------*/

static status_t RecKnightsTour(pos_xy_t curr_pos, path_t dest_path, bitarray_t board, int step, time_t timeout)
{
    int i = 0;
    status_t status = FAILURE;
    pos_xy_t next_pos = 0;

    assert(dest_path);

    if(timeout <= time(NULL))
    {
        return TIMEOUT;
    }

    if (BOARD_SIZE - 1 == step)
    {
        dest_path[step] = curr_pos;
        return SUCCESS;
    }

    board = BitarraySetBitOn(board, curr_pos);

    for (i = 0; i < NUMBER_OF_JUMP_OPTIONS && 
                SUCCESS != status && 
                TIMEOUT != status; ++i)
    {
        next_pos = UpdateNextPos(curr_pos, i);
        if (IsValidPosition(next_pos) && 0 == BitarrayGetBit(board, next_pos))
        {
            status = RecKnightsTour(next_pos, dest_path, board, step + 1, timeout);
        }
    }

    if (FAILURE == status)
    {
        return FAILURE;
    }
    
    dest_path[step] = curr_pos;
    return status;
}

/*----------------------------------------------------------------------*/
/************************* WARNDORFFS ALGORITHM *************************/
/*----------------------------------------------------------------------*/

static status_t WarndorffsKnightsTour(pos_xy_t curr_pos, path_t dest_path, bitarray_t board, int step, time_t timeout)
{
    status_t status = FAILURE;
    pos_xy_t next_pos = 0;

    assert(dest_path);

    if(timeout <= time(NULL))
    {
        return TIMEOUT;
    }

    if (BOARD_SIZE - 1 == step)
    {
        dest_path[step] = curr_pos;
        return SUCCESS;
    }

    board = BitarraySetBitOn(board, curr_pos);

    next_pos = FindBestMove(curr_pos, board);
    status = WarndorffsKnightsTour(next_pos, dest_path, board, step + 1, timeout);

    if (FAILURE == status)
    {
        return FAILURE;
    }
    
    dest_path[step] = curr_pos;
    return status;
}

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static pos_xy_t FindBestMove(pos_xy_t pos, bitarray_t board)
{
    int i = 0;
    int j = 0;
    int min = NUMBER_OF_JUMP_OPTIONS;
    int count = 0;
    pos_xy_t next_pos = 0;
    pos_xy_t next_pos_runner = 0;
    pos_xy_t next_next = 0;
    
    for (i = 0; i < NUMBER_OF_JUMP_OPTIONS; ++i)
    {
        next_pos_runner = UpdateNextPos(pos, i);
        if (!IsValidPosition(next_pos_runner) || 1 == BitarrayGetBit(board, next_pos_runner))
        {
            continue;
        }
        count = 0;
        for (j = 0; j < NUMBER_OF_JUMP_OPTIONS; ++j)
        {
            next_next = UpdateNextPos(next_pos_runner, j);
            
            if (IsValidPosition(next_next) && 
                0 == BitarrayGetBit(board, next_next))
            {
                ++count;
            }
        }
        if (min > count)
        {
            next_pos = next_pos_runner;
            min = count;
        }
    }
    return next_pos;
}

static pos_xy_t UpdateNextPos(pos_xy_t pos, int next)
{
    unsigned char x = 0;
    unsigned char y = 0;
    pos_xy_t next_pos = pos;

    ParsePosition(pos, &x, &y);
    x += row_lut[next];
    y += col_lut[next];

    next_pos = BuildPosition(x, y);
    return next_pos;
}
