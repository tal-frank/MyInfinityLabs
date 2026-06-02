/**********************
* sorted list
* Author: Tal Frank
* Reviewer: Or Zelner
* Last update: 11/06/2026
**********************/

#include <stdlib.h> /* malloc , free */
#include <stdio.h> /* printf for test only*/
#include <assert.h> /* assert */

#include "avl_recursive_tree.h"
#define TRUE (1)
#define FALSE (0)

enum
{
	SUCCESS,
	FAILURE	
};

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

/*-----------------------------------------------------------------------------------------*/
/****************************** STATIC FUNCTIONS DECLARATIONS ******************************/
/*-----------------------------------------------------------------------------------------*/

static void DestroyAllNodes(avl_node_t* root);
static size_t CountAllNodes(avl_node_t* root);
static void* FindElement(const avl_t* avl, avl_node_t* root, const void* data);
static int InsertElement(avl_t* avl, avl_node_t* root, avl_node_t* new_nod);
static void UpdateHeight(avl_node_t* root);
static avl_node_t* CreateNode(void* data);
static int GetNodeHeight(avl_node_t* node);
static void Remove(avl_node_t** node);
static void FindRemove(avl_t* avl, avl_node_t* node, avl_node_t* parent, const void* data);
static avl_node_t* FindSuccessor(avl_node_t* node, avl_node_t* parent);
static int IsLeaf(avl_node_t* node);
static avl_node_t* RotateLeft(avl_node_t** node);
static avl_node_t* RotateRight(avl_node_t** node);
static avl_node_t* Balance(avl_node_t** node);
static int BalanceFactor(avl_node_t* node);
static int ActForEachAllNodesPostOrder(int (*act_func)(void* data, void* param), 
				        avl_node_t* root, 
				        void* param);
static int ActForEachAllNodesPreOrder(int (*act_func)(void* data, void* param), 
				       avl_node_t* root, 
				       void* param);
static int ActForEachAllNodesInOrder(int (*act_func)(void* data, void* param), 
				      avl_node_t* root, 
				      void* param);

/*----------------------------------------------------------------------------*/
/****************************** CREATE & DESTROY ******************************/
/*----------------------------------------------------------------------------*/

avl_t* AVLCreate(int (*cmp_func)(const void* data, const void* tree_data))
{
	avl_t* avl = (avl_t*)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->cmp_func = cmp_func;
	avl->root = NULL;
	
	return avl;
}

void AVLDestroy(avl_t* avl)
{
	DestroyAllNodes(avl->root);
	free(avl);
}

/*---------------------------------------------------------------------------*/
/****************************** INSERT & REMOVE ******************************/
/*---------------------------------------------------------------------------*/

int AVLInsert(avl_t* avl, void* data)
{
	int status = SUCCESS;
	
	avl_node_t* new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return FAILURE;
	}
	
	if (NULL == avl->root)
	{
		avl->root = new_node;
		return SUCCESS;
	}
	
	status = InsertElement(avl, avl->root, new_node);
	avl->root = Balance(&avl->root);
	
	return status;
}


void AVLRemove(avl_t* avl, const void* data)
{
	int cmp = 0;
	int side = 0;
	
	assert(NULL != avl);
	
	if (NULL != avl->root)
	{
		cmp = avl->cmp_func(data, avl->root->data);
		 
		if (0 == cmp)
		{
			if (!IsLeaf(avl->root))
			{
				Remove(&avl->root);
				avl->root = Balance(&avl->root);
			}
			else
			{
				free(avl->root);
				avl->root = NULL;
			}
		}
		else
		{
			side = (0 > cmp) ? LEFT : RIGHT;
			FindRemove(avl, avl->root->children[side], avl->root, data);
			avl->root = Balance(&avl->root);
		}
	}
}

/*-------------------------------------------------------------------------------------*/
/****************************** COUNT & IS EMPTY & HEIGHT ******************************/
/*-------------------------------------------------------------------------------------*/

size_t AVLHeight(const avl_t* avl)
{
	if (AVLIsEmpty(avl))
	{
		return 0;
	}
	return avl->root->height;
}

size_t AVLCount(const avl_t* avl)
{
	return CountAllNodes(avl->root);
}

int AVLIsEmpty(const avl_t* avl)
{
	return NULL == avl->root;
}

