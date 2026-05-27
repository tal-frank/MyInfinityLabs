/**********************
* Binary Search Tree
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 25/05/2026
**********************/

#include <stdio.h> /* NULL */
#include <stdlib.h> /* malloc , free */
#include <assert.h> /* assert */

#include "binary_search_tree.h"

#define SUCCESS (1)
#define TRUE (1)
#define FALSE (0)

/*---------------------------------------------------------------------------*/
/********************************** STRUCTS **********************************/
/*---------------------------------------------------------------------------*/

enum
{
    SMALL = 0,
    BIG,
    NUM_OF_CHILDREN
};

typedef struct Tree_node tree_node_t;

struct Tree_node
{
    void* data;
    tree_node_t* parent;
    tree_node_t* children[NUM_OF_CHILDREN];
};

struct Binary_search_tree
{
    int (*cmp_func)(void* data, void* param);
    tree_node_t* end;
};

/*-------------------------------------------------------------------------------------------------*/
/********************************** STATIC FUNCTIONS DECLARATIONS **********************************/
/*-------------------------------------------------------------------------------------------------*/

static tree_node_t* IterToNode(bst_iter_t iter);
static bst_iter_t NodeToIter(tree_node_t* tnode);
static tree_node_t* GetParent(tree_node_t* tnode);
static tree_node_t* GetBigChild(tree_node_t* tnode);
static tree_node_t* GetSmallChild(tree_node_t* tnode);
static void SetParent(tree_node_t* new_tnode, tree_node_t* tnode);
static void SetBigChild(tree_node_t* tnode, tree_node_t* new_tnode);
static void SetSmallChild(tree_node_t* tnode, tree_node_t* new_tnode);
static void SetData(tree_node_t* tnode, void* data);
static int IsLeaf(tree_node_t* tnode);
static void RemoveNodeWithOneChild(tree_node_t* tnode);
static void RemoveLeaf(tree_node_t* tnode);

/*------------------------------------------------------------------------------------*/
/********************************** CREATE & DESTROY **********************************/
/*------------------------------------------------------------------------------------*/

bst_t* BSTCreate(int (*cmp_func)(void* data, void* param))
{
	bst_t* bst = (bst_t*)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return NULL;
	}
	
	assert (NULL != cmp_func);
	
	bst->end = (tree_node_t*)malloc(sizeof(tree_node_t));
	if (NULL == bst->end)
	{
		free(bst);
		bst = NULL;
		return NULL;
	}
	bst->cmp_func = cmp_func;
	bst->end->data = NULL;
	bst->end->parent = NULL;
	bst->end->children[0] = NULL;
	bst->end->children[1] = NULL;
	
	return bst;
}

void BSTDestroy(bst_t* bst)
{
	tree_node_t* node_to_destroy = NULL;
	tree_node_t* node = IterToNode(BSTBegin(bst));
	int child_index = 0;
	
	while(!BSTIsIterEqual(NodeToIter(node), bst->end))
	{
		while (!IsLeaf(node))
		{
			child_index = (NULL != GetSmallChild(node)) ? SMALL : BIG;
			node = node->children[child_index];
		}
		
		node_to_destroy = node;
		node = GetParent(node);
		child_index = (NULL != node->children[SMALL]) ? SMALL : BIG;
		node->children[child_index] = NULL;
		free(node_to_destroy);
		node_to_destroy = NULL;
	}
	
	free(node);
	node = NULL;
	free(bst);
	bst = NULL;
}

/*-----------------------------------------------------------------------------------*/
/********************************** INSERT & REMOVE **********************************/
/*-----------------------------------------------------------------------------------*/


