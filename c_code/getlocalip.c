#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>

int GetLocalIp(char *pLocalIp, int pIpLen);

int main(int argc ,char *argv[])
{
	char ipchar[1024] = {0};
	GetLocalIp(ipchar, 1024);
	printf("ipaddrss: %s.\n", ipchar);
	return 0;
}

int GetLocalIp(char *pLocalIp, int pIpLen)
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s;
	char host[NI_MAXHOST] = {0};

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs error");
		return -1;
	}
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL) {
			continue;
		}
		family = ifa->ifa_addr->sa_family;
		if (family == AF_INET || family == AF_INET6) {
			s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
			if (0 != s) {
				printf("getnameinfo() failed: %s.\n", gai_strerror(s));
				return -1;
			}
			if (strlen(pLocalIp) < (pIpLen - 1)) {
				strcat(pLocalIp, "-");
			}
			if (strlen(pLocalIp) < (pIpLen - strlen(host))) {
				strcat(pLocalIp, host);
			}
		}
	}
	freeifaddrs(ifaddr);
	return 0;
}