/*---------------------------------------------------------------------------*/
/****************************** FIND & FOR EACH ******************************/
/*---------------------------------------------------------------------------*/

void* AVLFind(const avl_t* avl, const void* data)
{
	if (NULL == avl->root)
	{
		return NULL;
	}
	return FindElement(avl, avl->root, data);
}

int AVLForEach(avl_t* avl, 
               int (*act_func)(void* data, void* param),
               void* param,
               traversal_t traversal_type)
{
	if (PREORDER == traversal_type)
	{
		return ActForEachAllNodesPreOrder(act_func, avl->root, param);
	}
	else if (INORDER == traversal_type)
	{
		return ActForEachAllNodesInOrder(act_func, avl->root, param);
	}
	else
	{
		return ActForEachAllNodesPostOrder(act_func, avl->root, param);
	}
}

/*---------------------------------------------------------------------------------------*/
/****************************** MULTIFIND & REMOVE MULTIPLE ******************************/
/*---------------------------------------------------------------------------------------*/

int AVLMultiFind(const avl_t* avl, const void* data);


void AVLRemoveMultiple(avl_t* avl, const void* data); 

/*----------------------------------------------------------------------------*/
/****************************** STATIC FUNCTIONS ******************************/
/*----------------------------------------------------------------------------*/


static int GetNodeHeight(avl_node_t* node)
{
	if (NULL == node)
	{
		return 0;
	}
	
	return node->height;
}

static size_t CountAllNodes(avl_node_t* root)
{
	if (NULL == root)
	{
		return 0;
	}
	
	return CountAllNodes(root->children[LEFT]) + 
	       CountAllNodes(root->children[RIGHT]) + 1;
}

static void DestroyAllNodes(avl_node_t* root)
{
	if (NULL == root)
	{
		return;
	}
	DestroyAllNodes(root->children[LEFT]);
	DestroyAllNodes(root->children[RIGHT]);
	free(root);
	root = NULL;
}

static void* FindElement(const avl_t* avl, avl_node_t* root, const void* data)
{
	int cmp = 0;
	int side = 0;
	
	if (NULL == root)
	{
		return NULL;
	}
	
	cmp = avl->cmp_func(data, root->data);
	side = (0 > cmp) ? LEFT : RIGHT;
	
	if (0 == cmp)
	{
		return root->data;
	}
	
	return FindElement(avl, root->children[side], data);
}

static avl_node_t* CreateNode(void* data)
{
	avl_node_t* new_node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->height = 1;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	return new_node;
}

static void UpdateHeight(avl_node_t* root)
{
	root->height = GetNodeHeight(root->children[LEFT]) > GetNodeHeight(root->children[RIGHT]) ? 
		       GetNodeHeight(root->children[LEFT]) + 1 : GetNodeHeight(root->children[RIGHT]) + 1;
}

static int ActForEachAllNodesPostOrder(int (*act_func)(void* data, void* param), 
					avl_node_t* root, 
					void* param)
{
	int status = SUCCESS;
	if (NULL == root)
	{
		return SUCCESS;
	}
	ActForEachAllNodesPostOrder(act_func, root->children[LEFT], param);
	ActForEachAllNodesPostOrder(act_func, root->children[RIGHT], param);
	status = act_func(root->data, param);
	
	return status;
}

static int ActForEachAllNodesPreOrder(int (*act_func)(void* data, void* param), 
				       avl_node_t* root, 
				       void* param)
{
	int status = SUCCESS;
	if (NULL == root)
	{
		return SUCCESS;
	}
	status = act_func(root->data, param);
	ActForEachAllNodesPreOrder(act_func, root->children[LEFT], param);
	ActForEachAllNodesPreOrder(act_func, root->children[RIGHT], param);
	
	return status;
}

static int ActForEachAllNodesInOrder(int (*act_func)(void* data, void* param), 
				      avl_node_t* root, 
				      void* param)
{
	int status = SUCCESS;
	if (NULL == root)
	{
		return SUCCESS;
	}
	ActForEachAllNodesInOrder(act_func, root->children[LEFT], param);
	status = act_func(root->data, param);
	ActForEachAllNodesInOrder(act_func, root->children[RIGHT], param);
	
	return status;
}

