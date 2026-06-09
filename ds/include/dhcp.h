#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>

#define BYTES_IN_IP (4)

typedef enum DHCPStatus
{
    SUCCESS,
    MEMORY_ERROR,
    IP_NOT_ALLOCATED_ERROR,
    IP_NOT_AVAILABLE_ERROR
} dhcp_status_t;

typedef struct Dhcp dhcp_t;


dhcp_t* DHCPCreate(const unsigned char subnet[BYTES_IN_IP], size_t num_of_bits_in_subnet);

void DHCPDestroy(dhcp_t* dhcp);

dhcp_status_t DHCPAllocIP(dhcp_t* dhcp,
                          const unsigned char request_ip[BYTES_IN_IP],
                          unsigned char result_ip[BYTES_IN_IP]);

dhcp_status_t DHCPFreeIP(dhcp_t* dhcp, const unsigned char ip_to_free[BYTES_IN_IP]);

size_t DHCPCountFree(const dhcp_t* dhcp);

#endif /* End of __DHCP_H__ */