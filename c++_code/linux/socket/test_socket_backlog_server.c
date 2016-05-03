#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static int stop = 0;

static void Handle_Term(int sig)
{
	stop = 1;
}

int main(int argc, char *argv[])
{
	signal(SIGTERM, Handle_Term);
	if (argc < 3) {
		//printf("usage: %s ip_addrss port_number backlog.\n", basename(argv[0]));
		return 0;
	}
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	int backlog = atoi(argv[3]);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	assert(sock >= 0);
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);
	int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);
	ret = listen(sock, backlog);
	assert(ret != -1);
	while (! stop) {
		sleep(1);
	}
	close(sock);
	return 0;
}
