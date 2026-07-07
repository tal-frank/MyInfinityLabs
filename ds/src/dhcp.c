#include <stdlib.h> /* malloc , free */
#include <string.h> /* memcpy , memset*/
#include <stdio.h>

#include "dhcp.h" /* dhcp API */

#define CHAR_BIT_SIZE (8)
#define BITS_IN_NET (CHAR_BIT_SIZE * BYTES_IN_IP)

/*-----------------------------------------------------------------*/
/************************* STRUCTS & ENUMS *************************/
/*-----------------------------------------------------------------*/

enum allocation_status
{
    NOT_ALLOCATED = 0,
    ALLOCATED
};

enum node_direction
{
    ZERO = 0,
    ONE = 1, 
    IS_BIT_ON
};

typedef struct trie_node trie_node_t;

struct trie_node
{
    int is_allocated;
    trie_node_t* children[IS_BIT_ON];
};

typedef struct trie
{
    trie_node_t* root;
}trie_t;

struct Dhcp
{
    size_t num_of_bits_in_subnet;
    const unsigned char subnet[BYTES_IN_IP];
    trie_t* trie;
};

/*-------------------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS DECLERATIONS *************************/
/*-------------------------------------------------------------------------------*/

static trie_t* TrieCreate(void);
static void TrieDestroy(trie_t* trie);
static void TrieDestroyRec(trie_t* trie, trie_node_t* node);
static size_t TrieCountAllocated(trie_node_t* node, int trie_depth);
static size_t IntPow(int num, int pow);
static trie_node_t* CreateNode(void);
static size_t InitBitIndex(dhcp_t* dhcp);
static size_t InitByteIndex(dhcp_t* dhcp);
static void UpdateAllocation(trie_node_t* node_to_allocate);

static dhcp_status_t TrieFree(trie_node_t* node, 
                              unsigned char ip_arr[], 
                              int size, 
                              int bit);

static dhcp_status_t TrieInsert(trie_node_t* node, 
                                unsigned char ip_arr[], 
                                int size, 
                                int bit, 
                                unsigned char result_ip[BYTES_IN_IP]);

/*------------------------------------------------------------------*/
/************************* CREATE & DESTROY *************************/
/*------------------------------------------------------------------*/

dhcp_t* DHCPCreate(const unsigned char subnet[BYTES_IN_IP], size_t num_of_bits_in_subnet)
{
    unsigned char network_address[BYTES_IN_IP] = {0};
    unsigned char server_address[BYTES_IN_IP] = {255, 255, 255, 254};
    unsigned char broadcast_address[BYTES_IN_IP] = {255, 255, 255, 255};
    size_t bytes = 0;
    size_t bits = 0;

    dhcp_t* dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));
    if (NULL == dhcp)
    {
        return NULL;
    }

    dhcp->trie = TrieCreate();
    memcpy((char*)dhcp->subnet, subnet, BYTES_IN_IP);
    dhcp->num_of_bits_in_subnet = num_of_bits_in_subnet;

    bytes = InitByteIndex(dhcp);
    bits = InitBitIndex(dhcp);

    TrieInsert(dhcp->trie->root, 
               network_address, 
               bytes, 
               bits, 
               network_address);

               printf("\n\n\n");
               
    TrieInsert(dhcp->trie->root, 
               server_address, 
               bytes, 
               bits, 
               server_address);

               printf("\n\n\n");
               
    TrieInsert(dhcp->trie->root, 
               broadcast_address, 
               bytes, 
               bits, 
               broadcast_address);

               printf("\n\n\n");
    
    return dhcp;
}

void DHCPDestroy(dhcp_t* dhcp)
{
    TrieDestroy(dhcp->trie);
    dhcp->trie = NULL;
    free(dhcp);
    dhcp = NULL;
}

/*--------------------------------------------------------------*/
/************************* ALLOC & FREE *************************/
/*--------------------------------------------------------------*/

dhcp_status_t DHCPAllocIP(dhcp_t* dhcp,
                          const unsigned char request_ip[BYTES_IN_IP],
                          unsigned char result_ip[BYTES_IN_IP])
{
    dhcp_status_t status = SUCCESS;
    unsigned char initial_ip[BYTES_IN_IP] = {0};
    size_t bytes = InitByteIndex(dhcp);
    size_t bits = InitBitIndex(dhcp);
    
    memcpy(result_ip, dhcp->subnet, BYTES_IN_IP);

    status = TrieInsert(dhcp->trie->root, 
                        (unsigned char*)request_ip, 
                        bytes, 
                        bits, 
                        result_ip);
    if (IP_NOT_AVAILABLE_ERROR == status)
    {
        memcpy(result_ip, dhcp->subnet, BYTES_IN_IP);
        printf("check if entered\n\n\n");
        status = TrieInsert(dhcp->trie->root, 
                            initial_ip, 
                            bytes, 
                            bits, 
                            result_ip);
    }

    return status;
}

