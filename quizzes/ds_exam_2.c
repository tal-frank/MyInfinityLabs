#include <stdio.h> // NULL , calloc
#include <stack.h> // stack API
#include <stddef.h> // size_t

#define NUM_OF_CHILDREN (2)
#define CHAR_SIZE (256)

enum
{
    LEFT = 0,
    RIGHT
};

enum
{
    SUCCESS = 0,
    FAILURE
};

typedef struct SllNode sll_node_t;
typedef struct BSTNode tree_node_t;

struct SllNode
{
    sll_node_t* next;
    void* data;
};

struct BSTNode
{
    tree_node_t* children[NUM_OF_CHILDREN];
    int data;
};

//#########################################################//
//-------------------- question 1 -------------------------//
//#########################################################//

sll_node_t* IterSllFlip (sll_node_t* node)
{
    sll_node_t* prev = node;
    sll_node_t* cur = prev->next;
    sll_node_t* next = cur->next;

    prev->next = NULL;
    while (NULL != next)
    {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;

    return cur;
}

sll_node_t* RecSllFlip(sll_node_t* cur, sll_node_t* next)
{
    sll_node_t* new_first = NULL;
    if (NULL == next)
    {
        return cur;
    }
    new_first = RecSllFlip(next, next->next);
    next->next = cur;

    return new_first;
}

sll_node_t* WrapperRecSllFlip(sll_node_t* node)
{
    sll_node_t* cur = node;
    sll_node_t* next = cur->next;

    cur->next = NULL;
    node = RecSllFlip(cur, next);

    return node;
}

//#########################################################//
//-------------------- question 2 -------------------------//
//#########################################################//

int ArrayBiggestSum(int arr[], size_t size)
{
    size_t i = 0;
    int max_sum = 0;
    int sum = 0;

    for (i = 0; i = size; ++i)
    {
        sum += arr[i];
        sum = sum < 0 ? 0 : sum;
        if (sum > max_sum)
        {
            max_sum = sum;
        }
    }
    return max_sum;
}

//#########################################################//
//-------------------- question 3 -------------------------//
//#########################################################//

void SortStack(stack_t* stack)
{
    int sort_again = 0;
    int biggest = 0;
    stack_t* temp_stack = StackCreate(StackCapacity(stack), sizeof(int));
    if (NULL == stack)
    {
        return;
    }

    biggest = *(int*)StackPeek(stack);
    StackPop(stack);
    while (sort_again)
    {
        sort_again = 0;
        while (!StackIsEmpty(stack))
        {
            if (StackPeek(stack) > biggest)
            {
                sort_again = 1;
                StackPush(temp_stack, biggest);
                biggest = *(int*)StackPeek(stack);
                StackPop(stack);
            }
            else
            {
                StackPush(temp_stack, StackPeek(stack));
                StackPop(stack);
            }
        }

        while (!StackIsEmpty(temp_stack))
        {
            StackPush(stack, StackPeek(temp_stack));
            StackPop(temp_stack);
        }
    }
}

//#########################################################//
//-------------------- question 4 -------------------------//
//#########################################################//

int SortCharInFile(const char* file_name, char* result)
{
    size_t buffer_i = 0;
    size_t counter = 0;
    size_t result_i = 0;
    char ch = 0;
    char* count_buff = calloc(CHAR_SIZE);
    FILE* file = fopen(file_name, "r");
    if (NULL == file)
    {
        return FAILURE;
    }

    ch = fgetc(file);
    while (EOF != ch)
    {
        count_buff[ch] += 1;
        ch = fgetc(file);
    }

    for (buffer_i = 0; buffer_i < CHAR_SIZE; ++buffer_i)
    {
        counter = count_buff[i];
        while (0 < counter)
        {
            result[result_i] = i;
            ++result_i;
            --counter;
        }
    }
    return SUCCESS;
}

//#########################################################//
//-------------------- question 5 -------------------------//
//#########################################################//

void IterativeInsertTree(tree_node_t* root, tree_node_t* new_node)
{
    int side = (root->data > new_node->data) ? LEFT : RIGHT;

    while(NULL != root->children[side])
    {
        root = root->children[side];
        side = (root->data > new_node->data) ? LEFT : RIGHT;
    }
    root->children[side] = new_node;
}

void RecInsertTree(tree_node_t* root, tree_node_t* new_node)
{
    int side = (root->data > new_node->data) ? LEFT : RIGHT;

    if (NULL != root->children[side])
    {
        root->children[side] = new_node;
        return;
    }
    RecInsertTree(root->children[side], new_node);
}

int ArrTreeInsert(int* arr[], size_t size, int new_data)
{
    int i = 0;

    while(NULL != arr[i] && i < size)
    {
        i = (arr[i] > new_data) ? 2*i + 1 : 2*i + 2;
    }

    if (i > size)
    {
        return FAILURE;
    }
    else
    {
        *arr[i] = new_data;
    }
}
