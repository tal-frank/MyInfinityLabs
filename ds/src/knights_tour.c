
#include "knights_tour.h"
#include "bit_array.h"

#define NUMBER_OF_COLS (8)
#define NUMBER_OF_JUMP_OPTIONS (8)

typedef enum status
{
    FAILURE = -1,
    SUCCESS
}status_t;

static const int row_lut[] = {2, 1, -1, -2, -2, -1, 1, 2};
static const int col_lut[] = {1, 2, 2, 1, -1, -2, -2, -1};

static pos_xy_t UpdateNextPos(pos_xy_t pos, int next);
static pos_xy_t FindBestMove(pos_xy_t pos, bitarray_t bitarray);
static status_t RecKnightsTour(pos_xy_t curr_pos, 
                               path_t dest_path, 
                               bitarray_t bitarray, 
                               int places_left);
static status_t WarndorffsKnightsTour(pos_xy_t curr_pos, 
                                      path_t dest_path, 
                                      bitarray_t bitarray, 
                                      int step);

int KnightsTour(pos_xy_t start_pos, path_t dest_path, unsigned int timeout, int use_heuristic)
{
    status_t status = SUCCESS;
    bitarray_t bitarray = 0;
    int step = 0;
    if (use_heuristic)
    {
        status = WarndorffsKnightsTour(start_pos, dest_path, bitarray, step);
    }
    else
    {
        status = RecKnightsTour(start_pos, dest_path, bitarray, step);
    }
    return status;
}

int IsValidPosition(pos_xy_t pos)
{
    return (pos < BOARD_SIZE);
}

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
    if (!IsValidPosition(pos))
    {
        return;
    }

    *x = pos / NUMBER_OF_COLS;
    *y = pos % NUMBER_OF_COLS;
}


static status_t RecKnightsTour(pos_xy_t curr_pos, path_t dest_path, bitarray_t bitarray, int step)
{
    int i = 0;
    status_t status = FAILURE;
    pos_xy_t next_pos = 0;

    if (BOARD_SIZE - 1 == step)
    {
        dest_path[step] = curr_pos;
        return SUCCESS;
    }

    bitarray = BitarraySetBitOn(bitarray, curr_pos);

    for (i = 0; i < NUMBER_OF_JUMP_OPTIONS && SUCCESS != status; ++i)
    {
        next_pos = UpdateNextPos(curr_pos, i);
        if (IsValidPosition(next_pos) && 0 == BitarrayGetBit(bitarray, next_pos))
        {
            status = RecKnightsTour(next_pos, dest_path, bitarray, step + 1);
        }
    }

    if (FAILURE == status)
    {
        return FAILURE;
    }
    
    dest_path[step] = curr_pos;
    return SUCCESS;
}

static status_t WarndorffsKnightsTour(pos_xy_t curr_pos, path_t dest_path, bitarray_t bitarray, int step)
{
    status_t status = FAILURE;
    pos_xy_t next_pos = 0;

    if (BOARD_SIZE == step)
    {
        dest_path[step] = curr_pos;
        return SUCCESS;
    }

    bitarray = BitarraySetBitOn(bitarray, curr_pos);

    next_pos = FindBestMove(curr_pos, bitarray);
    status = WarndorffsKnightsTour(next_pos, dest_path, bitarray, step + 1);

    if (FAILURE == status)
    {
        return FAILURE;
    }
    
    dest_path[step] = curr_pos;
    return SUCCESS;
}

static pos_xy_t FindBestMove(pos_xy_t pos, bitarray_t bitarray)
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
        if (!IsValidPosition(next_pos_runner) || 1 == BitarrayGetBit(bitarray, next_pos_runner))
        {
            continue;
        }
        count = 0;
        for (j = 0; j < NUMBER_OF_JUMP_OPTIONS; ++j)
        {
            next_next = UpdateNextPos(next_pos_runner, j);
            
            if (IsValidPosition(next_next) && 
                0 == BitarrayGetBit(bitarray, next_next))
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

/*
static status_t WarndorffsKnightsTour(pos_xy_t curr_pos, path_t dest_path, bitarray_t bitarray, int step)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int min = NUMBER_OF_JUMP_OPTIONS;
    int count = 0;
    status_t status = FAILURE;
    pos_xy_t next_pos = {0};
    pos_xy_t next_pos_runner = {0};
    pos_xy_t next_next = {0};

    if (BOARD_SIZE - 1== step)
    {
        return SUCCESS;
    }

    bitarray = BitarraySetBitOn(bitarray, curr_pos);

    do 
    {
        next_pos_runner = UpdateNextPos(curr_pos, i);
        if (!IsValidPosition(next_pos_runner))
        {
            ++i;
            continue;
        }
        for (j = 0; j < NUMBER_OF_JUMP_OPTIONS; ++j)
        {
            count = 0;
            for (k = 0; k < NUMBER_OF_JUMP_OPTIONS; ++k)
            {    
                next_next = UpdateNextPos(next_pos_runner, k);
                if (IsValidPosition(next_next) && 0 == BitarrayGetBit(bitarray, next_next))
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
        if (NUMBER_OF_JUMP_OPTIONS == i)
        {
            return FAILURE;
        }
        status = WarndorffsKnightsTour(next_pos, dest_path, bitarray, step + 1);
        ++i;
    } while(status != SUCCESS && i < NUMBER_OF_JUMP_OPTIONS);
    
    if (SUCCESS != status)
    {
        return FAILURE;
    }

    dest_path[step] = curr_pos;

    return SUCCESS;
}
*/
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
