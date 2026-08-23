#include <stdio.h> /* NULL */
#include <stack.h> /* stack API */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */
#include <stdlib.h> /* calloc */

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
    int data;
};

struct BSTNode
{
    tree_node_t* children[NUM_OF_CHILDREN];
    int data;
};

/*#########################################################*/
/*-------------------- question 1 -------------------------*/
/*#########################################################*/

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

/*#########################################################*/
/*-------------------- question 2 -------------------------*/
/*#########################################################*/

int ArrayBiggestSum(int arr[], size_t size)
{
    size_t i = 0;
    int max_sum = 0;
    int sum = 0;

    for (i = 0; i < size; ++i)
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

/*#########################################################*/
/*-------------------- question 3 -------------------------*/
/*#########################################################*/

void SortStack(stack_t* stack)
{
    int biggest = 0;
    stack_t* temp_stack = StackCreate(StackCapacity(stack), sizeof(int));
    if (NULL == stack)
    {
        return;
    }

    while (!StackIsEmpty(stack))
    {
        biggest = *(int*)StackPeek(stack);
        StackPop(stack);
        while (!StackIsEmpty(temp_stack) && biggest > *(int*)StackPeek(temp_stack))
        {
            StackPush(stack, StackPeek(temp_stack));
            StackPop(temp_stack);
        }
        StackPush(temp_stack, &biggest);
    }

    while (!StackIsEmpty(temp_stack))
    {
        StackPush(stack, StackPeek(temp_stack));
        StackPop(temp_stack);
    }
    StackDestroy(temp_stack);
}


/*#########################################################*/
/*-------------------- question 4 -------------------------*/
/*#########################################################*/

int SortCharInFile(const char* file_name, char* result)
{
    size_t buffer_i = 0;
    size_t counter = 0;
    size_t result_i = 0;
    int ch = 0;
    char* count_buff = (char*)calloc(CHAR_SIZE, sizeof(char));
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
        counter = count_buff[buffer_i];
        while (0 < counter)
        {
            result[result_i] = buffer_i;
            ++result_i;
            --counter;
        }
    }
    result[result_i] = '\0';
    fclose(file);
    free(count_buff);
    return SUCCESS;
}

/*#########################################################*/
/*-------------------- question 5 -------------------------*/
/*#########################################################*/

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
    size_t i = 0;

    while(NULL != arr[i] && i < size)
    {
        i = (*arr[i] > new_data) ? 2*i + 1 : 2*i + 2;
    }

    if (i > size)
    {
        return FAILURE;
    }
    else
    {
        *arr[i] = new_data;
    }
    return SUCCESS;
}

/*#########################################################*/
/*-------------------- question 7 -------------------------*/
/*#########################################################*/

void RecReverseString(char* str, size_t place, size_t len)
{
    char temp = 0;
    if(place > len / 2)
    {
        return;
    }
    temp = str[place];
    str[place] = str[len - place - 1];
    str[len - place - 1] = temp;
    
    RecReverseString(str, ++place, len);
}

void ReverseString(char* str)
{
    size_t len = strlen(str);
    RecReverseString(str, 0, len);
}

/*##########################################################*/
/*-------------------- question 10 -------------------------*/
/*##########################################################*/

void StackInsertInOrder(stack_t* stack, int num)
{
    int top = 0;

    if(StackIsEmpty(stack) || *(int*)StackPeek(stack) < num)
    {
        StackPush(stack, &num);
        return;
    }
    top = *(int*)StackPeek(stack);
    StackPop(stack);
    
    StackInsertInOrder(stack, num);
    StackPush(stack, &top);
}

/*#############################################################*/
/*-------------------- test functions -------------------------*/
/*#############################################################*/

