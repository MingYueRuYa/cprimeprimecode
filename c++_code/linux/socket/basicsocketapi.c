/*
 * basic socket API exercise
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	struct in_addr inp;
	if (0 == inet_aton("192.168.1.1", &inp)) {
		printf("inet_aton error.\n");
		exit(-1);
	}
	
	char *ipaddrch = inet_ntoa(inp);
	printf("ip address %s.\n", ipaddrch);
	return 0;
}
