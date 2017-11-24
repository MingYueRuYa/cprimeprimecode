#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
    unsigned long addr = inet_addr("192.168.0.100");
    printf("%u.\n", addr);  //1677764800.

    struct in_addr ipaddr;
    ipaddr.s_addr = addr;
    printf("%s.\n", inet_ntoa(ipaddr)); //192.168.0.100

    struct sockaddr_in addr_in;
    printf("sockaddr_in size:%d.\n", sizeof(addr_in));
    printf("sockaddr_in sin_family size %d.\n", sizeof(addr_in.sin_family));
    printf("sockaddr_in sin_port size %d.\n", sizeof(addr_in.sin_port));
    printf("sockaddr_in sin_addr size %d.\n", sizeof(addr_in.sin_addr.s_addr));

    return 0;
}