bst_iter_t BSTInsert(bst_t* bst, void* data)
{
	int is_inserted = FALSE;
	int child_index = 0;
	tree_node_t* curr_tnode = bst->end;
	tree_node_t* new_tnode = (tree_node_t*)malloc(sizeof(tree_node_t));
	
	assert(NULL != bst);
	
	if (NULL == new_tnode)
	{
		return BSTEnd(bst);
	}
	new_tnode->data = data;
	SetBigChild(new_tnode, NULL);
	SetSmallChild(new_tnode, NULL);
		
	if (BSTIsEmpty(bst))
	{
		SetSmallChild(curr_tnode, new_tnode);
		SetParent(new_tnode, curr_tnode);
		is_inserted = TRUE;
	}
	curr_tnode = GetSmallChild(curr_tnode);
	while (!is_inserted)
	{
		assert(0 != bst->cmp_func(BSTGetData(NodeToIter(new_tnode)), NodeToIter(BSTGetData(curr_tnode))));
		
		child_index = 
			(0 < bst->cmp_func(BSTGetData(NodeToIter(new_tnode)), BSTGetData(NodeToIter(curr_tnode)))) ? 
				BIG : SMALL;
		if (NULL != curr_tnode->children[child_index])
		{
			curr_tnode = curr_tnode->children[child_index];
			continue;
		}
		curr_tnode->children[child_index] = new_tnode;
		SetParent(new_tnode, curr_tnode);
		is_inserted = TRUE;
		
	}
	
	return NodeToIter(new_tnode);
}

void BSTRemove(bst_iter_t iter)
{
	tree_node_t* tnode_to_remove = IterToNode(iter);
	tree_node_t* next_tnode = NULL;
		
	if (NULL != GetBigChild(tnode_to_remove) && NULL != GetSmallChild(tnode_to_remove))
	{
		next_tnode = IterToNode(BSTNext(iter));
		SetData(tnode_to_remove, BSTGetData(NodeToIter(next_tnode)));
		tnode_to_remove = next_tnode;
	}
	
	if (IsLeaf(tnode_to_remove))
	{
		RemoveLeaf(tnode_to_remove);
		tnode_to_remove = NULL;
		return;
	}
	
	RemoveNodeWithOneChild(tnode_to_remove);
}

/*-------------------------------------------------------------------------------*/
/********************************** END & BEGIN **********************************/
/*-------------------------------------------------------------------------------*/

bst_iter_t BSTEnd(const bst_t* bst)
{
	assert(NULL != bst);	
	
	return NodeToIter(bst->end);
}

bst_iter_t BSTBegin(const bst_t* bst)
{
	tree_node_t* tnode = bst->end;
	
	assert(NULL != bst);
	
	while (NULL != GetSmallChild(tnode))
	{
		tnode = GetSmallChild(tnode);
	}
	
	return NodeToIter(tnode);
}

/*------------------------------------------------------------------------------------------*/
/********************************** NEXT & PREV & GET DATA **********************************/
/*------------------------------------------------------------------------------------------*/

bst_iter_t BSTNext(bst_iter_t iter)
{
	tree_node_t* tnode = IterToNode(iter);
	
	if (NULL == GetBigChild(tnode))
	{
		while(NULL != GetParent(tnode) && tnode != GetSmallChild(GetParent(tnode)))
		{
			tnode = GetParent(tnode);
		}
		return GetParent(tnode);
	}
	
	tnode = GetBigChild(tnode);
	while(NULL != GetSmallChild(tnode))
	{
		tnode = GetSmallChild(tnode);
	}
	
	return NodeToIter(tnode);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	tree_node_t* tnode = IterToNode(iter);
	
	if (NULL == GetSmallChild(tnode))
	{
		while(NULL != GetParent(tnode) && tnode != GetBigChild(GetParent(tnode)))
		{
			tnode = GetParent(tnode);
		}
		return GetParent(tnode);
	}
	
	tnode = GetSmallChild(tnode);
	while(NULL != GetBigChild(tnode))
	{
		tnode = GetBigChild(tnode);
	}
	
	return NodeToIter(tnode);
}

void* BSTGetData(bst_iter_t iter)
{
	tree_node_t* tnode = IterToNode(iter);
	
	return tnode->data;
}

/*--------------------------------------------------------------------------------------------*/
/********************************** IS EMPTY & ITER IS EQUAL **********************************/
/*--------------------------------------------------------------------------------------------*/

int BSTIsEmpty(const bst_t* bst)
{
	assert(NULL != bst);

	return NULL == GetSmallChild(bst->end);
}

int BSTIsIterEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return iter1 == iter2;
}

/*-------------------------------------------------------------------------*/
/********************************** COUNT **********************************/
/*-------------------------------------------------------------------------*/

size_t BSTCount(const bst_t* bst)
{
	size_t cnt = 0;
	bst_iter_t iter = BSTBegin(bst);
	
	assert(NULL != bst);
	
	while(NULL != BSTNext(iter))
	{
		iter = BSTNext(iter);
		++cnt;
	}
	
	return cnt;
}

