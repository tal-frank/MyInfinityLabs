#include "dhcp.h" 

typedef struct Trie_node
{
    
};

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