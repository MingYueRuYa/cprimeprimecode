#ifndef common_h
#define common_h

#include <sys/time.h>
#include <sys/resource.h>

#define ERR_EXIT(msg)   \
    do  \
    {   \
        perror(msg);    \
        exit(EXIT_FAILURE);  \
    } while (0)

typedef struct packet {
    int len;
    char buff[1024];
} packet;

void setfdcount(const int maxfdcount)
{
	struct rlimit rlim;
 	if (getrlimit(RLIMIT_NOFILE, &rlim) < 0) {
 		perror("getrlimit");
 		exit(-1);
 	}
 	printf("max fd count:%d\n", (int)rlim.rlim_max);
	
	rlim.rlim_cur = maxfdcount;
	if (setrlimit(RLIMIT_NOFILE, &rlim) < 0) {
		perror("setrlimit");
		exit(-1);
	}
	printf("max fd count:%d\n", (int)rlim.rlim_max);
	printf("cur fd count:%d\n", (int)rlim.rlim_cur);
}

#endif //common_h