dhcp_status_t DHCPFreeIP(dhcp_t* dhcp, const unsigned char ip_to_free[BYTES_IN_IP])
{
    size_t bytes = InitByteIndex(dhcp);
    size_t bits = InitBitIndex(dhcp);
    
    return TrieFree(dhcp->trie->root, (unsigned char*)ip_to_free, bytes, bits);
}

/*------------------------------------------------------------*/
/************************* COUNT FREE *************************/
/*------------------------------------------------------------*/

size_t DHCPCountFree(const dhcp_t* dhcp)
{
    size_t host_bits = BITS_IN_NET - dhcp->num_of_bits_in_subnet;
    size_t num_allocated = TrieCountAllocated(dhcp->trie->root, host_bits + 1);
    return IntPow(2, host_bits) - num_allocated - 1; 
}

/*----------------------------------------------------------------*/
/************************* TRIE FUNCTIONS *************************/
/*----------------------------------------------------------------*/

static trie_t* TrieCreate(void)
{
    trie_t* trie = (trie_t*)malloc(sizeof(trie_t));
    if (NULL == trie)
    {
        return NULL;
    }

    trie->root = (trie_node_t*)malloc(sizeof(trie_node_t));
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;
        return NULL;
    }

    trie->root->children[ZERO] = NULL;
    trie->root->children[ONE] = NULL;
    trie->root->is_allocated = 0;
    
    return trie;
}

static dhcp_status_t TrieInsert(trie_node_t* node, 
                                unsigned char ip_arr[], 
                                int bytes, 
                                int bits, 
                                unsigned char result_ip[BYTES_IN_IP])
{
    dhcp_status_t status = SUCCESS;
    char mask = 1 << bits;
    unsigned int path = !!(ip_arr[bytes] & mask);
    unsigned char init_ip[BYTES_IN_IP] = {0};
    trie_node_t* next_node = NULL;

    if ((0 > bits) && (BYTES_IN_IP - 1 == bytes))
    {
        if (ALLOCATED == node->is_allocated)
        {
            return IP_NOT_AVAILABLE_ERROR;
        }
        /*
        (0 == path) ? (result_ip[bytes] &= ~mask) : 
                      (result_ip[bytes] |= mask);
        */
        node->is_allocated = ALLOCATED;
        return SUCCESS;
    }

    if (NULL == node->children[path])
    {
        node->children[path] = CreateNode();
        if (NULL == node)
        {
            return MEMORY_ERROR;
        }
    }
    
    next_node = node->children[path];
    (0 > bits) ? (bits = CHAR_BIT_SIZE - 1 , ++bytes) : (--bits);
    status = TrieInsert(next_node, ip_arr, bytes, bits, result_ip);
    /*
    if (0 > bits)
    {
        status = TrieInsert(next_node, ip_arr, bytes + 1, CHAR_BIT_SIZE - 1, result_ip);
    }
    else
    {
        status = TrieInsert(next_node, ip_arr, bytes, bits - 1, result_ip);
    }
    */

/*
    printf("status1 = %d , bit = %d, byte = %d, path = %d\n", status, bits, bytes, path);
*/
    
    if (SUCCESS == status)
    {    
        (0 == path) ? (result_ip[bytes] &= ~mask) : 
                      (result_ip[bytes] |= mask);   
        UpdateAllocation(node);
    }

    else if (IP_NOT_AVAILABLE_ERROR == status)
    {
        if (NULL == node->children[ONE])
        {
            node->children[ONE] = CreateNode();
            if (NULL == node)
            {
                return MEMORY_ERROR;
            }
        }
        if ((0 == path) && 
            (NOT_ALLOCATED == node->children[ONE]->is_allocated))
        {
            result_ip[bytes] |= mask;
            path = 1;
            status = TrieInsert(node->children[ONE], 
                                result_ip, 
                                bytes, 
                                bits, 
                                result_ip);
            /*
            printf("status2 = %d , bit = %d, byte = %d path = %d\n", status, bits, bytes, path);
            */
        }
        else
        {
            return IP_NOT_AVAILABLE_ERROR;
        }
    }
/*
    printf("status3 = %d , bit = %d, byte = %d, path = %d\n", status, bits, bytes, path);
*/
    return status;
}

