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
                              int bytes,
                              int bits);

static dhcp_status_t TrieInsert(trie_node_t* node,
                                unsigned char ip_arr[],
                                int bytes,
                                int bits,
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

    TrieInsert(dhcp->trie->root,
               server_address,
               bytes,
               bits,
               server_address);

    TrieInsert(dhcp->trie->root,
               broadcast_address,
               bytes,
               bits,
               broadcast_address);

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
                        (NULL == request_ip) ? initial_ip :
                                               (unsigned char*)request_ip,
                        bytes,
                        bits,
                        result_ip);

    if (IP_NOT_AVAILABLE_ERROR == status)
    {
        memcpy(result_ip, dhcp->subnet, BYTES_IN_IP);
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
    size_t num_allocated = TrieCountAllocated(dhcp->trie->root, host_bits);
    return IntPow(2, host_bits) - num_allocated;
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
    unsigned char init_ip[BYTES_IN_IP] = {0};
    unsigned char mask = 0;
    unsigned int path = 0;
    int next_bytes = bytes;
    int next_bits = bits - 1;

    if (ALLOCATED == node->is_allocated)
    {
        return IP_NOT_AVAILABLE_ERROR;
    }

    if (BYTES_IN_IP <= bytes)
    {
        node->is_allocated = ALLOCATED;
        return SUCCESS;
    }

    mask = (unsigned char)(1u << bits);
    path = !!(ip_arr[bytes] & mask);

    if (0 > next_bits)
    {
        next_bits = CHAR_BIT_SIZE - 1;
        ++next_bytes;
    }

    if (NULL == node->children[path])
    {
        node->children[path] = CreateNode();
        if (NULL == node->children[path])
        {
            return MEMORY_ERROR;
        }
    }

    status = TrieInsert(node->children[path],
                        ip_arr,
                        next_bytes,
                        next_bits,
                        result_ip);

    if ((IP_NOT_AVAILABLE_ERROR == status) && (ZERO == path))
    {
        path = ONE;

        if (NULL == node->children[ONE])
        {
            node->children[ONE] = CreateNode();
            if (NULL == node->children[ONE])
            {
                return MEMORY_ERROR;
            }
        }

        status = TrieInsert(node->children[ONE],
                            init_ip,
                            next_bytes,
                            next_bits,
                            result_ip);
    }

    if (SUCCESS == status)
    {
        (ZERO == path) ? (result_ip[bytes] &= ~mask) :
                         (result_ip[bytes] |= mask);
        UpdateAllocation(node);
    }

    return status;
}

static dhcp_status_t TrieFree(trie_node_t* node,
                              unsigned char ip_arr[],
                              int bytes,
                              int bits)
{
    dhcp_status_t status = SUCCESS;
    unsigned char mask = 0;
    unsigned int path = 0;
    int next_bytes = bytes;
    int next_bits = bits - 1;
    trie_node_t* next_node = NULL;

    if (BYTES_IN_IP <= bytes)
    {
        if (NOT_ALLOCATED == node->is_allocated)
        {
            return IP_NOT_ALLOCATED_ERROR;
        }

        node->is_allocated = NOT_ALLOCATED;
        return SUCCESS;
    }

    mask = (unsigned char)(1u << bits);
    path = !!(ip_arr[bytes] & mask);
    next_node = node->children[path];

    if (NULL == next_node)
    {
        return IP_NOT_ALLOCATED_ERROR;
    }

    if (0 > next_bits)
    {
        next_bits = CHAR_BIT_SIZE - 1;
        ++next_bytes;
    }

    status = TrieFree(next_node, ip_arr, next_bytes, next_bits);

    if (SUCCESS == status)
    {
        node->is_allocated = NOT_ALLOCATED;
    }

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