static int InsertElement(avl_t* avl, avl_node_t* root, avl_node_t* new_node)
{
	int status = SUCCESS;
	int cmp = 0;
	int side = 0;
	
	cmp = avl->cmp_func(new_node->data, root->data);
	side = (0 > cmp) ? LEFT : RIGHT;
	
	assert(0 != cmp);
	
	if (NULL == root->children[side])
	{
		root->children[side] = new_node;
		UpdateHeight(root);
		return SUCCESS;
	}
	
	status = InsertElement(avl, root->children[side], new_node);	
	
	root->children[side] = Balance(&root->children[side]);
	
	return status;
}

static int IsLeaf(avl_node_t* node)
{
	if (NULL == node->children[RIGHT] && NULL == node->children[LEFT])
	{
		return TRUE;
	}
	return FALSE;
}

static void FindRemove(avl_t* avl, avl_node_t* node, avl_node_t* parent, const void* data)
{
	int cmp = avl->cmp_func(data, node->data);
	int side = (0 > cmp) ? LEFT : RIGHT;

	if (0 == cmp)
	{
		side = (node == parent->children[LEFT]) ? LEFT : RIGHT;
		Remove(&parent->children[side]);
	}
	else
	{
		FindRemove(avl, node->children[side], node, data);
		side = (node == parent->children[side]) ? side : !side;
		parent->children[side] = Balance(&parent->children[side]);
	}
}

static void Remove(avl_node_t** node)
{
	int side = 0;
	avl_node_t* successor = NULL;
	
	if (IsLeaf(*node))
	{
		free(*node);
		*node = NULL;
		return;
	}
	else if (NULL == (*node)->children[RIGHT])
	{
		successor = (*node)->children[LEFT];
		**node = *successor;
		free(successor);
		successor = NULL;
	}
	else
	{
		successor = FindSuccessor((*node)->children[RIGHT], (*node));
		if (successor == (*node)->children[RIGHT])
		{
			(*node)->children[RIGHT] = successor->children[RIGHT];	
		}
		
		(*node)->data = successor->data;
		free(successor);
		successor = NULL;
	}
	
	UpdateHeight(*node);
}

static avl_node_t* FindSuccessor(avl_node_t* node, avl_node_t* parent)
{
	avl_node_t* successor = NULL;
	
	if (NULL == node->children[LEFT])
	{
		if (node == parent->children[LEFT])
		{
			parent->children[LEFT] = node->children[RIGHT];
		}
		return node;
	}
	
	successor = FindSuccessor(node->children[LEFT], node);
	parent->children[LEFT] = Balance(&parent->children[LEFT]);
	
	return successor;
}

static int BalanceFactor(avl_node_t* node)
{
	int left_weight = NULL != node->children[LEFT] 
			? node->children[LEFT]->height : 0;
			
	int right_weight = NULL != node->children[RIGHT] 
			 ? node->children[RIGHT]->height : 0;	
			 
	return left_weight - right_weight;
}

static avl_node_t* Balance(avl_node_t** node)
{
	int balance_factor = BalanceFactor(*node);
	
	if (NULL == node || NULL == *node)
	{
		return NULL;
	}
	
	if (1 < balance_factor)
	{
		if (0 > BalanceFactor((*node)->children[LEFT]))
		{
			(*node)->children[LEFT] = RotateLeft(&((*node)->children[LEFT]));
		}
		*node = RotateRight(node);
	}
	else if (-1 > balance_factor)
	{
		if (0 < BalanceFactor((*node)->children[RIGHT]))
		{
			(*node)->children[RIGHT] = RotateRight(&((*node)->children[RIGHT]));
		}
		*node = RotateLeft(node);
	}
	else
	{
		UpdateHeight(*node);
	}
	
	return *node;
}

static avl_node_t* RotateRight(avl_node_t** node)
{
	avl_node_t* new_root = (*node)->children[LEFT];
	avl_node_t* right_child = new_root->children[RIGHT];
	
	new_root->children[RIGHT] = *node;
	(*node)->children[LEFT] = right_child;
	
	UpdateHeight(*node);
	UpdateHeight(new_root);
	
	return new_root;
}

static avl_node_t* RotateLeft(avl_node_t** node)
{
	avl_node_t* new_root = (*node)->children[RIGHT];
	avl_node_t* left_child = new_root->children[LEFT];
	
	new_root->children[LEFT] = *node;
	(*node)->children[RIGHT] = left_child;
	
	UpdateHeight(*node);
	UpdateHeight(new_root);
	
	return new_root;
}