/*-----------------------------------------------------------------------------------*/
/********************************** FIND & FOR EACH **********************************/
/*-----------------------------------------------------------------------------------*/

bst_iter_t BSTFind(const bst_t* bst, void* param)
{
	tree_node_t* tnode = GetSmallChild(bst->end);
	int node_cmp = bst->cmp_func(BSTGetData(NodeToIter(tnode)), param);
	int child_index = 0;
	
	assert(NULL != bst);
	
	while (0 != node_cmp && NULL != tnode)
	{
		child_index = (node_cmp > 0) ? SMALL : BIG;
		if (NULL == tnode->children[child_index])
		{
			return BSTEnd(bst);
		}
		tnode = tnode->children[child_index];
		
		node_cmp = bst->cmp_func(BSTGetData(NodeToIter(tnode)), param);		
	}
	
	if (NULL == tnode)
	{
		return BSTEnd(bst);
	}
	return NodeToIter(tnode);
}

int BSTForEach(bst_iter_t from,
               bst_iter_t to,
               int (*act_func)(void* data, void* param),
               void* param)
{
	int is_success = SUCCESS;
	int cnt = 0;
	
	while (!BSTIsIterEqual(from, to) && SUCCESS == is_success)
	{
		is_success = act_func(BSTGetData(from), param);
		from = BSTNext(from);
		++cnt;
	}
	return cnt;
}

/*------------------------------------------------------------------------------------*/
/********************************** STATIC FUNCTIONS **********************************/
/*------------------------------------------------------------------------------------*/

static void RemoveLeaf(tree_node_t* tnode)
{
	tree_node_t* parent = GetParent(tnode);
	int child_index = BSTIsIterEqual(NodeToIter(parent->children[SMALL]), NodeToIter(tnode)) ? SMALL : BIG;
	parent->children[child_index] = NULL;
	free(tnode);
	tnode = NULL;
	return;
}

static void RemoveNodeWithOneChild(tree_node_t* tnode)
{
	tree_node_t* child = NULL;
	int child_index = (NULL != GetSmallChild(tnode)) ? SMALL : BIG;
	
	child = tnode->children[child_index];

	SetData(tnode, BSTGetData(NodeToIter(child)));
	tnode->children[BIG] = GetBigChild(child);
	tnode->children[SMALL] = GetSmallChild(child);
	SetParent(child, GetParent(tnode));
		
	free(child);
	child = NULL;
}
           
static tree_node_t* GetParent(tree_node_t* tnode)
{
	return tnode->parent;
}
    
static tree_node_t* GetBigChild(tree_node_t* tnode)
{
	return tnode->children[BIG];
}
      
static tree_node_t* GetSmallChild(tree_node_t* tnode)
{
	return tnode->children[SMALL];
}      
  
static void SetParent(tree_node_t* new_tnode, tree_node_t* tnode)
{
	new_tnode->parent = tnode;
}
         
static void SetBigChild(tree_node_t* tnode, tree_node_t* new_tnode)
{
	tnode->children[BIG] = new_tnode;
}
      
static void SetSmallChild(tree_node_t* tnode, tree_node_t* new_tnode)
{
	tnode->children[SMALL] = new_tnode;
}

static void SetData(tree_node_t* tnode, void* data)
{
	tnode->data = data;
}

static tree_node_t* IterToNode(bst_iter_t iter)
{
	return (tree_node_t*)iter;
}

static bst_iter_t NodeToIter(tree_node_t* tnode)
{
	return (bst_iter_t)tnode;
}

static int IsLeaf(tree_node_t* tnode)
{
	return (NULL == GetSmallChild(tnode)) && (NULL == GetBigChild(tnode));
}





/********************************** SECTION ONLY FOR TESTS **********************************/
bst_iter_t GetBigChildForWhiteboxTest(bst_iter_t iter)
{
	tree_node_t* tnode = IterToNode(iter);
	tnode = tnode->children[BIG];
	return NodeToIter(tnode);
}

bst_iter_t GetSmallChildForWhiteboxTest(bst_iter_t iter)
{
	tree_node_t* tnode = IterToNode(iter);
	tnode = tnode->children[SMALL];
	return NodeToIter(tnode);
} 
/********************************** SECTION ONLY FOR TESTS **********************************/


