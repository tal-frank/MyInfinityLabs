
#include <stdio.h>

#include "binary_search_tree.h"

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

int CmpFunc(void* num1, void* num2)
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


void TreePrint(bst_iter_t root, int level)
{
	int i = 0;
        if (root == NULL)
        {
                return;
        }
        for (i = 0; i < level; i++)
        {
                printf(i == level - 1 ? "|-" : "  ");
        }
        printf("%d\n", *(int*)BSTGetData(root));
        TreePrint(GetBigChildForWhiteboxTest(root), level + 1);
        TreePrint(GetSmallChildForWhiteboxTest(root), level + 1);
}


void InsertTest(void)
{
	bst_t* bst = BSTCreate(CmpFunc);
	bst_iter_t iter= 0;
	
	printf(CYAN "IS EMPTY TEST\n" RESET_COLOR);
	if (!BSTIsEmpty(bst))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("tells not empty when empty\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty works\n\n");
	
	BSTInsert(bst, &num5);

	if (BSTIsEmpty(bst))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("tells empty when not empty\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("is empty works\n\n");
	
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num9);
	iter = BSTBegin(bst);
	printf("\n");
	
	
	printf(CYAN "INSERT TEST\n" RESET_COLOR);
	while (!BSTIsIterEqual(BSTNext(iter), BSTEnd(bst)))
	{
		printf(" %d ", *(int*)BSTGetData(iter));
		iter = BSTNext(iter);
		if (*(int*)BSTGetData(iter) < *(int*)BSTGetData(BSTPrev(iter)))
		{
			printf(RED "---FAIL---\n" RESET_COLOR);
			printf("didn't insert the right way or Next is not working good\n\n");
			BSTDestroy(bst);
			return;
		}
	}
	printf("\n");
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("inserted right and NEXT is working\n\n");
	printf("\n");
	
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	BSTDestroy(bst);

}

void FindTest(void)
{
	bst_t* bst = BSTCreate(CmpFunc);
	bst_iter_t iter= 0;
	
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num11);
	iter = BSTBegin(bst);
	printf("\n");
	
	while (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(" %d ", *(int*)BSTGetData(iter));
		iter = BSTNext(iter);
	}
	printf("\n\n");
	printf(CYAN "FIND TEST\n" RESET_COLOR);
	iter = BSTFind(bst, &num8);
	if (8 != *(int*)BSTGetData(iter))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't find the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found the right iter\n\n");
	
	iter = BSTFind(bst, &num5);
	if (5 != *(int*)BSTGetData(iter))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't find the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found the right iter\n\n");
	
	iter = BSTFind(bst, &num11);
	if (11 != *(int*)BSTGetData(iter))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't find the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found the right iter\n\n");
	
	iter = BSTFind(bst, &num6);
	if (6 != *(int*)BSTGetData(iter))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't find the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("found the right iter\n\n");
	
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	BSTDestroy(bst);
}

void RemoveTest(void)
{
	bst_t* bst = BSTCreate(CmpFunc);
	bst_iter_t iter= 0;
	
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num11);
	iter = BSTBegin(bst);
	printf("\n");
	printf(CYAN "REMOVE TEST\n" RESET_COLOR);
	printf("before remove:\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num7);
	BSTRemove(iter);
	printf("after remove 7:\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num7);
	if (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't remove the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed the right iter\n\n");
	
	iter = BSTFind(bst, &num10);
	BSTRemove(iter);
	printf("after remove 10:\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num10);
	if (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't remove the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed the right iter\n\n");
	
	iter = BSTFind(bst, &num4);
	BSTRemove(iter);
	printf("after remove 4 :\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num4);
	if (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't remove the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed the right iter\n\n");
	
	BSTInsert(bst, &num3);
	BSTInsert(bst, &num4);
	
	iter = BSTFind(bst, &num2);
	BSTRemove(iter);
	printf("after remove 2 :\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num2);
	if (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't remove the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed the right iter\n\n");
	
	iter = BSTFind(bst, &num6);
	BSTRemove(iter);
	printf("after remove 6 :\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter = BSTFind(bst, &num6);
	if (!BSTIsIterEqual(iter, BSTEnd(bst)))
	{
		printf(RED "---FAIL---\n" RESET_COLOR);
		printf("didn't remove the right iter\n\n");
		BSTDestroy(bst);
		return;
	}
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("removed the right iter\n\n");
	
	BSTDestroy(bst);
}

void PrevTest(void)
{
	bst_t* bst = BSTCreate(CmpFunc);
	bst_iter_t iter = 0;
	
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num4);
	BSTInsert(bst, &num2);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num7);
	BSTInsert(bst, &num10);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num11);
	iter = BSTEnd(bst);
	do
	{
		iter = BSTPrev(iter);
		printf(" %d ", *(int*)BSTGetData(iter));
	} while (!BSTIsIterEqual(iter, BSTBegin(bst)));
	
	BSTDestroy(bst);
}

void ForeachTest(void)
{
	bst_t* bst = BSTCreate(CmpFunc);
	bst_iter_t iter1 = 0;
	bst_iter_t iter2 = 0;
	bst_iter_t iter3 = 0;
	int arr[9] = {0};
	size_t i = 0;
	
	BSTInsert(bst, &num6);
	BSTInsert(bst, &num4);
	iter1 = BSTInsert(bst, &num2);
	BSTInsert(bst, &num1);
	BSTInsert(bst, &num8);
	BSTInsert(bst, &num7);
	iter2 = BSTInsert(bst, &num10);
	BSTInsert(bst, &num5);
	BSTInsert(bst, &num11);
	
	printf("\n");
	printf(CYAN "FOREACH TEST\n" RESET_COLOR);
	printf("before foreach :\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	iter3 = iter1;
	i = 0;
	while (!BSTIsIterEqual(iter3, iter2))
	{
		arr[i++] = *(int*)BSTGetData(iter3);
		iter3 = BSTNext(iter3);
	}
	
	BSTForEach(iter1, iter2, AddNum, &num1);
	printf("\nafter foreach :\n");
	TreePrint(GetSmallChildForWhiteboxTest(BSTEnd(bst)), 0);
	
	i = 0;
	while (!BSTIsIterEqual(iter1, iter2))
	{
		if ((arr[i++] + 1) != *(int*)BSTGetData(iter1))
		{
			printf("\n");
			printf(RED "---FAIL---\n" RESET_COLOR);
			printf("didn't act right\n");
			printf("expected : %d\nactual :%d\n", arr[i++] + 1, *(int*)BSTGetData(iter1));
			BSTDestroy(bst);
			return;
		}
		iter1 = BSTNext(iter1);
	}
	printf("\n");
	printf(GREEN "---PASSED---\n" RESET_COLOR);
	printf("acted as expected for each node\n\n");
	
	BSTDestroy(bst);
	
}

int main()
{
	printf("\n");
	InsertTest();
	FindTest();
	RemoveTest();
	PrevTest();
	ForeachTest();
	return 0;
}