void PrintSll(sll_node_t* node)
{
    while (NULL != node)
    {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void PrintStack(stack_t* stack)
{
    int temp = 0;

    if (StackIsEmpty(stack))
    {
        return;
    }

    temp = *(int*)StackPeek(stack);
    StackPop(stack);
    PrintStack(stack);
    printf(" %d ", temp);
    StackPush(stack, &temp);
}

void PrintArr(char arr[])
{
    size_t i = 0;
    while ('\0' != arr[i])
    {
        printf("%c", arr[i++]);
    }
    printf("\n");
}


/*###################################################*/
/*-------------------- main -------------------------*/
/*###################################################*/

int main()
{
    int find_biggest_sum[10] = {5, 2, -1, -7, 3, 4, -5, 9, -4, 3};
    int biggest_sum = 0;
    char sorted_file[1000];
    char* string_to_reverse = (char*)malloc(20 * sizeof(char*));

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 6;
    int num6 = 6;
    int num7 = 7;
    int num8 = 8;
    int num9 = 9;
    int num10 = 11;
    int num11 = 11;
    int num12 = 12;
    int num13 = 13;
    int num14 = 14;
    int num15 = 15;
    int num16 = 5;
    int num17 = 10;
    int num18 = 16;
    int num19 = 0;
    int num20 = 13;

    sll_node_t* sll_node1 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node2 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node3 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node4 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node5 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node6 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node7 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node8 = (sll_node_t*)malloc(sizeof(sll_node_t));
    sll_node_t* sll_node9 = (sll_node_t*)malloc(sizeof(sll_node_t));

    stack_t* stack = StackCreate(20, sizeof(int));

    sll_node1->data = 1;
    sll_node1->next = sll_node2;
    sll_node2->data = 2;
    sll_node2->next = sll_node3;
    sll_node3->data = 3;
    sll_node3->next = sll_node4;
    sll_node4->data = 4;
    sll_node4->next = sll_node5;
    sll_node5->data = 5;
    sll_node5->next = sll_node6;
    sll_node6->data = 6;
    sll_node6->next = sll_node7;
    sll_node7->data = 7;
    sll_node7->next = sll_node8;
    sll_node8->data = 8;
    sll_node8->next = sll_node9;
    sll_node9->data = 9;
    sll_node9->next = NULL;

    printf("\nexercise 1 : sll flip\n");
    printf("sll before iterative flip : ");
    PrintSll(sll_node1);
    IterSllFlip(sll_node1);
    printf("sll after iterative flip : ");
    PrintSll(sll_node9);
    printf("sll after recursive flip : ");
    WrapperRecSllFlip(sll_node9);
    PrintSll(sll_node1);

    free(sll_node1);
    free(sll_node2);
    free(sll_node3);
    free(sll_node4);
    free(sll_node5);
    free(sll_node6);
    free(sll_node7);
    free(sll_node8);
    free(sll_node9);

    
    StackPush(stack, &num6);
    StackPush(stack, &num3);
    StackPush(stack, &num2);
    StackPush(stack, &num12);
    StackPush(stack, &num5);
    StackPush(stack, &num1);
    StackPush(stack, &num11);
    StackPush(stack, &num4);
    StackPush(stack, &num9);
    StackPush(stack, &num14);
    StackPush(stack, &num13);
    StackPush(stack, &num7);
    StackPush(stack, &num8);
    StackPush(stack, &num15);
    StackPush(stack, &num10);

    printf("\nexercise 2 : biggest sum\n");
    biggest_sum = ArrayBiggestSum(find_biggest_sum, 10);
    printf("biggest sum is: %d\n", biggest_sum);

    printf("\nexercise 3 : stack sort\n");
    PrintStack(stack);
    printf("\n");
    SortStack(stack);
    PrintStack(stack);
    printf("\n");

    
    printf("\nexercise 4 : sort file\n");
    SortCharInFile("test.txt", sorted_file);
    PrintArr(sorted_file);
    
    printf("\nexercise 4 : sort file\n");
    


    printf("\nexercise 7 : reverse string\n");
    memcpy(string_to_reverse, "abcdefghijk", 12);
    printf("%s\n", string_to_reverse);
    ReverseString(string_to_reverse);
    printf("%s\n", string_to_reverse);
    
    free(string_to_reverse);
    
    printf("\nexercise 9 : insert to stack in order\n");
    PrintStack(stack);
    printf("\n");
    StackInsertInOrder(stack, num16);
    StackInsertInOrder(stack, num17);
    StackInsertInOrder(stack, num18);
    StackInsertInOrder(stack, num19);
    StackInsertInOrder(stack, num20);
    PrintStack(stack);
    printf("\n");

    StackDestroy(stack);

    return 0;
}