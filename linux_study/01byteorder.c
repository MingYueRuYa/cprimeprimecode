#include <stdio.h>
#include <arpa/inet.h>

int main(void)
{
    unsigned long x = 0x12345678;
    unsigned char *p = (unsigned char *)&x;
    printf("%0x, %0x, %0x, %0x.\n", p[0], p[1], p[2], p[3]);
    // 78, 56, 34, 12.

    // 将host转为network long类型，大端类型
    unsigned long y = ntohl(x);
    p = (unsigned char *)&y;
    printf("%0x, %0x, %0x, %0x.\n", p[0], p[1], p[2], p[3]);
    // 12, 34, 56, 78.

    return 0;
}
