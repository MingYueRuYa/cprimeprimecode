#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

// int getrlimit(int resource, struct rlimit *rlim);
// int setrlimit(int resource, const struct rlimit *rlim);

// struct rlimit {
// 	rlim_t rlim_cur;  /* Soft limit */
// 	rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
// };


int main(int argc, char *argv[])
{
	struct rlimit rlim;
	if (getrlimit(RLIMIT_NOFILE, &rlim) < 0) {
		perror("getrlimit");
		exit(-1);
	}
	printf("max fd count:%d\n", (int)rlim.rlim_max);
	
	rlim.rlim_cur = 2048;
	if (setrlimit(RLIMIT_NOFILE, &rlim) < 0) {
		perror("setrlimit");
		exit(-1);
	}
	printf("max fd count:%d\n", (int)rlim.rlim_max);
	printf("cur fd count:%d\n", (int)rlim.rlim_cur);

	return 0;
}
