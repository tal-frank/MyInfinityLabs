#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode node_t;

struct TreeNode
{
    int data;
    node_t* children[2];
};

enum
{
    LEFT = 0,
    RIGHT
};

static void LevelByLevelPrint(node_t* root, queue_t* queue)
{
    QueueEnqueue(queue, root);
    while (!QueueIsEmpty(queue))
    {
        if (NULL != root->children[LEFT])
        {
            QueueEnqueue(queue, root->children[LEFT]);
        }
        if (NULL != root->children[RIGHT])
        {
            QueueEnqueue(queue, root->children[RIGHT]);
        }
        printf(" %d ", ((node_t*)QueuePeek(queue))->data);
        QueueDequeue(queue);
        root = (node_t*)QueuePeek(queue);
    }
}

int main()
{
    node_t* root = (node_t*)malloc(sizeof(node_t));
    node_t* left1 = (node_t*)malloc(sizeof(node_t));
    node_t* left2 = (node_t*)malloc(sizeof(node_t));
    node_t* left3 = (node_t*)malloc(sizeof(node_t));
    node_t* left4 = (node_t*)malloc(sizeof(node_t));
    node_t* right1 = (node_t*)malloc(sizeof(node_t));
    node_t* right2 = (node_t*)malloc(sizeof(node_t));
    node_t* right3 = (node_t*)malloc(sizeof(node_t));
    node_t* right4 = (node_t*)malloc(sizeof(node_t));
    node_t* right5 = (node_t*)malloc(sizeof(node_t));

    queue_t* queue = QueueCreate();

    root->data = 0;
    root->children[LEFT] = left1;
    root->children[RIGHT] = right1;

    left1->data = 1;
    left1->children[LEFT] = left2;
    left1->children[RIGHT] = right2;

    left2->data = 3;
    left2->children[LEFT] = NULL;
    left2->children[RIGHT] = right4;

    left3->data = 5;
    left3->children[LEFT] = NULL;
    left3->children[RIGHT] = right5;
    left4->data = 8;

    left4->children[LEFT] = NULL;
    left4->children[RIGHT] = NULL;

    right1->data = 2;
    right1->children[LEFT] = left3;
    right1->children[RIGHT] = right3;

    right2->data = 4;
    right2->children[LEFT] = left4;
    right2->children[RIGHT] = NULL;

    right3->data = 6;
    right3->children[LEFT] = NULL;
    right3->children[RIGHT] = NULL;

    right4->data = 7;
    right4->children[LEFT] = NULL;
    right4->children[RIGHT] = NULL;

    right5->data = 9;
    right5->children[LEFT] = NULL;
    right5->children[RIGHT] = NULL;

    LevelByLevelPrint(root, queue);

    QueueDestroy(queue);
    free(root);
    free(left1);
    free(left2);
    free(left3);
    free(left4);
    free(right1);
    free(right2);
    free(right3);
    free(right4);
    free(right5);

    return 0;
}