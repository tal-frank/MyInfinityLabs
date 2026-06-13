
#include <stdio.h>

#include "avl_recursive_tree.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET_COLOR   "\x1b[0m"

static int num1 = 1;
static int num2 = 2;
static int num3 = 3;
static int num4 = 4;
static int num5 = 5;
static int num6 = 6;
static int num7 = 7;
static int num8 = 8;
static int num9 = 9;
static int num10 = 10;
static int num11 = 11;

enum
{
    LEFT = 0, 
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct Avl_node avl_node_t;
struct AVLTree
{
	avl_node_t* root;
	int (*cmp_func)(const void* data, const void* tree_data);
};
struct Avl_node
{
	size_t height;
	void* data;
	avl_node_t* children[NUM_OF_CHILDREN];
};

int CmpFunc(const void* num1, const void* num2)
{
	int number1 = *(int*)num1;
	int number2 = *(int*)num2;
	
	return number1 - number2;
}

int AddNum(void* num1, void* num2)
{	
	*(int*)num1 += *(int*)num2;
	
	return 0;
}

avl_node_t* GetRightChildForWhiteboxTest(avl_node_t* root)
{
	return root->children[RIGHT];
}

avl_node_t* GetLeftChildForWhiteboxTest(avl_node_t* root)
{
	return root->children[LEFT];
}

void TreePrint(avl_node_t* root, int level)
{
	int i = 0;
        if (root == NULL)
        {
                return;
        }
        TreePrint(GetRightChildForWhiteboxTest(root), level + 2);
        for (i = 0; i < level; i++)
        {
                printf(i == level - 1 ? "|-" : "  ");
        }
        printf("%d\n", *(int*)root->data);
        TreePrint(GetLeftChildForWhiteboxTest(root), level + 2);
}

void InsertTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	
	printf(CYAN "IS EMPTY TEST\n" RESET_COLOR);
	if (!AVLIsEmpty(avl))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("tells not empty when empty\n\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty works\n\n");
	
	AVLInsert(avl, &num5);
	
	TreePrint(avl->root, 0);
	
	if (AVLIsEmpty(avl))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("tells empty when not empty\n\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty works\n\n");
	
	printf(CYAN "INSERT\n" RESET_COLOR);
	
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num8);
	AVLInsert(avl, &num7);
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num9);
	printf("\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLDestroy(avl);
}

void CountTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	size_t count = 0;
	
	printf(CYAN "COUNT TEST\n" RESET_COLOR);
	count = AVLCount(avl);
	if (0 != count)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("count is wrong\n");
		printf("expected : 0\nactual : %ld\n\n", count);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count 0 works\n\n");
	
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num2);
	
	count = AVLCount(avl);
	if (2 != count)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("count is wrong\n");
		printf("expected : 2\nactual : %ld\n\n", count);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count 2 works\n\n");
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num8);
	AVLInsert(avl, &num7);
	
	count = AVLCount(avl);
	if (5 != count)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("count is wrong\n");
		printf("expected : 5\nactual : %ld\n\n", count);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count 5 works\n\n");
	
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num9);
	
	count = AVLCount(avl);
	if (8 != count)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("count is wrong\n");
		printf("expected : 8\nactual : %ld\n\n", count);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("count 8 works\n\n");
	
	AVLDestroy(avl);
}


void HeightTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	size_t height = 0;
	
	printf(CYAN "HEIGHT TEST\n" RESET_COLOR);
	
	height = AVLHeight(avl);
	if (0 != height)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("height is wrong\n");
		printf("expected : 0\nactual : %ld\n\n", height);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("height 0 works\n\n");
	
	AVLInsert(avl, &num5);
	
	height = AVLHeight(avl);
	if (1 != height)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("height is wrong\n");
		printf("expected : 1\nactual : %ld\n\n", height);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("height 1 works\n\n");
	
	AVLInsert(avl, &num2);
	
	height = AVLHeight(avl);
	if (2 != height)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("height is wrong\n");
		printf("expected : 2\nactual : %ld\n\n", height);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("height 2 works\n\n");
	
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num8);
	AVLInsert(avl, &num7);
	
	height = AVLHeight(avl);
	if (3 != height)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("height is wrong\n");
		printf("expected : 3\nactual : %ld\n\n", height);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("height 3 works\n\n");
	
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num9);
	
	height = AVLHeight(avl);
	if (4 != height)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("height is wrong\n");
		printf("expected : 4\nactual : %ld\n\n", height);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("height 4 works\n\n");
	
	AVLDestroy(avl);
}

void FindTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	int data = -1;
	int number1 = 9;
	int number2 = 6;
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num8);
	AVLInsert(avl, &num7);
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num9);
	
	printf(CYAN "FIND TEST\n" RESET_COLOR);
	
	data = *(int*)AVLFind(avl, &num2);	
	if (2 != data)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("element wasn't found\n");
		printf("expected : 2\nactual : %d\n\n", data);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found 2\n\n");
	
	data = *(int*)AVLFind(avl, &number1);	
	if (9 != data)
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("element wasn't found\n");
		printf("expected : 9\nactual : %d\n\n", data);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found 9\n\n");
	
	if (NULL != AVLFind(avl, &number2))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("element found when it shouldn't\n");
		printf("expected : NULL\nactual : %d\n\n", data);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("did not find missing element\n\n");
	
	AVLDestroy(avl);
}

void RemoveTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	
	AVLInsert(avl, &num6);
	AVLInsert(avl, &num2);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num7);
	AVLInsert(avl, &num8);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num9);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num11);
	
	printf(CYAN "REMOVE TEST\n" RESET_COLOR);
	
	TreePrint(avl->root, 0);
	AVLRemove(avl, &num6);
	if (NULL != AVLFind(avl, &num6))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("did not remove element\n");
		TreePrint(avl->root, 0);
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed 6th element successfully\n\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLRemove(avl, &num3);
	if (NULL != AVLFind(avl, &num3))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("did not remove element\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed 3rd element successfully\n\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLRemove(avl, &num5);
	if (NULL != AVLFind(avl, &num5))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("did not remove element\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed 5th element successfully\n\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLRemove(avl, &num8);
	if (NULL != AVLFind(avl, &num8))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("did not remove element\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed 8th element successfully\n\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLRemove(avl, &num10);
	if (NULL != AVLFind(avl, &num10))
	{
		printf(RED "---FAILED---\n" RESET_COLOR);
		printf("did not remove element\n");
		AVLDestroy(avl);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed 10th element successfully\n\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLDestroy(avl);
}

void AVLInsertTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	
	printf(CYAN "AVL INSERT TEST\n" RESET_COLOR);
	
	printf("insert 1\n");
	AVLInsert(avl, &num1);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 2\n");
	AVLInsert(avl, &num2);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 3\n");
	AVLInsert(avl, &num3);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 4\n");
	AVLInsert(avl, &num4);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 5\n");
	AVLInsert(avl, &num5);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 6\n");
	AVLInsert(avl, &num6);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 7\n");
	AVLInsert(avl, &num7);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 8\n");
	AVLInsert(avl, &num8);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("insert 9\n");
	AVLInsert(avl, &num9);
	TreePrint(avl->root, 0);
	
	printf("insert 10\n");
	AVLInsert(avl, &num10);
	printf("\n");
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLDestroy(avl);
}

void AVLRemoveTest(void)
{
	avl_t* avl = AVLCreate(CmpFunc);
	
	printf(CYAN "AVL REMOVE TEST\n" RESET_COLOR);
		
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num2);			
	AVLInsert(avl, &num9);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num6);
	AVLInsert(avl, &num11);
	AVLInsert(avl, &num7);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num8);
	
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("remove 5\n");
	AVLRemove(avl, &num5);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("remove 7 & 8\n");
	AVLRemove(avl, &num7);
	AVLRemove(avl, &num8);
	TreePrint(avl->root, 0);
	printf("\n");
	
	printf("remove 6\n");
	AVLRemove(avl, &num6);
	TreePrint(avl->root, 0);
	printf("\n");
	
	AVLDestroy(avl);
}

void ForEachTest(void)
{
	int num = 1;
	avl_t* avl = AVLCreate(CmpFunc);
	
	printf(CYAN "FOR EACH TEST\n" RESET_COLOR);
	AVLInsert(avl, &num4);
	AVLInsert(avl, &num2);			
	AVLInsert(avl, &num9);
	AVLInsert(avl, &num5);
	AVLInsert(avl, &num1);
	AVLInsert(avl, &num10);
	AVLInsert(avl, &num6);
	AVLInsert(avl, &num11);
	AVLInsert(avl, &num7);
	AVLInsert(avl, &num3);
	AVLInsert(avl, &num8);

	printf("avl tree\n\n");
	TreePrint(avl->root, 0);

	AVLForEach(avl, AddNum, &num, 0);
	
	printf("tree after adding 1 to each node\n\n");
	TreePrint(avl->root, 0);
	AVLDestroy(avl);
	
}

int main()
{
	printf("\n");
	InsertTest();
	CountTest();
	HeightTest();
	FindTest();
	RemoveTest();
	AVLInsertTest();
	AVLRemoveTest();
	ForEachTest();
	
	printf("\n");
	return 0;
}



