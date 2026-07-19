#include <stdio.h>

#include "dhcp.h"

void PrintIP(unsigned char arr[BYTES_IN_IP])
{
    size_t i = 0;
    for(i = 0; i < BYTES_IN_IP; ++i)
    {
        printf("%d", arr[i]);
        printf(".");
    }
    printf("\n\n");
}

void AllocTest(void)
{
    dhcp_status_t status = SUCCESS;
    size_t size = 0;
    unsigned char subnet[BYTES_IN_IP] = {192, 168, 1, 1};
    unsigned char request_ip1[BYTES_IN_IP] = {192, 168, 192, 1};
    unsigned char request_ip2[BYTES_IN_IP] = {192, 168, 192, 2};
    unsigned char request_ip3[BYTES_IN_IP] = {192, 168, 192, 3};
    unsigned char request_ip4[BYTES_IN_IP] = {192, 168, 192, 4};
    unsigned char request_ip5[BYTES_IN_IP] = {192, 168, 192, 5};
    unsigned char request_ip6[BYTES_IN_IP] = {192, 168, 192, 6};
    unsigned char request_ip7[BYTES_IN_IP] = {192, 168, 192, 7};
    unsigned char request_ip8[BYTES_IN_IP] = {192, 168, 192, 8};
    unsigned char request_ip9[BYTES_IN_IP] = {192, 168, 192, 9};
    unsigned char request_ip10[BYTES_IN_IP] = {192, 168, 192, 255};
    
    unsigned char request_ip11[BYTES_IN_IP] = {192, 168, 255, 254};
    unsigned char request_ip12[BYTES_IN_IP] = {192, 168, 0, 1};

    unsigned char result_ip[BYTES_IN_IP] = {0};
    
    dhcp_t* dhcp = DHCPCreate(subnet, 16);

    size = DHCPCountFree(dhcp);
    printf("size = %ld\n", size);

    status = DHCPAllocIP(dhcp, request_ip1, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip2, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip1, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    
    status = DHCPAllocIP(dhcp, request_ip2, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    
    status = DHCPAllocIP(dhcp, request_ip3, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip1, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    
    status = DHCPAllocIP(dhcp, request_ip5, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip7, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip8, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip9, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip10, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    
    status = DHCPAllocIP(dhcp, request_ip10, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip11, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);

    
    status = DHCPAllocIP(dhcp, request_ip12, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip12, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
    status = DHCPAllocIP(dhcp, request_ip6, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);
   
    
   
    size = DHCPCountFree(dhcp);
    printf("size = %ld\n", size);
   
    status = DHCPFreeIP(dhcp, request_ip3);
    printf("status = %d\n", status);
    status = DHCPFreeIP(dhcp, request_ip2);
    printf("status = %d\n", status);
    
    status = DHCPFreeIP(dhcp, request_ip6);
    printf("status = %d\n", status);

    size = DHCPCountFree(dhcp);
    printf("size = %ld\n", size);
    
    status = DHCPAllocIP(dhcp, request_ip1, result_ip);
    printf("status = %d\n", status);
    PrintIP(result_ip);

    size = DHCPCountFree(dhcp);
    printf("size = %ld\n", size);
    DHCPDestroy(dhcp);
}

int main()
{
    AllocTest();
    return 0;
}