static dhcp_status_t TrieFree(trie_node_t* node, 
                              unsigned char ip_arr[], 
                              int bytes, 
                              int bits)
{
    dhcp_status_t status = SUCCESS;
    char mask = 1 << bits;
    unsigned int path = !!(ip_arr[bytes] & mask);

    trie_node_t* next_node = node->children[path];
    
    if ((BYTES_IN_IP - 1 == bytes) && (0 > bits))
    {
        node->is_allocated = NOT_ALLOCATED;
        return SUCCESS;
    }
    if (NULL == next_node)
    {
        return IP_NOT_ALLOCATED_ERROR;
    }

    (0 > bits) ? (bits = (CHAR_BIT_SIZE - 1) , ++bytes) : (--bits);

    status = TrieFree(next_node, ip_arr, bytes, bits);
    node->is_allocated = NOT_ALLOCATED;

    return status;
}

static void TrieDestroy(trie_t* trie)
{
    TrieDestroyRec(trie, trie->root);
    free(trie);
    trie = NULL;
}

static void TrieDestroyRec(trie_t* trie, trie_node_t* node)
{
    if (NULL == node)
    {
        return;
    }

    TrieDestroyRec(trie, node->children[ZERO]);
    TrieDestroyRec(trie, node->children[ONE]);
    free(node);
}

static size_t TrieCountAllocated(trie_node_t* node, int trie_depth)
{    
    if (NULL == node)
    {
        return 0;
    }
    if (ALLOCATED == node->is_allocated)
    {
        return (IntPow(2, trie_depth));
    }

    return TrieCountAllocated(node->children[ZERO], trie_depth - 1) +
           TrieCountAllocated(node->children[ONE], trie_depth - 1);
}

/*------------------------------------------------------------------*/
/************************* STATIC FUNCTIONS *************************/
/*------------------------------------------------------------------*/

static size_t IntPow(int num, int pow)
{
    int i = 0;
    size_t result = 1;
    
    for(i = 0; i < pow; ++i)
    {
        result *= num;
    }

    return result;
}

static trie_node_t* CreateNode(void)
{
    trie_node_t* new_node = (trie_node_t*)malloc(sizeof(trie_node_t));
    new_node->children[ZERO] = NULL;
    new_node->children[ONE] = NULL;
    new_node->is_allocated = NOT_ALLOCATED;

    return new_node;
}

static size_t InitBitIndex(dhcp_t* dhcp)
{
    return (BITS_IN_NET - (dhcp->num_of_bits_in_subnet + 1)) % 
            CHAR_BIT_SIZE;
}

static size_t InitByteIndex(dhcp_t* dhcp)
{
    return BYTES_IN_IP - 
           (BITS_IN_NET - (dhcp->num_of_bits_in_subnet + 1)) / CHAR_BIT_SIZE - 1;
}

static void UpdateAllocation(trie_node_t* node_to_allocate)
{
    if (NULL != node_to_allocate->children[ZERO] &&
        NULL != node_to_allocate->children[ONE] &&
        ALLOCATED == node_to_allocate->children[ZERO]->is_allocated &&
        ALLOCATED == node_to_allocate->children[ONE]->is_allocated)
    {
        node_to_allocate->is_allocated = ALLOCATED;
    }
}
/*
static dhcp_status_t RecAllocIP(trie_node_t node, unsigned char requested[BYTES_IN_IP], unsigned char result[BYTES_IN_IP], size_t hight, size_t host_size)
{
    const unsigned char min_ip[BYTES_IN_IP] = {0};
    int side = getside(requested, hight, host_size);
    if (1 == hight)
    {
        node->is_allocated = ALLOCATED;
        return SUCCESS;
    }

    if (LEFT == side && IsTaken(node->chidren[side]))
    {
        side = RIGHT;
        requested = min_ip;
    }
    if (RIGHT == side && IsTaken(node->chidren[side]))
    {
        return IP_NOT_AVAILABLE_ERROR;
    }
    
    status = RecAllocIP(node->children[side], requested, result, hight - 1, host_size);

    if (SUCCESS == status)
    {
        UpdateIsAllocated(node);
    }
    else 
    {
        if (LEFT == side && !IsTaken(node->children[RIGHT]))
        {
            requsted = min_ip;
            RecAllocIP(,min_ip,)
        }
        else
        {
            return IP_NOT_AVAILABLE_ERROR;
        }
    }

    return SUCCESS;
}
*/

