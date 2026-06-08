#include <stdlib.h> /* malloc , free */
#include 

#include "dhcp.h" /* dhcp API */

enum
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

struct DHCP
{
     const unsigned char subnet[BYTES_IN_IP];
     trie_t* trie;
};



dhcp_t* DHCPCreate(const unsigned char subnet[BYTES_IN_IP], size_t num_of_bits_in_subnet);

void DHCPDestroy(dhcp_t* dhcp);

dhcp_status_t DHCPAllocIP(dhcp_t* dhcp,
                          const unsigned char request_ip[BYTES_IN_IP],
                          unsigned char result_ip[BYTES_IN_IP]);

dhcp_status_t DHCPFreeIP(dhcp_t* dhcp, const unsigned char ip_to_free[BYTES_IN_IP]);

size_t DHCPCountFree(const dhcp_t* dhcp);


static trie_t* TrieCreate(void)
{
    trie_t* trie = (trie_t*)malloc(sizeof(trie_t));
    if (NULL == trie)
    {
        return NULL;
    }
    trie->root = (trie_node_t*)calloc(1, sizeof(trie_node_t));
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;
        return NULL;
    }
}