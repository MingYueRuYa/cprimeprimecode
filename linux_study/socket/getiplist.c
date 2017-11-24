#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <netdb.h>

int main(void)
{
    char hostname[1024] = {0};
    if (gethostname(hostname, sizeof(hostname)) < 0) {
        return -1;
    }
    printf("hostname:%s\n", hostname);

    struct hostent *dp = gethostbyname(hostname);
    if (dp == NULL) {
        return -1;
    }

    int i = 0;
    while (dp->h_addr_list[i] != NULL) {
        printf("ip:%s\n", inet_ntoa(*(struct in_addr *)dp->h_addr_list[i]));
        i++;
    }

    return 0;
}
